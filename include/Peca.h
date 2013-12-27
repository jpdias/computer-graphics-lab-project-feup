#ifndef PECA_H
#define PECA_H

#include <string>
#include "CGFscene.h"
#include "ObjectCompost.h"
#include "Object.h"
#include <map>

class Peca: public CGFobject {

	public:
		double x;
		double y;
		string type;
		bool c,isCastle;
		char team;
		int num;
		Peca(double num,double x,double y,string type,char team,map<string,Object*> mapObjects);
		void draw();
		
		Object *piece;
		void setX(double x);
		void setY(double y);
};

#endif