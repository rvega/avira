#pragma once
#include "ofMain.h"

class Persona{
   public:
      explicit Persona();
      virtual ~Persona();
      // Persona(const Persona&);
      // Persona& operator=(const Persona&);

      void setBorderColor(float r, float g, float b);
      void drawBorder();
      void setActiva(bool val);
      bool getActiva();
      bool getQuieta();
      void setDimensions(float newX, float newY, float newW, float newH);
      float getY();
      float getX();
      bool checked;
      int label;

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
