#include "LinearAnimation.h"
#define PI (3.141592653589793)

#include <math.h>

LinearAnimation::LinearAnimation(vector<coordi> points,float span){
	this->span=span;
	this->points=points;
	flag=false;
	start=false;
	CalcVars();
}


void LinearAnimation::CalcVars(){

	float medium_speed_norm = 0;

	coordi speed;
	float angle,vec_x=cos(0.0),vec_z=sin(0.0),len1=1,len2,dotProduct;
	
	medium_speed.x = 0;
	medium_speed.y = 0;
	medium_speed.z = 0;

	for(size_t i=0; i<points.size()-1;i++) { // segment distance calc
		speed.x =  points[i+1].x-points[i].x;
		speed.y =  points[i+1].y-points[i].y;
		speed.z =  points[i+1].z-points[i].z;

		velocities.push_back(speed);

		medium_speed_norm += sqrt(speed.x*speed.x + speed.y*speed.y + speed.z*speed.z);

	}

	for(size_t i=0; i<velocities.size();i++) { 
		dotProduct = (velocities[i].x)*(vec_x) + (velocities[i].z)*(vec_z);

		len2 = sqrt((velocities[i].x)*((velocities[i].x)) + (velocities[i].z)*(velocities[i].z));

		if((len1*len2) == 0)
			angle = 0;
		else
			angle = acos(dotProduct/(len1*len2));

		angle *= 180.0/PI;
		if(velocities[i].z > 0)
			angle *= -1.0;

		angles.push_back(angle);

	}

	medium_speed_norm /= span;

	float prev_dt=0,dt=0;
	
	for(size_t i=0; i<velocities.size();i++) { 
		prev_dt += dt;
		dt = sqrt(velocities[i].x*velocities[i].x + velocities[i].y*velocities[i].y + velocities[i].z*velocities[i].z)/medium_speed_norm;

		velocities[i].x /= dt;
		velocities[i].y /= dt;
		velocities[i].z /= dt;

		dts.push_back(dt+prev_dt);
	}

}

coordi LinearAnimation::getCoordi() {
	int index=-1;
	coordi p;
	float elap = elapsed/1000.0;

	for(size_t i=0; i<dts.size();i++) {
		if(elap <= dts[i]) {
			index = i;
			break;
		}
	}
	if(index == -1) {
		p.x = 0;
		p.y = 0;
		p.z = 0;
		Animation::elapsed=0;
		translate.x = 0;
		translate.y = 0;
		translate.z = 0;
		start=true;
	}
	else {
		p.x = velocities[index].x * dt;
		p.y = velocities[index].y * dt;
		p.z = velocities[index].z * dt;

	}
	if(elap != elapsed_p) {
		elapsed_p = elap;
		translate.x += p.x;
		translate.y += p.y;
		translate.z += p.z;
	}
	return translate;
}

float LinearAnimation::getAngle() {
	int index=-1;
	float elap = elapsed/1000.0;

	for(size_t i=0; i<dts.size();i++) {
		if(elap <= dts[i]) {
			index = i;
			break;
		}
	}
	if(index == -1)
		return angles[dts.size()-1];

	return angles[index];
}

bool LinearAnimation::apply() {
	
	coordi animation = getCoordi();
	//float angle = getAngle();
	
	if(start){
		if ((animation.x==0) &&
			(animation.y==0) &&
			(animation.z==0) && flag){
			Animation::go=false;
			return false;
		}
		
		glTranslatef(animation.x,animation.y,animation.z);

		flag=true;

	}
		return true;
	
	
	
}

