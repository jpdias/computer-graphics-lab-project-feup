#ifndef CLOCK_H
#define CLOCK_H

#include "Clock.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFappearance.h"


class Clock{
	public:
		Clock();
		void draw();

	public: 
		double elapsed,oldt,newt,min,sec;
		int timer;
		bool count;
		char minute[3];
		char second[3];
};

#endif