#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
//#include "Object.h"
//#include "ObjectCompost.h"
#include "Tabuleiro.h"
#include "Camera.h"
#include "Clock.h"

class DemoScene : public CGFscene
{
public:
	CGFcamera* camera1;
	CGFcamera* camera2;
	CGFcamera* cameratop;
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
	int wire,texttab,cams;
	void toggleSomething();
	Tabuleiro* tab;
	unsigned long _time;
	Clock clock;
	char turn;
private:
	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;
	CGFlight* light4;
	CGFlight* light5;
	/*Object* ark;
	Object* king;
	Object* tower;
	Object* seargent;
	Object* squire;
	Object* pike;
	Object* peak;
	ObjectCompost* knight;
	ObjectCompost* prince;
	ObjectCompost* duke;*/
	
	Object* tree;

};

#endif