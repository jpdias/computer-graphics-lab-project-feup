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
	 camera1 = new CGFcamera();
	 camera2 = new CGFcamera();
	
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
}


void DemoScene::update(unsigned long t)
{
	/*shader->bind();
	shader->update(t/400.0);
	shader->unbind();*/
	
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
	CGFscene::activeCamera->applyView();
	//camera1->applyView();
	// Draw (and update) light
	//light0->draw();	
	light1->draw();	
	light2->draw();	
	light3->draw();	
	light4->draw();	


	tab->draw(texttab);



	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(light0);
}

void DemoScene::toggleSomething(){
};