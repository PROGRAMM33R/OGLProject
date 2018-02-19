#pragma once

#include "Std.hpp"

namespace Hud {

	Config *_cfg;
	TwBar *myBar;

	void init(Config *cfg, float *frames, double *escapeDuration) {

		_cfg = cfg;

		if (TwInit(TW_OPENGL_CORE, NULL) == 0) {
			fprintf(stderr, "AntTweakBar error: %s", TwGetLastError());
		}
		else {
			myBar = TwNewBar("Parameters");

			//*escapeDuration = pow(*escapeDuration, 1);

			TwWindowSize(_cfg->WINDOW_WIDTH, _cfg->WINDOW_HEIGHT);

			TwAddVarRO(myBar, "FPS", TW_TYPE_FLOAT, frames, NULL);
			TwAddSeparator(myBar, "", NULL);

			TwAddVarRO(myBar, "Boids", TW_TYPE_INT32, &(_cfg->BOID_NUMBER_OF_BOIDS), NULL);
			TwAddVarRO(myBar, "Separation enabled", TW_TYPE_INT32, &(_cfg->SEPARATION_ENABLED), NULL);
			TwAddVarRO(myBar, "Alignment enabled", TW_TYPE_INT32, &(_cfg->ALIGNMENT_ENABLED), NULL);
			TwAddVarRO(myBar, "Cohesion enabled", TW_TYPE_INT32, &(_cfg->COHESION_ENABLED), NULL);
			TwAddVarRO(myBar, "Path finding enabled", TW_TYPE_INT32, &(_cfg->PATH_FINDING_ENABLED), NULL);
			TwAddVarRO(myBar, "Escape sensitivity", TW_TYPE_FLOAT, &(_cfg->ESCAPE_SENSITIVITY), NULL);

			TwAddSeparator(myBar, "", NULL);

			TwAddVarRO(myBar, "Escape sec", TW_TYPE_DOUBLE, escapeDuration, NULL);

		}

	}

	void draw(void) {
		TwDraw();
	}

};