#pragma once

#include "Std.hpp"

class Hud {

private:
	Config *cfg;
	TwBar *myBar;

public:
	Hud(Config *cfg) 
		: cfg(cfg)
	{}

	void init(void) {

		if (TwInit(TW_OPENGL_CORE, NULL) == 0) {
			fprintf(stderr, "AntTweakBar error: %s", TwGetLastError());
		}
		else {
			this->myBar = TwNewBar("Parameters");

			TwWindowSize(this->cfg->WINDOW_WIDTH, this->cfg->WINDOW_HEIGHT);

			int boids = cfg->BOID_NUMBER_OF_BOIDS;
			TwAddVarRO(this->myBar, "Boids", TW_TYPE_INT32, &boids, " min = -1000 max = 1000 keyIncr = z keyDecr = Z ");

		}

	}

	void draw(void) const {
		TwDraw();
	}

};