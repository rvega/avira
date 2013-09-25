#include "Persona.h"
#include "constantes.h"
#include "ofMain.h"

Persona::Persona():
x(0), y(0), height(0), width(0), activa(false), quieta(false)
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
   x = POSICION_5_X + (this->x * IMAGEN_PEQUENA_WIDTH);
   y = POSICION_5_Y + (this->y * IMAGEN_PEQUENA_HEIGHT);
   w = width * IMAGEN_PEQUENA_WIDTH;
   h = height * IMAGEN_PEQUENA_HEIGHT;
   ofRect(x,y,w,h);

   x = POSICION_6_X + (this->x * IMAGEN_PEQUENA_WIDTH);
   y = POSICION_6_Y + (this->y * IMAGEN_PEQUENA_HEIGHT);
   ofRect(x,y,w,h);

   ofPopStyle();
}

bool Persona::getQuieta(){
   return quieta;
}

bool Persona::getActiva(){
   return activa;
}

void Persona::setActiva(bool val){
   activa=val;
}

float Persona::getY(){
   return y;
}

float Persona::getX(){
   return x;
}

void Persona::setDimensions(float newX, float newY, float newW, float newH){
   // Solo personas en la mitad de abajo del cuadro y
   // quietas mas de 1 seg
   if(newY > 0.4){
      float dist = pow(x-newX,2) + pow(y-newY,2);
      if(dist <= 0.0002){
         float time = ofGetElapsedTimef();
         if(time - startTime >= 1.0){
            quieta=true;
         }
         else{
            quieta=false;
         }
      }
      else{
         startTime = ofGetElapsedTimef();
         quieta=false;
      }
   }

   x = newX;
   y = newY;
   width = newW;
   height = newH;
}
