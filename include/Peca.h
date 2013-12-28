#ifndef PECA_H
#define PECA_H

#include <string>
#include "CGFscene.h"
#include "ObjectCompost.h"
#include "Object.h"
#include "LinearAnimation.h"
#include <map>



class Peca: public CGFobject {

	public:
		double x,newx;
		double y,newy;
		double h,newz;
		string type;
		bool c,isCastle,animation;
		char team;
		int num;
		Peca(double num,double x,double y,string type,char team,map<string,Object*> mapObjects);
		void draw();
		
		Object *piece;
		void setX(double x);
		void setY(double y);
		LinearAnimation *ani;
};

#endif