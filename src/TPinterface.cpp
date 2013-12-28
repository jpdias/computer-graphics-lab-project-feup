#include "TPinterface.h"




// buffer to be used to store the hits during picking
#define BUFSIZE 256

bool selec,next_c;
int sel,oldx,oldy;
char player;
using namespace std;

GLuint selectBuf[BUFSIZE];



TPinterface::TPinterface()
{
	next_c=false;
}


void TPinterface::initGUI()
{
	/*GLUI_Panel *varLuz= addPanel("Cameras", 2);
	addCheckboxToPanel(varLuz, "Camera Jog1",&((DemoScene *) scene)->state1,NULL);
	addColumn ();
	GLUI_Panel *varClock= addPanel("Relogio", 3);
	addStaticText("Relógio");
	addButton ("Pause/Start",1);
	addColumn ();*/
	GLUI_Panel *text1= addPanel("Cameras");
	GLUI_RadioGroup *group2=addRadioGroupToPanel(text1,&((DemoScene *) scene)->cams);
	addRadioButtonToGroup(group2,"Top");
	addRadioButtonToGroup(group2,"Standard");
	addRadioButtonToGroup(group2,"Jog1");
	addRadioButtonToGroup(group2,"Jog2");
	
	addColumn();


	GLUI_Panel *text= addPanel("Wireframe");
	GLUI_RadioGroup *group1=addRadioGroupToPanel(text,&((DemoScene *) scene)->wire);
	addRadioButtonToGroup(group1,"Normal");
	addRadioButtonToGroup(group1,"Wireframe");
	addColumn();
	GLUI_Panel *varwire= addPanel("Appearance");
	GLUI_RadioGroup *group=addRadioGroupToPanel(varwire,&((DemoScene *) scene)->texttab);
	addRadioButtonToGroup(group,"Standard");
	addRadioButtonToGroup(group,"Rock");
	addColumn();
	turn = addPanel("Turn");
	turn->set_name("Turn: Player A");
	addButtonToPanel(turn,"End Turn",101);
	
	socketConnect();
	//quit();
}
void TPinterface::processGUI(GLUI_Control *ctrl)
{	
	switch (ctrl->user_id)
	{
	case 101:
			
			 if(((DemoScene *) scene)->turn=='b'){
				 ((DemoScene *) scene)->turn='a';
				 turn->set_name("Turn: Player A");
			 }
			 else if(((DemoScene *) scene)->turn=='a'){
				 ((DemoScene *) scene)->turn='b';
				 turn->set_name("Turn: Player B");
			 }
			 printf("\nTurn:%c",((DemoScene *) scene)->turn);
			 envia("changeturn.\n",strlen("changeturn.\n"));
			break;
		};

	
}

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);
	
	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !Animation::go)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	char str_socket[128];
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected,x,y;
	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		int size;
		for (int i=0; i<nselected; i++){
			
			if(i==0){
				x=selected[i];
				printf("%d ",x);
			}
			else{
				y=selected[i];
				printf("%d ",y);

				if(((DemoScene *) scene)->turn=='a' || selec==true){
					size= ((DemoScene *) scene)->tab->jog1Pecas.size();
					for(int j=0;j< size;j++){
						if((((DemoScene *) scene)->tab->jog1Pecas.at(j)->x==x) && (((DemoScene *) scene)->tab->jog1Pecas.at(j)->y==y)){
							if(!selec){
								printf(" Player A Piece selected");
								next_c = true;
								sel = j;
								oldx=x;
								oldy=y;
								player = 'a';
							}
							else
							{
									((DemoScene *) scene)->tab->jog1Pecas.erase((((DemoScene *) scene)->tab->jog1Pecas).begin()+j);
									break;
							}
						}
					}

				}
				if(((DemoScene *) scene)->turn=='b' || selec==true){
					size= ((DemoScene *) scene)->tab->jog2Pecas.size();
					for(int j=0;j< size;j++){
						if((((DemoScene *) scene)->tab->jog2Pecas.at(j)->x==x) && (((DemoScene *) scene)->tab->jog2Pecas.at(j)->y==y)){
							if(!selec){
								printf(" Player B Piece");
								next_c = true;
								sel = j;
								oldx=x;
								oldy=y;
								player = 'b';
							}
							else
							{
									((DemoScene *) scene)->tab->jog2Pecas.erase((((DemoScene *) scene)->tab->jog2Pecas).begin()+j);
									break;
							}
						}
					}
				}
				if(selec)
				{
					int space,direction=getDirection(x,y,oldx,oldy,&space);
					printf("\nDIR:%d|SPACE:%d\n",direction,space);
					selec = false;
					next_c = false;
					fill( begin( str_socket ), end( str_socket ), 0 );
					if(((DemoScene *) scene)->turn=='a')
						_snprintf(str_socket,128,"movepiece-%s-%c-%d-%d-%d.",((DemoScene *) scene)->tab->jog1Pecas.at(sel)->type.c_str(),player,((DemoScene *) scene)->tab->jog1Pecas.at(sel)->num,direction,space);
					else if(((DemoScene *) scene)->turn=='b')
						_snprintf(str_socket,128,"movepiece-%s-%c-%d-%d-%d.",((DemoScene *) scene)->tab->jog2Pecas.at(sel)->type.c_str(),player,((DemoScene *) scene)->tab->jog2Pecas.at(sel)->num,direction,space);
					strcat(str_socket,"\n");
					envia(str_socket,strlen(str_socket));
					fill( begin( str_socket ), end( str_socket ), 0 );
					recebe(str_socket);
					if(strcmp(str_socket,"true")==0){
						if(((DemoScene *) scene)->turn=='a'){
							((DemoScene *) scene)->movePiece(((DemoScene *) scene)->tab->jog1Pecas.at(sel),x,y);
							((DemoScene *) scene)->tab->jog1Pecas.at(sel)->newx=x;
							((DemoScene *) scene)->tab->jog1Pecas.at(sel)->newy=y;
							Animation::go=true;
							/*for(int j=0;j< size;j++){
								if((((DemoScene *) scene)->tab->jog2Pecas.at(j)->x==x) && (((DemoScene *) scene)->tab->jog2Pecas.at(j)->y==y)){
									((DemoScene *) scene)->tab->jog2Pecas.erase((((DemoScene *) scene)->tab->jog2Pecas).begin()+j-1);
								}
							}*/
						}
						else if(((DemoScene *) scene)->turn=='b'){
							((DemoScene *) scene)->movePiece(((DemoScene *) scene)->tab->jog2Pecas.at(sel),x,y);
							((DemoScene *) scene)->tab->jog2Pecas.at(sel)->newx=x;
							((DemoScene *) scene)->tab->jog2Pecas.at(sel)->newy=y;
							Animation::go=true;
						}
					}
				}
				if(next_c)
					selec = true;

			}

		}
		printf("\n");
	}
	else
		printf("Nothing selected while picking \n");	
}

