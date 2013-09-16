#include "Persona.h"

Persona::Persona(){
   x=0;
   y=0;
   width=0;
   height=0; 
}

Persona::~Persona(){}

void Persona::setColor(int r, int g, int b){
   color.r = r;
   color.g = g;
   color.b = b;
}

ofColor Persona::getColor(){
   return color;
}
