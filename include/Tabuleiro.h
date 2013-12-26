#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "CGFobject.h"
#include "Rectangle.h"
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#define NUM_ROWS 12
#define NUM_COLS 12

class Tabuleiro: public CGFobject {

	public:
		int text1;
		void draw(int text1);
		Tabuleiro();
		CGFappearance* dirt;
		CGFappearance* rock;
		CGFappearance* black;
		CGFappearance* white;
	Rectangle obj;
};

#endif