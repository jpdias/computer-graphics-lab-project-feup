#include "Peca.h"

Peca::Peca(double num,double y,double x,string type,char team,map<string,Object*> mapObjects){
	this->x=x;
	this->y=y;
	this->type=type;
	this->team=team;
	isCastle=false;
	animation=false;
	this->num=num;
	h=0;

	piece = mapObjects[type];
	if(type.compare("castle")==0)
		isCastle=true;
	

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
		if(!animation)
			//glTranslated(55-5*x,0+h,-55+5*y);
			glTranslated(55-5*x,0+h,-55+5*y);
		else{
			animation=ani->apply();
			if(animation==false){
				x=newx;
				y=newy;
			}
			glTranslated(55-5*x,0+h,-55+5*y);
		}
		if(team=='a')
				piece->draw(1);
		else if(team=='b')
				piece->draw(0);
		else if(team=='v')
				piece->draw(3);

		glPopName();
	glPopMatrix();

}

void Peca::setX(double x){
	this->x=x;
}

void Peca::setY(double y){
	this->y=y;
}


