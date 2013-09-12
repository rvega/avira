#include "Renderer.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
Renderer::Renderer():
   fullscreen(false)
{
   ofRegisterGetMessages(this);
}

Renderer::~Renderer() {
   ofUnregisterGetMessages(this);
}

//===========//
//  SETTERS  //
//===========//
void Renderer::setTitle1(string val){
   title1 = val;
}

// void Renderer::setTitle2(string val){
//    title2 = val;
// }
// 
// void Renderer::setTitle3(string val){
//    title3 = val;
// }
// 
void Renderer::setImgOutput(ofxCvColorImage val){
   imgOutput = val;
}

void Renderer::setImg1(ofxCvGrayscaleImage val){
   img1 = val;
}

// void Renderer::setImg2(ofxCvGrayscaleImage val){
//    img2 = val;
// }
// 
// void Renderer::setImg3(ofxCvGrayscaleImage val){
//    img3 = val;
// }

//===========================================//
//  MENSAJES QUE LLEGAN DESDE OTROS OBJETOS  //
//===========================================//
void Renderer::gotMessage(ofMessage& msg){
   if(msg.message == "FULLSCREEN_ON"){
      fullscreen = true;
   }
   else if(msg.message == "FULLSCREEN_OFF"){
      fullscreen = false;
   }
}

//========//
//  DRAW  //
//========//
template<class imageType>
void Renderer::drawImage(int x, int y, string title, imageType img){
   ofPushMatrix();
   ofTranslate(x, y);
   ofRect(0,0,IMAGEN_PEQUENA_WIDTH+2, IMAGEN_PEQUENA_HEIGHT+2);
   ofDrawBitmapString(title, 0, -5);
   img.draw(1, 1, IMAGEN_PEQUENA_WIDTH, IMAGEN_PEQUENA_HEIGHT);
   ofPopMatrix();
}

void Renderer::draw(){
   ofPushMatrix();
   ofSetColor(255,255,255);
   if(!fullscreen){
      drawImage<ofxCvGrayscaleImage>(POSICION_1_X, POSICION_1_Y, title1, img1);
      // drawImage(POSICION_2_X, POSICION_2_Y, "Fondo:", imgOutput);
      // drawImage(POSICION_3_X, POSICION_3_Y, "Fondo:", imgOutput);
      // drawImage(POSICION_4_X, POSICION_4_Y, "Fondo:", imgOutput);
      // drawImage(POSICION_5_X, POSICION_5_Y, "Fondo:", imgOutput);
      drawImage<ofxCvColorImage>(POSICION_6_X, POSICION_6_Y, "Output:", imgOutput);
   }
   else{
      imgOutput.draw(0, 0, IMAGEN_GRANDE_WIDTH, IMAGEN_GRANDE_HEIGHT);
   }
   ofPopMatrix();
}
