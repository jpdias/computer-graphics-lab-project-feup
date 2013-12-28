#ifndef LINEARANIMATION_H
#define LINEARANIMATION_H
#include "Animation.h"
#include <math.h>
#include <vector>
#include <stdlib.h>
#include "CGFapplication.h"

using std::vector;

	typedef struct{
		float x,y,z;
	}coordi;

class LinearAnimation : Animation{
	public:
		
		vector<coordi> points;
		float span;
		
		void CalcVars();
		LinearAnimation(vector<coordi> ctrlpointList,float span);
		
		bool flag,start;
	string id;
	float elapsed_p;
	string type;
	vector<coordi> ctrlpoints;
	vector<coordi> velocities;
	vector<float> dts;
	vector<float> angles;
	coordi medium_speed;
	coordi translate;
	
coordi getCoordi();
	float getAngle();

	bool apply();
};

#endif