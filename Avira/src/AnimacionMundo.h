#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"


class AnimacionMundo: public Animacion{
   public:
      explicit AnimacionMundo(float x, float y);
      virtual ~AnimacionMundo();
};
