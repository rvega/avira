#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"

class AnimacionAbira: public Animacion{
   public:
      explicit AnimacionAbira(float x, float y);
      virtual ~AnimacionAbira();
};
