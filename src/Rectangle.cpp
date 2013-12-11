#include "Rectangle.h"
#include "DemoScene.h"
void Rectangle::draw() 
{
	
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glTexCoord2d(0,0);
		glVertex3f(x1,y1,0);
		glTexCoord2d(x2-x1,0);
		glVertex3f(x2,y1,0);
		glTexCoord2d(x2-x1,y2-y1);
		glVertex3f(x2,y2,0);
		glTexCoord2d(0,y2-y1);
		glVertex3f(x1,y2,0);
	glEnd();

}