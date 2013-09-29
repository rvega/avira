#include "AnimacionEscenaPajaro.h"
#include "AnimacionPajaro.h"
#include "AnimacionMundo.h"
#include "AnimacionBurbujas.h"
#include "AnimacionProbeta.h"
#include "AnimacionCabeza.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionEscenaPajaro::AnimacionEscenaPajaro(float x, float y):
Animacion(x,y)
{
   complete = false;
   estado = "STOP";

   AnimacionPajaro* pajaro = new AnimacionPajaro(0,0);
   animaciones.push_back(pajaro);

   AnimacionMundo* mundi = new AnimacionMundo(0,0);
   animaciones.push_back(mundi);

    AnimacionMundo* mundi_concecuente = new AnimacionMundo(0,0);
    mundi_concecuente->relativoAPersona = true;
    animaciones.push_back(mundi_concecuente);

    AnimacionProbeta* probeta = new AnimacionProbeta(0,0);
    animaciones.push_back(probeta);

    AnimacionBurbujas* burbujas = new AnimacionBurbujas(0,0);
    burbujas->relativoAPersona = true;
    animaciones.push_back(burbujas);

    setCualAccesorio("probeta");
}

void AnimacionEscenaPajaro::setCualAccesorio(string val){
    if(val == "probeta"){
        accesorio = animaciones.at(3);
        consecuencia = animaciones.at(4);
    }
    else if(val=="mundo"){
        accesorio = animaciones.at(1);
        consecuencia = animaciones.at(2);
    }
}


void AnimacionEscenaPajaro::play(){
   estado = "PAJARO_VOLANDO";
   complete = false;
   animaciones.at(0)->play();
   accesorio->stop();
   consecuencia->stop();

   Animacion::play();
}

void AnimacionEscenaPajaro::draw(){
    if(estado == "PAJARO_VOLANDO"){
        // if pajaro cerca de persona
        if(abs((animaciones.at(0)->getX() - xPersona)) < 0.1){
            accesorio->setX( animaciones.at(0)->getX() + 0.05 );
            accesorio->setY( animaciones.at(0)->getY() + 0.1 );
            accesorio->setXPersona( xPersona );
            accesorio->setYPersona( yPersona );
            accesorio->play();
            estado = "ACCESORIO_CAYENDO";
        }
    }
    if(estado == "ACCESORIO_CAYENDO"){
        if( accesorio->isComplete() ){
            consecuencia->play();
            accesorio->stop();
            timer = ofGetElapsedTimef();
            estado = "ACCESORIO_CONSECUENCIA";
        }
    }
    if(estado == "ACCESORIO_CONSECUENCIA"){
        consecuencia->setXPersona(xPersona);
        consecuencia->setYPersona(yPersona);
        if(ofGetElapsedTimef() - timer > 6) {
            consecuencia->stop();
            animaciones.at(0)->stop();
            stop();
            complete = true;
            estado == "STOP";
        }
    }

   Animacion::draw();
}

bool AnimacionEscenaPajaro::isComplete(){
    return complete;
}

void AnimacionEscenaPajaro::setX(float val){
   x = 0;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setX(0);
   }
}

void AnimacionEscenaPajaro::setY(float val){
   y = 0;
   for(unsigned int i=0; i<animaciones.size(); i++){
      animaciones.at(i)->setY(0);
   }
}
