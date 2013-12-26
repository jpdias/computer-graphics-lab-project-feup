#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "DemoScene.h"
#include "Tabuleiro.h"
class TPinterface: public CGFinterface {
	public:
		TPinterface();

		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]); 

};


#endif
