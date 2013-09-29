#include "Animacion.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
Animacion::Animacion(float x, float y):
fps(12),
loop(true),
playing(false),
relativoAPersona(false),
x(x),
y(y),
xPersona(x),
yPersona(y),
xOffset(0.0),
yOffset(0.0),
height(0),
width(0.1),
fullscreen(false),
frameIndex(0)
{
   ofRegisterGetMessages(this);
}

Animacion::~Animacion(){
   ofUnregisterGetMessages(this);

   cargadorImagenes.stopThread();

   for(unsigned int i = 0; i < animaciones.size(); i++) {
      delete animaciones.at(i);
   }
}


//===========//
//  SETTERS  //
//===========//
void Animacion::setPath(string val){
   ofDirectory directorio;
   directorio.listDir(val);
   directorio.sort();
   imagenes.resize( directorio.numFiles() );
   for(int i=0; i < directorio.numFiles(); ++i) {
      cargadorImagenes.loadFromDisk(imagenes[i], directorio.getPath(i));
   }

   sleep(1);
   if(imagenes.size() > 0){
      float proporcion = (float)imagenes.at(0).width / (float)imagenes.at(0).height;
      height = width / proporcion;
   }
}

float Animacion::getX(){
   return x;
}

float Animacion::getY(){
   return y;
}

void Animacion::setX(float val){
   x = val;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setX(val);
   }
}

void Animacion::setY(float val){
   y = val;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setY(val);
   }
}

void Animacion::setXPersona(float val){
   xPersona = val;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setXPersona(val);
   }
}

void Animacion::setYPersona(float val){
   yPersona = val;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setYPersona(val);
   }
}


//===========================================//
//  MENSAJES QUE LLEGAN DESDE OTROS OBJETOS  //
//===========================================//
void Animacion::gotMessage(ofMessage& msg){
   if(msg.message == "FULLSCREEN_ON"){
      fullscreen = true;
   }
   else if(msg.message == "FULLSCREEN_OFF"){
      fullscreen = false;
   }
}

void Animacion::play(){
   frameIndex = 0;
   startTime = ofGetElapsedTimef();
   playing = true;
}

void Animacion::stop(){
   playing = false;
   for(unsigned int i = 0; i < animaciones.size(); i++) {
      animaciones.at(i)->stop();
   }
}


//========//
//  DRAW  //
//========//
void Animacion::drawImagen(){
   if(imagenes.size() == 0) return;

   float time = ofGetElapsedTimef() - startTime;
   frameIndex = (unsigned int)(time * (float)fps) % imagenes.size();

   // pare al final.
   if(!loop && (frameIndex == (imagenes.size()-1))){
      playing = false;
      frameIndex = imagenes.size()-1;
   }

   int imgX, imgY, imgH, imgW;
   if(fullscreen){
      if(relativoAPersona){
         imgX = (xPersona+xOffset) * VENTANA_WIDTH;
         imgY = (yPersona+yOffset) * VENTANA_HEIGHT;
      }
      else{
         imgX = (x+xOffset) * VENTANA_WIDTH;
         imgY = (y+yOffset) * VENTANA_HEIGHT;
      }
      imgW = width * VENTANA_WIDTH;
      imgH = height * VENTANA_WIDTH; // Yes, width is ok, (height is initially calculated based on width)
   }
   else{
      if(relativoAPersona){
         imgX = POSICION_3_X + ((xPersona+xOffset) * IMAGEN_PEQUENA_WIDTH);
         imgY = POSICION_3_Y + ((yPersona+yOffset) * IMAGEN_PEQUENA_HEIGHT);
      }
      else{
         imgX = POSICION_3_X + ((x+xOffset) * IMAGEN_PEQUENA_WIDTH);
         imgY = POSICION_3_Y + ((y+yOffset) * IMAGEN_PEQUENA_HEIGHT);
      }

      imgW = width * IMAGEN_PEQUENA_WIDTH;
      imgH = height * IMAGEN_PEQUENA_WIDTH;
   }
   imagenes[frameIndex].draw(imgX, imgY, imgW, imgH);
}

void Animacion::drawSubAnimaciones(){
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->draw();
   }
}

void Animacion::draw(){
   if(playing){
      drawImagen();
      drawSubAnimaciones();
   }
}
