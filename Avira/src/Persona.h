#pragma once
#include "ofMain.h"

class Persona{
   public:
      explicit Persona();
      virtual ~Persona();
      float x;
      float y;
      float height;
      float width;      
      bool activa;
      void setBorderColor(float r, float g, float b);
      void drawBorder();


   private:
      ofColor color;
      // Persona(const Persona&);
      // Persona& operator=(const Persona&);
};
