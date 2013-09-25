#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"


class AnimacionProbeta: public Animacion{
   public:
      explicit AnimacionProbeta(float x, float y);
      virtual ~AnimacionProbeta();
};
