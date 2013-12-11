#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include <math.h>

#include "CGFappearance.h"

void DemoScene::init() 
{
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	// Declares and enables a light
	float light0_pos[4] = {0, 6.0, 0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	ark = new Object("../data/arrow.obj");
	tower = new Object("../data/tower.obj");
	seargent = new Object("../data/duke.obj");
	knight = new ObjectCompost("../data/knight.obj","../data/horse.obj");
	duke = new ObjectCompost("../data/duke.obj","../data/horse.obj");
	prince = new ObjectCompost("../data/prince.obj","../data/horse.obj");
	squire = new Object("../data/prince.obj");
	king = new Object("../data/knight.obj");
	pike = new Object("../data/pike.obj");

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
	
	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();
	
	// Draw (and update) light
	light0->draw();
	glPushMatrix();
	glTranslated(0,0,0);
	glRotated(-90,1,0,0);
	glBegin(GL_QUADS);

	glVertex2f(2.5, 2.5); 
	glVertex2f(-2.5, 2.5); 
	glVertex2f(-2.5, -2.5); 
	glVertex2f(2.5, -2.5);
 
	glEnd();
	glPopMatrix();
    
	glPushMatrix();
	
	ark->draw();
	
	glPopMatrix();


	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(light0);
}
