#include <iostream>
#include "aviraApp.h"
#include "Tracker.h"

Tracker::Tracker(){
   std::cout << "aaa" << "\n";
}

Tracker::~Tracker(){

}

void Tracker::setApp(aviraApp& theApp){
   app = theApp;
}

