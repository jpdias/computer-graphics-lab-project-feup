#include "Tabuleiro.h"
//#include "DemoScene.h"
#include <iostream>
using std::cout;

Tabuleiro::Tabuleiro(){
	text1=true;
	obj.x1=-0.5;
	obj.y1=-0.5;
	obj.x2=0.5;
	obj.y2=0.5;
	dirt=new CGFappearance("data/dirt.jpg",1,1);
	rock=new CGFappearance("data/rock.jpg",1,1);
	black = new CGFappearance("data/black.jpg",1,1);
	white = new CGFappearance("data/white.jpg",1,1);

	float sp[4] = {0.1, 0.1,0.1, 0};
	float a[4] = {0.8, 0.8,0.8, 0};
	float z[4] = {0.3, 0.3,0.3, 0};
	rock->setSpecular(sp);
	rock->setAmbient(a);
	rock->setDiffuse(z);
	rock->setShininess(0.7);
	dirt->setSpecular(sp);
	dirt->setAmbient(a);
	dirt->setDiffuse(z);
	black->setSpecular(sp);
	black->setAmbient(a);
	black->setDiffuse(z);
	black->setShininess(0.7);
	white->setSpecular(sp);
	white->setAmbient(a);
	white->setDiffuse(z);
	rock->setShininess(0.7);
	
	wall = new CGFappearance();
	wall->setTexture("data/wall.jpg");
	wall->setTextureWrap(GL_REPEAT,GL_REPEAT);

	initTab();
	placePieces();
}

