#include "AnimacionMapa.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionMapa::AnimacionMapa(float x, float y):
Animacion(x,y)
{ 
   fps=15;
   width=0.15;
   setPath("animaciones/accesorios/mapa");
}

AnimacionMapa::~AnimacionMapa(){ } 


