#include "AnimacionCabeza.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionCabeza::AnimacionCabeza(float x, float y):
Animacion(x,y)
{ 
   // fps=5;
   width=0.15;
   setPath("animaciones/avira/cabeza");
}

AnimacionCabeza::~AnimacionCabeza(){ } 
