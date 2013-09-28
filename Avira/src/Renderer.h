#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Persona.h"
#include "Animacion.h"

class Renderer{
   public:
      explicit Renderer();
      virtual ~Renderer();

      void gotMessage(ofMessage& msg);

      void drawInterimImages(vector<ofxCvImage*>);
      void drawOutputImage(ofxCvImage*);
      void drawAnimaciones(map<int, Persona> gente);

   private:
      bool fullscreen;
      bool playing;
      std::vector<Animacion*> animaciones;

      template<class imageType>
         void drawImage(int x, int y, string title, imageType *img);

      Renderer(const Renderer& other);
      Renderer& operator=(const Renderer& other);
};