bool TPinterface::socketConnect() {// Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return false;
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
    }

    // Send and receive data.
	printf("Connected\n");
	return true;
}
void TPinterface::envia(char *s, int len) {
	int bytesSent = send(m_socket, s, len, 0);
	if(bytesSent == SOCKET_ERROR)
		printf("Client: send() error %ld.\n", WSAGetLastError());
}
void TPinterface::recebe(char *ans) {
	int bytesRecv = SOCKET_ERROR;
	char t[6]="true";
	t[4]=13;
	char f[7]="false";
	f[5]=13;
	int pos = 0;
	while (true) {
		recv(m_socket, &ans[pos], 1, 0);
		if (ans[pos] == '\n')
			break;
		pos++;
	}
	ans[pos] = 0;
	if(strcmp(ans,t)==0){
		memset(&ans[0], 0, sizeof(ans));
		strcpy(ans,"true");
	}
	else if(strcmp(ans,f)==0){
		memset(&ans[0], 0, sizeof(ans));
		strcpy(ans,"false");
	}	
}
void TPinterface::quit() {
	cout << "Asking prolog to quit" << endl;
	char buff[] = "quit.\n";
	envia(buff, 6);
	char ans[128];
	recebe(ans);
}

int TPinterface::getDirection(int newy,int newx,int oldy,int oldx,int *space)
{
	int x_len=newx-oldx;
	int y_len=newy-oldy;
	
	if(x_len!=0)
		*space = abs(x_len);
	else
		*space = abs(y_len);
	//Diagonals
	if(abs(x_len)==abs(y_len))
	{
		if(newx<oldx && newy<oldy)
			return 1;
		else if(newx>oldx && newy<oldy)
			return 3;
		else if(newx>oldx && newy>oldy)
			return 8;
		else if(newx<oldx && newy>oldy)
			return 6;
	}
	else if(x_len == 0 && y_len == 0)
		return 0;
	else if((x_len == 0 && y_len != 0) ||
			(x_len != 0 && y_len == 0))
	{
		if(x_len>0)
			return 5;
		else if(x_len<0)
			return 4;
		else if(y_len<0)
			return 2;
		else if(y_len>0)
			return 7;
	}
	else
		return 10;

}