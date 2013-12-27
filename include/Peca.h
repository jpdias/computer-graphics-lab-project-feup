#ifndef PECA_H
#define PECA_H

#include <string>
#include "CGFscene.h"
#include "ObjectCompost.h"
#include "Object.h"
#include <map>

class Peca: public CGFobject {

	public:
		int x;
		int y;
		string type;
		bool c,isCastle;
		char team;
		
		Peca(int x,int y,string type,char team,map<string,Object*> mapObjects);
		void draw();
		Object *piece;
		ObjectCompost *pieceCompost;
};

#endif