void Tabuleiro::draw(int text1){
	obj.x1=-0.5;
	obj.y1=-0.5;
	obj.x2=0.5;
	obj.y2=0.5;
	
	
		glPushMatrix();
	wall->apply();
	glTranslatef(0,-5.1,0);
	glScaled(140,10,140);
	
	glutSolidCube(1);

	glPopMatrix();

	
	
	glPushMatrix();
	glTranslatef(55, 0, -55);
	glRotatef(90,0,0,1);
	glScaled(5,5,5);
	
	glPushName(-1);		// Load a default name

	// example 2: structured naming
	for (int r=0; r < NUM_ROWS; r++)
	{
		glPushMatrix();
		glTranslatef(0, r, 0);
		glLoadName(r+1);
		for (int c=0; c < NUM_COLS; c++)
		{
			glPushMatrix();
			glTranslatef(0,0,c);
			glRotatef(90,0,1,0);
			glPushName(c+1);
			glPushMatrix();
			if(c%2==0 && r%2==0)
				if(text1)
					rock->apply();
				else
					black->apply();
			else if(c%2!=0 && r%2==0)
				if(text1)
					dirt->apply();
				else
					white->apply();
			else if(c%2==0 && r%2!=0)
				if(text1)
				dirt->apply();
				else
					white->apply();
			else
				if(text1)
				rock->apply();
				else
					black->apply();
			
			obj.draw();
			
			glPopMatrix();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();

	}

		glPopMatrix();
		
		for(int i=0;i<jog1Pecas.size();i++)
			jog1Pecas.at(i)->draw();
		for(int i=0;i<jog2Pecas.size();i++)
			jog2Pecas.at(i)->draw();
}

void Tabuleiro::initTab(){
	//               m-v-v-1
	string l1[] = {"n-a-ki-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-a-d-1"};
	vector<string>line (std::begin(l1), std::end(l1));
	board.push_back(line);

	string l2[] = {"n-a-p-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","[c-a]-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l2), std::end(l2));
	board.push_back(line);
	
	string l3[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","[g-a]-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l3), std::end(l3));
	board.push_back(line);
	
	string l4[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-a-k-1","n-v-v-1","n-a-sq-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l4), std::end(l4));
	board.push_back(line);
	
	string l5[] = {"n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l5), std::end(l5));
	board.push_back(line);
	
	string l6[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1"};
	line.assign(std::begin(l6), std::end(l6));
	board.push_back(line);
	
	string l7[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-a-ar-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l7), std::end(l7));
	board.push_back(line);
	
	string l8[] = {"n-v-v-1","n-a-ki-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-a-ki-2"};
	line.assign(std::begin(l8), std::end(l8));
	board.push_back(line);
	
	string l9[] = {"m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l9), std::end(l9));
	board.push_back(line);
	
	string l10[] = {"m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-a-pi-1","n-a-pi-2","n-a-se-1","n-a-se-2","n-a-pi-3","n-a-pi-4","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l10), std::end(l10));
	board.push_back(line);
	
	string l11[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l11), std::end(l11));
	board.push_back(line);
	
	string l12[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l12), std::end(l12));
	board.push_back(line);
	
	string l13[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l13), std::end(l13));
	board.push_back(line);
	
	string l14[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l14), std::end(l14));
	board.push_back(line);
	
	string l15[] = {"m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-b-pi-1","n-b-pi-2","n-b-se-1","n-b-se-2","n-b-pi-3","n-b-pi-4","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l15), std::end(l15));
	board.push_back(line);
	
	string l16[] = {"m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l16), std::end(l16));
	board.push_back(line);
	
	string l17[] = {"n-v-v-1","n-b-ki-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-b-ki-2"};
	line.assign(std::begin(l17), std::end(l17));
	board.push_back(line);
	
	string l18[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-b-ar-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l18), std::end(l18));
	board.push_back(line);
	
	string l19[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1"};
	line.assign(std::begin(l19), std::end(l19));
	board.push_back(line);
	
	string l20[] = {"n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l20), std::end(l20));
	board.push_back(line);
	
	string l21[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-b-k-1","n-v-v-1","n-b-sq-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","r-v-v-1","r-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l21), std::end(l21));
	board.push_back(line);
	
	string l22[] = {"n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","[g-b]-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l22), std::end(l22));
	board.push_back(line);
	
	string l23[] = {"n-b-p-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","[c-b]-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1"};
	line.assign(std::begin(l23), std::end(l23));
	board.push_back(line);
	
	string l24[] = {"m-v-v-1","n-v-v-1","n-v-v-1","m-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-v-v-1","n-b-d-1"};
	line.assign(std::begin(l24), std::end(l24));
	board.push_back(line);

}

void Tabuleiro::placePieces(){
	string type,team,piece,tmp;
	int num;
	string delim ="-";
	/*
	
	ark = new Object("data/arrow.obj");
	tower = new Object("data/tower.obj");
	seargent = new Object("data/duke.obj");
	knight = new ObjectCompost("data/knight.obj","data/horse.obj");
	duke = new ObjectCompost("data/duke.obj","data/horse.obj");
	prince = new ObjectCompost("data/prince.obj","data/horse.obj");
	squire = new Object("data/prince.obj");
	king = new Object("data/knight.obj");
	pike = new Object("data/pike.obj");

	*/
	for(int i=0;i<board.size();i++){
		for(int j=0;j<board.at(i).size();j++){
			
			//PARSE
			//######[c-a]

			if(board.at(i).at(j).substr(0, board.at(i).at(j).find(delim)).compare("[c")==0){
				tmp=board.at(i).at(j).substr(board.at(i).at(j).find(delim));
				if(tmp.at(1)=='a')
					jog1Pecas.push_back(new Peca(j,i,"castle",tmp.at(1)));
				if(tmp.at(1)=='b')
					jog2Pecas.push_back(new Peca(j,i,"castle",tmp.at(1)));
			}
			else if(board.at(i).at(j).substr(0, board.at(i).at(j).find(delim)).compare("[g")==0){
				tmp=board.at(i).at(j).substr(board.at(i).at(j).find(delim));
				if(tmp.at(1)=='a')
					jog1Pecas.push_back(new Peca(j,i,"garden",tmp.at(1)));
				if(tmp.at(1)=='b')
					jog2Pecas.push_back(new Peca(j,i,"garden",tmp.at(1)));
			}
		
			else{
			type = board.at(i).at(j).substr(0, board.at(i).at(j).find(delim));
			tmp=board.at(i).at(j).substr(board.at(i).at(j).find(delim)+1);
			team=tmp.substr(0, tmp.find(delim));
			tmp=tmp.substr(tmp.find(delim)+1);		
			piece=tmp.substr(0, tmp.find(delim));
			num=atoi(tmp.substr(tmp.find(delim)+1).c_str());
			//######
			//if(team.compare("v")!=0){
			if ((piece.compare("ki")==0)||(piece.compare("p")==0)||(piece.compare("d")==0)||(piece.compare("se")==0)||(piece.compare("sq")==0)||(piece.compare("pi")==0)||(piece.compare("k")==0))	
			if(team.compare("a")==0)
				jog1Pecas.push_back(new Peca(j,i,piece,team.at(0)));
				else if(team.compare("b")==0)
					jog2Pecas.push_back(new Peca(j,i,piece,team.at(0)));

			}
			//}

			//n-a-ki-1
			//sscanf(board.at(i).at(j),"%s-%s-%s-%d",type,team,piece,num);
		}
		
	}


}
