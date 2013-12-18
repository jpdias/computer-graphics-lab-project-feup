#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Object.h"
#include "ObjectCompost.h"
#include "Tabuleiro.h"

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
private:
	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;
	CGFlight* light4;
	CGFlight* light5;
	Object* ark;
	Object* king;
	Object* tower;
	Object* seargent;
	Object* squire;
	Object* pike;
	ObjectCompost* knight;
	ObjectCompost* prince;
	ObjectCompost* duke;
	Tabuleiro* tab;
};

#endif