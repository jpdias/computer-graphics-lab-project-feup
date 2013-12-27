#ifndef CAMERA_H
#define CAMERA_H

#include "CGFcamera.h"
#include "CGFapplication.h"
#include <string>

class Camera : public CGFcamera{
protected:
	string id;

public:

	Camera();
	Camera(string id);
	char* getID();
	virtual void updateProjectionMatrix(int width, int height);	
	virtual void applyView();

};

class Perspective : public Camera{	
private:
	float near, far, angle, x1, y1, z1, x2, y2, z2;
public:
	Perspective(string id,float near,float far,float angle,float x1,float y1, float z1, float x2, float y2, float z2);
	void updateProjectionMatrix(int width, int height);	
	void applyView();
	int state;

};

class Ortho : public Camera{
private:
	float near, far, top, bottom, left, right;

public:
	Ortho(string id,float near,float far,float top,float bottom,float left,float right);
	void updateProjectionMatrix(int width, int height);	
	void applyView();
	int state;
};



#endif