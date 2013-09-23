#include "Persona.h"
#include "constantes.h"

Persona::Persona():
x(0), y(0), height(0), width(0), activa(false)
{ }

Persona::~Persona(){}

void Persona::setBorderColor(float r, float g, float b){
   color.r = r;
   color.g = g;
   color.b = b;
}

void Persona::drawBorder(){
   ofPushStyle();
   ofNoFill();
   ofSetColor(color);
   float x,y,w,h;
   x = POSICION_6_X + (this->x * IMAGEN_PEQUENA_WIDTH);
   y = POSICION_6_Y + (this->y * IMAGEN_PEQUENA_HEIGHT);
   w = width * IMAGEN_PEQUENA_WIDTH;
   h = height * IMAGEN_PEQUENA_HEIGHT;
   ofRect(x,y,w,h);
   ofPopStyle();
}
