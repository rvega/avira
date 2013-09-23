#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"

class AnimacionCabeza: public Animacion{
   public:
      explicit AnimacionCabeza(float x, float y);
      virtual ~AnimacionCabeza();
};
