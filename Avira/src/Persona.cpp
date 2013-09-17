#include "Persona.h"

Persona::Persona(){
   activa = false;
   x=0;
   y=0;
   width=0;
   height=0; 
}

Persona::~Persona(){}

void Persona::setColor(float r, float g, float b){
   color.r = r;
   color.g = g;
   color.b = b;
}

ofColor Persona::getColor(){
   return color;
}
