#include "Persona.h"
#include "constantes.h"
#include "ofMain.h"

Persona::Persona():
checked(false), x(0), y(0), height(0), width(0), activa(false), quieta(false), startTime(0)
{ }

Persona::~Persona(){}

// Persona::Persona(const Persona& other):
// x(other.x), y(other.y), height(other.height), width(other.width), activa(other.activa), quieta(other.quieta), color(other.color), startTime(other.startTime)
// {
//    ofLogNotice() << "Pesona copy constructor";
// }
// 
// Persona& Persona::operator=(const Persona& other){
//    ofLogNotice() << "Pesona assignment operatorr";
// 
//    x = other.x;
//    y = other.y;
//    height = other.height;
//    width = other.width;
//    activa = other.activa;
//    quieta = other.quieta;
//    color = other.color;
//    startTime = other.startTime;
// 
//    return *this;
// }

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
   x = POSICION_2_X + (this->x * IMAGEN_PEQUENA_WIDTH);
   y = POSICION_2_Y + (this->y * IMAGEN_PEQUENA_HEIGHT);
   w = width * IMAGEN_PEQUENA_WIDTH;
   h = height * IMAGEN_PEQUENA_HEIGHT;
   ofDrawBitmapString(ofToString(label), x+3, y-3);
   ofRect(x,y,w,h);

   x = POSICION_3_X + (this->x * IMAGEN_PEQUENA_WIDTH);
   y = POSICION_3_Y + (this->y * IMAGEN_PEQUENA_HEIGHT);
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
