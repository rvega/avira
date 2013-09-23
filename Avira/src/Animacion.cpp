#include "Animacion.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
Animacion::Animacion(float x, float y):
x(x), y(y), width(0.1), fps(10), fullscreen(false)
{
   ofRegisterGetMessages(this);
}

Animacion::~Animacion(){
   ofUnregisterGetMessages(this);

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
   playing = true;
}

void Animacion::stop(){
   // TODO: rewind
   playing = false;
}


//========//
//  DRAW  //
//========//
void Animacion::drawImagen(){
   if(imagenes.size() == 0) return;

   int frameIndex = (int)(ofGetElapsedTimef() * fps) % imagenes.size();
   int imgX, imgY, imgH, imgW;
   if(fullscreen){
      imgX = x * VENTANA_WIDTH;
      imgY = y * VENTANA_HEIGHT;
      imgW = width * VENTANA_WIDTH;
      imgH = height * VENTANA_WIDTH; // Yes, width is ok, (height is initially calculated based on width)
   }
   else{
      imgX = POSICION_6_X + (x * IMAGEN_PEQUENA_WIDTH);
      imgY = POSICION_6_Y + (y * IMAGEN_PEQUENA_HEIGHT);
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
