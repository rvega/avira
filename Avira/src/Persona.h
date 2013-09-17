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
      void setColor(float r, float g, float b);
      ofColor getColor();

   private:
      ofColor color;
      // Persona(const Persona&);
      // Persona& operator=(const Persona&);
};
