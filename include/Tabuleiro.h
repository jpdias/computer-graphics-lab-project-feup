#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "CGFobject.h"
#include "Rectangle.h"

#define NUM_ROWS 12
#define NUM_COLS 12

class Tabuleiro: public CGFobject {
	public:
		void draw();
		Tabuleiro();

	Rectangle obj;
};

#endif