#pragma once
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "Animacion.h"

class AnimacionMunecoAvira: public Animacion{
   public:
      explicit AnimacionMunecoAvira(float x, float y);
      virtual ~AnimacionMunecoAvira();
};
