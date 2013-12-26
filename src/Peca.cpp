#include "Peca.h"

Peca::Peca(int y,int x,string type,char team){
	this->x=x;
	this->y=y;
	this->type=type;
	this->team=team;
	c=false;
	isCastle=false;

	if(type.compare("ki")==0){
		c=true;
		pieceCompost = new ObjectCompost("data/knight.obj","data/horse.obj");
	}
	else if(type.compare("p")==0){
		c=true;
		pieceCompost = new ObjectCompost("data/prince.obj","data/horse.obj");
	}
	else if(type.compare("d")==0){
		c=true;
		pieceCompost = new ObjectCompost("data/duke.obj","data/horse.obj");
	}
	else if(type.compare("se")==0)
		piece = new Object("data/duke.obj");
	else if(type.compare("sq")==0)
		piece = new Object("data/prince.obj");
	else if(type.compare("pi")==0)
		piece = new Object("data/pike.obj");
	else if(type.compare("k")==0)
		piece = new Object("data/knight.obj");
	else if(type.compare("castle")==0){
		piece = new Object("data/tower.obj");
		isCastle=true;
	}

	/*

pieceList([[k-1-'King'-3-3],
x[p-1-'Prince'-24-24],
x[d-1-'Duke'-24-24],
x[ki-1-'Kight 1'-24-24],[ki-2-'Kight 2'-24-24],
[se-1-'Sergeant 1'-2-13],[se-2-'Sergeant 2'-2-13],
[sq-1-'Squire'-'ERROR'-'ERROR'],[ar-1-'Archer'-4-4],
[pi-1-'Pikeman 1'-13-2],[pi-2-'Pikeman 2'-13-2],[pi-3-'Pikeman 3'-13-2],[pi-4-'Pikeman 4'-13-2]]).

	ark = new Object("data/arrow.obj");
	tower = new Object("data/tower.obj");
	seargent = new Object("data/duke.obj");
	knight = new ObjectCompost("data/knight.obj","data/horse.obj");
	duke = new ObjectCompost("data/duke.obj","data/horse.obj");
	prince = new ObjectCompost("data/prince.obj","data/horse.obj");
	squire = new Object("data/prince.obj");
	king = new Object("data/knight.obj");
	pike = new Object("data/pike.obj");
	*/

}

void Peca::draw(){

	//(27.5,0,-27.5) (1,1)
	glPopName();
	
	glPushMatrix();
		glPushName(x);
		glPushName(y);
		glTranslated(27.5-5*x,0,-27.5+5*y);
		if(team=='a')
			if(c)
				pieceCompost->draw(1);
			else
				piece->draw(1);
		else if(team=='b')
			if(c)
				pieceCompost->draw(0);
			else
				piece->draw(0);
		glPopName();
	glPopMatrix();

}