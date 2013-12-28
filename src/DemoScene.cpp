#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include <math.h>
#include "CGFappearance.h"


void DemoScene::init() 
{
	  wire=false;
	  texttab=true;
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_FALSE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT);  // Define ambient light
	glShadeModel(GL_SMOOTH);
	if(wire)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else 
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	// Declares and enables a light
	float light0_pos[4] = {0, 40.0, 0, 0.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	float light1_pos[4] = {-19, 40.0, -19, 0.0};
	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	float light2_pos[4] = {19, 40.0, 19, 0.0};
	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	float light3_pos[4] = {-19, 40.0, 19, 0.0};
	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	float light4_pos[4] = {19, 40.0, -19, 0.0};
	light4 = new CGFlight(GL_LIGHT4, light4_pos);
	
	light0->enable();
	light1->enable();
	light2->enable();
	light3->enable();
	light4->enable();
	// Defines a default normal
	glNormal3f(0,0,1);
	camera1 = new Perspective("um",0,110,45,120,50,0,0,0,0);
	camera2 = new Perspective("dois",0,110,-45,-120,50,0,0,0,0);
	cameratop = new Perspective("tres",0,100,90,0.1,165,0,0,0,0);

/*
	ark = new Object("../data/arrow.obj");
	tower = new Object("../data/tower.obj");
	seargent = new Object("../data/duke.obj");
	knight = new ObjectCompost("../data/knight.obj","../data/horse.obj");
	duke = new ObjectCompost("../data/duke.obj","../data/horse.obj");
	prince = new ObjectCompost("../data/prince.obj","../data/horse.obj");
	squire = new Object("../data/prince.obj");
	king = new Object("../data/knight.obj");
	pike = new Object("../data/pike.obj");
	peak = new Object("../data/peak.obj");*/
	//tree = new Object("data/tre.obj");

	tab=new Tabuleiro();
	turn='a';
	setUpdatePeriod(30);
	elapsed=0;
	_time=0;
	moving=false;
	ppux=0;
	ppuy=0;
	timer=0;
	ctr=0;
}


void DemoScene::update(unsigned long t)
{
	long elapsedt = t - _time;
	_time = t;
	if(Animation::go){
		Animation::dt = elapsedt/1000.0;
		Animation::elapsed += elapsedt;
	}
	else{
		Animation::dt = 0;
		Animation::elapsed += 0;
		_time = t;
	}
	/*shader->bind();
	shader->update(t/400.0);
	shader->unbind();*/
}

void DemoScene::movePiece(Peca *p,double endx,double endy){
	vector<coordi> points;
	coordi pt;

	//55-5*x,0+h,-55+5*y
	
	pt.x=55-5*p->x;
	pt.y=0;
	pt.z=-55+5*p->y;

	points.push_back(pt);
	pt.y=5;
	points.push_back(pt);
	pt.x=55-5*endx;
	pt.y=5;
	pt.z=-55+5*endy;
	points.push_back(pt);
	pt.y=0;
	points.push_back(pt);
	p->ani=new LinearAnimation(points,1);
	p->animation=true;
}
void DemoScene::move(){
	timer+=elapsed;
	if(timer > ctr*1000){
		peca_link->setX(posx[ctr]);
		peca_link->setY(posy[ctr]);
		ctr++;
	}
	if(ctr==5){
		moving=false;
		ctr=0;
		timer=0;
	}
}
	
void DemoScene::display() 
{
	
	if(wire)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else 
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Apply transformations corresponding to the camera position relative to the origin
	//
	if(cams==0)
		cameratop->applyView();
	else if (cams==1)
		CGFscene::activeCamera->applyView();
	else if (cams==2)
		camera1->applyView();
	else if (cams == 3)
		camera2->applyView();
	else
		CGFscene::activeCamera->applyView();
	// Draw (and update) light
	//light0->draw();	
	light1->draw();	
	light2->draw();	
	light3->draw();	
	light4->draw();	


	tab->draw(texttab);
	clock.draw();



	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(light0);
}

void DemoScene::toggleSomething(){
};