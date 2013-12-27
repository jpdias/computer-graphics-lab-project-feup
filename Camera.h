#include "Camera.h"

Camera::Camera() {}
Camera::Camera(string id) {
	this->id = id;
}

char* Camera::getID() {
	char* cameraID = (char *) malloc(sizeof(char)*(id.size()));
	strcpy(cameraID,id.c_str());
	return cameraID;
}

void Camera::updateProjectionMatrix(int width, int height)	 {}

void Camera::applyView() {}

Perspective::Perspective(string id,float near,float far,float angle,float x1,float y1, float z1, float x2, float y2, float z2){
	this->near = near;
	this->far = far;
	this->angle = angle;
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->id=id;
}

void Perspective::updateProjectionMatrix(int width, int height)	 {
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,CGFapplication::xy_aspect,near,far);

}

void Perspective::applyView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x1,y1,z1,x2,y2,z2,0,1,0);
}

Ortho::Ortho(string id,float near,float far,float top,float bottom,float left,float right){
	this->near = near;
	this->far = far;
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
	this->id=id;
}

void Ortho::updateProjectionMatrix(int width, int height)	 {
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left,right,bottom,top,near,far);
}

void Ortho::applyView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}