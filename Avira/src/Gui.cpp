#include "Gui.h"
#include "constantes.h"

Gui::Gui():
   fullscreen(false),

   // Invoca el constructor de ofxUI para la variable gui:
   gui(GUI_POS_X, GUI_POS_Y, GUI_WIDTH, 0),
   gui2(GUI_POS_X+GUI_WIDTH+8, GUI_POS_Y+18, GUI_WIDTH*2, 0),
   gui3(GUI_POS_X+3*GUI_WIDTH+8, GUI_POS_Y+18, GUI_WIDTH*2, 0)
{}

Gui::~Gui(){}

void Gui::setup(){
   gui.setWidgetFontSize(OFX_UI_FONT_SMALL);
   gui2.setWidgetFontSize(OFX_UI_FONT_SMALL);
   gui3.setWidgetFontSize(OFX_UI_FONT_SMALL);

   gui.addButton("Usar Camara", true);
   gui.addButton("Usar Pelicula", true);
   gui.addButton("Capturar Fondo", true);
   gui.addButton("Pantalla Completa", true);
   gui.autoSizeToFitWidgets();

   gui2.addSlider("Threshold", THRESHOLD1_MIN, THRESHOLD1_MAX, THRESHOLD_DEFAULT);
   gui2.addSlider("Blur", BLUR_MIN, BLUR_MAX, BLUR_DEFAULT);
   gui2.addSlider("Threshold2", THRESHOLD2_MIN, THRESHOLD2_MAX, THRESHOLD_DEFAULT);
   gui2.addSlider("Tamanho Minimo", SLIDER_TAMANO_MIN_LEFT, SLIDER_TAMANO_MIN_RIGHT, SLIDER_TAMANO_DEFAULT);
   gui2.addSlider("Tamanho Maximo", SLIDER_TAMANO_MAX_LEFT, SLIDER_TAMANO_MAX_RIGHT, SLIDER_TAMANO_DEFAULT);
   gui2.autoSizeToFitWidgets();

   gui3.addSlider("Frame Counter", 1.0, 30.0, 5.0);
   gui3.addButton("Play/Pausa", true);
   gui3.addSlider("Posicion Pelicula", 0.0, 1.0, 0.0);
   gui3.autoSizeToFitWidgets();

   ofAddListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(gui2.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(gui3.newGUIEvent, this, &Gui::guiEvent);

   ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   
   gui2.loadSettings("settings2.xml");
   gui3.loadSettings("settings3.xml");
}

void Gui::exit(){
   gui2.saveSettings("settings2.xml");
   gui3.saveSettings("settings3.xml");

   ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   ofRemoveListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofRemoveListener(gui2.newGUIEvent, this, &Gui::guiEvent);
   ofRemoveListener(gui3.newGUIEvent, this, &Gui::guiEvent);
}

void Gui::guiEvent(ofxUIEventArgs &e) {
   if(e.widget->getName()=="Threshold") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("THRESHOLD1 " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Threshold2") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("THRESHOLD2 " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Tamanho Minimo") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("TAMANO_MINIMO " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Blur") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("BLUR " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Posicion Pelicula") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("POSICION_PELICULA " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Tamanho Maximo") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("TAMANO_MAXIMO " + ofToString(value) );
      return;
   }

   if(e.widget->getName()=="Frame Counter") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("FRAME_COUNTER " + ofToString(value) );
      return;
   }

   bool value = ((ofxUIButton*)(e.widget))->getValue();
   if(e.widget->getName()=="Pantalla Completa" && value) {
      fullscreen = true;
      gui.setVisible(false);
      gui2.setVisible(false);
      gui3.setVisible(false);
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
   else if(e.widget->getName()=="Play/Pausa" && value) {
      ofSendMessage("PLAY");
   }
}

void Gui::mousePressed(ofMouseEventArgs& data){
   if(fullscreen){
      fullscreen = false;
      gui.setVisible(true);
      gui2.setVisible(true);
      gui3.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}

void Gui::keyPressed(ofKeyEventArgs& data){
   if(fullscreen){
      fullscreen=false;
      gui.setVisible(true);
      gui2.setVisible(true);
      ofSendMessage("FULLSCREEN_OFF");
   }
}
