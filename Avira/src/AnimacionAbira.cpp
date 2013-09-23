#include "AnimacionAbira.h"
#include "constantes.h"

//=======================//
//  SETUP Y DESTRUCCION  //
//=======================//
AnimacionAbira::AnimacionAbira(float x, float y):
Animacion(x,y)
{ 
   fps=5;
   width=0.4;
   setPath("animaciones/abira/abiraAnim");
}

AnimacionAbira::~AnimacionAbira(){ } 


