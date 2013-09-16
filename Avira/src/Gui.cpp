#include "Gui.h"
#include "constantes.h"

Gui::Gui():
   fullscreen(false),

   // Invoca el constructor de ofxUI para la variable gui:
   gui(GUI_POS_X, GUI_POS_Y, GUI_WIDTH, 0)
{}

Gui::~Gui(){}

void Gui::setup(){
   gui.addLabel("Opciones", OFX_UI_FONT_MEDIUM);
   gui.setWidgetFontSize(OFX_UI_FONT_SMALL);
   gui.addSpacer(GUI_WIDTH,1);
   ofColor bgColor = ofColor(50, 50, 50);
   gui.setColorBack(bgColor);
   gui.addButton("Usar Camara", true);
   gui.addButton("Usar Pelicula", true);
   gui.addButton("Capturar Fondo", true);
   gui.addButton("Pantalla Completa", true);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.addSlider("Threshold", 0, 100, THRESHOLD_DEFAULT);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.autoSizeToFitWidgets();

   ofAddListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
}

void Gui::exit(){
   ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   ofRemoveListener(gui.newGUIEvent, this, &Gui::guiEvent);
}

void Gui::guiEvent(ofxUIEventArgs &e) {
   if(e.widget->getName()=="Threshold") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("THRESHOLD " + ofToString(value) );
      return;
   }

   bool value = ((ofxUIButton*)(e.widget))->getValue();
   if(e.widget->getName()=="Pantalla Completa" && value) {
      fullscreen = true;
      gui.setVisible(false);
      ofSendMessage("FULLSCREEN_ON");
   }
   else if(e.widget->getName()=="Capturar Fondo" && value) {
      ofSendMessage("CAPTURAR_FONDO");
   }
   else if(e.widget->getName()=="Usar Camara" && value) {
      ofSendMessage("USAR_CAMARA");
   }
   else if(e.widget->getName()=="Usar Pelicula" && value) {
      ofSendMessage("USAR_PELICULA");
   }
}

void Gui::mousePressed(ofMouseEventArgs& data){
   if(fullscreen){
      fullscreen = false;
      gui.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}

void Gui::keyPressed(ofKeyEventArgs& data){
   if(fullscreen){
      fullscreen=false;
      gui.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}
