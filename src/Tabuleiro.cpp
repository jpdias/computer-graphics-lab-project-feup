#include "Tabuleiro.h"
#include <iostream>
using std::cout;

Tabuleiro::Tabuleiro(){
	obj.x1=-0.5;
	obj.y1=-0.5;
	obj.x2=0.5;
	obj.y2=0.5;
}

void Tabuleiro::draw(){

	glPushMatrix();
	glTranslatef(27.5, 0, -27.5);
	glRotatef(90,0,0,1);
	glScaled(5,5,5);
	
//	glPushName(-1);		// Load a default name

	// example 2: structured naming
	for (int r=0; r < NUM_ROWS; r++)
	{
		glPushMatrix();
		glTranslatef(0, r, 0);
		glLoadName(r);
		for (int c=0; c < NUM_COLS; c++)
		{
			
			glPushMatrix();
			glTranslatef(0,0,c);
			glRotatef(90,0,1,0);
			glPushName(c);
			glPushMatrix();
			obj.draw();
			glPopMatrix();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}

		glPopMatrix();

}


