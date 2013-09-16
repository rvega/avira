#pragma once
#include "ofMain.h"

class Persona{
   public:
      explicit Persona();
      virtual ~Persona();
      int x;
      int y;
      int height;
      int width;      
      void setColor(int r, int g, int b);
      ofColor getColor();

   private:
      ofColor color;
      // Persona(const Persona&);
      // Persona& operator=(const Persona&);
};
