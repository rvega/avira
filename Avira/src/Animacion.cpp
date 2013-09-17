#include "Animacion.h"

Animacion::Animacion(int x, int y, int fps):
x(x), y(y), fps(30)
{
   width=0;
   height=0;
}

Animacion::~Animacion(){}

void Animacion::setPath(string val){
   ofDirectory directorio;
   directorio.listDir(val);
   imagenes.resize( directorio.numFiles() );
   for(int i=0; i < directorio.numFiles(); ++i) {
      cargadorImagenes.loadFromDisk(imagenes[i], directorio.getPath(i));
   }
}

void Animacion::play(){
   playing = true;
}

void Animacion::stop(){
   // TODO: rewind
   playing = false;
}


void Animacion::draw(){
   ofPushMatrix();
   ofPushStyle();
   if(playing){
      int frameIndex = (int)(ofGetElapsedTimef() * fps) % imagenes.size();
      imagenes[frameIndex].draw(x,y);
   }
   ofPopStyle();
   ofPopMatrix();
}
