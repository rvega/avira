#pragma once
#include "ofMain.h"

class Persona{
   public:
      explicit Persona();
      virtual ~Persona();
      void setBorderColor(float r, float g, float b);
      void drawBorder();
      void setActiva(bool val);
      bool getActiva();
      bool getQuieta();
      void setDimensions(float newX, float newY, float newW, float newH);
      float getY();
      float getX();

   private:
      float x;
      float y;
      float height;
      float width;      
      bool activa;
      bool quieta;
      ofColor color;
      float startTime;
};
