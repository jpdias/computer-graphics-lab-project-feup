#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "DemoScene.h"
#include "Tabuleiro.h"
#include "Peca.h"
#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
class TPinterface: public CGFinterface {
	public:
		TPinterface();
		SOCKET m_socket;
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]); 
		bool socketConnect();
		void envia(char *s, int len);
		void recebe(char *ans);
		void quit();
		int getDirection(int newx,int newy, int oldx, int oldy,int *space);
};


#endif
