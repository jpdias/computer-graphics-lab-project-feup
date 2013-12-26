#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "CGFobject.h"
#include "Rectangle.h"
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#define NUM_ROWS 24
#define NUM_COLS 24

class Tabuleiro: public CGFobject {

	public:
		int text1;
		void draw(int text1);
		void drawbox(bool text2);
		Tabuleiro();
		CGFappearance* dirt;
		CGFappearance* rock;
		CGFappearance* black;
		CGFappearance* white;
		CGFappearance* wall;
	Rectangle obj;
	Rectangle cube;
};

#endif