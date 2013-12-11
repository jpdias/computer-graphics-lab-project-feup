#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Object.h"
#include "ObjectCompost.h"

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
private:
	CGFlight* light0;
	Object* ark;
	Object* king;
	Object* tower;
	Object* seargent;
	Object* squire;
	Object* pike;
	ObjectCompost* knight;
	ObjectCompost* prince;
	ObjectCompost* duke;
};

#endif