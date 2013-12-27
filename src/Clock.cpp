#include "Clock.h"
#include <math.h>
#include <cmath>

Clock::Clock(){
	oldt=0;
	newt=0;
	count=false;
	timer=0;
}

void Clock::draw() 
{
	if(count){
		newt=glutGet(GLUT_ELAPSED_TIME);
		elapsed=newt-oldt;
		oldt=newt;
		timer+=elapsed;
		
	}
	else{
		count=true;
		newt=glutGet(GLUT_ELAPSED_TIME);
		oldt=glutGet(GLUT_ELAPSED_TIME);
	}
	
	
	min=(timer/1000)/60;
	sec=(timer/1000)%60;

	itoa(min,minute,10);
	itoa(sec,second,10);

	glDisable(GL_LIGHTING);

	glPushMatrix();

	glTranslatef(-12,0,-60);
	glScalef(0.05, 0.05, 0.05);
		glColor3f(1.0,0.0,0.0);
		if(min>10){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, minute[0]);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, minute[1]);
		}
		else{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, minute[0]);
		}
		glutStrokeCharacter(GLUT_STROKE_ROMAN, ':');
		if(sec>10){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, second[0]);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, second[1]);
		}
		else{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, second[0]);
		}
	glPopMatrix();
	glEnable(GL_LIGHTING);

	// Texto BitMap, GLUT
	// glRasterPos3f(x,y,z);
	// void glutBitmapCharacter(void *font, int character);	// valores varios...
	// int glutBitmapWidth(GLUTbitmapFont font, int character);


}