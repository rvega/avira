#include "Gui.h"
#include "constantes.h"

Gui::Gui():
   fullscreen(false),

   // Invoca el constructor de ofxUI para la variable gui:
   gui(GUI_POS_X, GUI_POS_Y, GUI_WIDTH, 0),
   gui2(GUI_POS_X+GUI_WIDTH+8, GUI_POS_Y+18, GUI_WIDTH, 0)
{}

Gui::~Gui(){}

void Gui::setup(){
   // ofColor bgColor = ofColor(50, 50, 50);
   // gui.setColorBack(bgColor);
   // gui2.setColorBack(bgColor);

   gui.setWidgetFontSize(OFX_UI_FONT_SMALL);
   gui2.setWidgetFontSize(OFX_UI_FONT_SMALL);

   gui.addLabel("Opciones", OFX_UI_FONT_MEDIUM);
   gui.addSpacer(GUI_WIDTH,0);
   gui.addButton("Usar Camara", true);
   gui.addButton("Usar Pelicula", true);
   gui.addButton("Capturar Fondo", true);
   gui.addButton("Pantalla Completa", true);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.addSpacer(GUI_WIDTH, 0);
   gui.autoSizeToFitWidgets();

   gui2.addSpacer(GUI_WIDTH, 0);
   gui2.addSlider("Threshold", 0, 100, THRESHOLD_DEFAULT);
   gui2.addSlider("Tamanho Minimo", SLIDER_TAMANO_MIN_LEFT, SLIDER_TAMANO_MIN_RIGHT, SLIDER_TAMANO_DEFAULT);
   gui2.addSlider("Tamanho Maximo", SLIDER_TAMANO_MAX_LEFT, SLIDER_TAMANO_MAX_RIGHT, SLIDER_TAMANO_DEFAULT);
   gui2.addSlider("Blur", 1, 99, 1);
   gui2.autoSizeToFitWidgets();

   ofAddListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(gui2.newGUIEvent, this, &Gui::guiEvent);
   ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   
   gui.loadSettings("settings1.xml");
   gui2.loadSettings("settings2.xml");
}

void Gui::exit(){
   gui.saveSettings("settings1.xml");
   gui2.saveSettings("settings2.xml");

   ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
   ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
   ofRemoveListener(gui.newGUIEvent, this, &Gui::guiEvent);
   ofRemoveListener(gui2.newGUIEvent, this, &Gui::guiEvent);
}

void Gui::guiEvent(ofxUIEventArgs &e) {
   if(e.widget->getName()=="Threshold") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("THRESHOLD " + ofToString(value) );
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

   if(e.widget->getName()=="Tamanho Maximo") {
      float value = ((ofxUISlider*)(e.widget))->getScaledValue();
      ofSendMessage("TAMANO_MAXIMO " + ofToString(value) );
      return;
   }

   bool value = ((ofxUIButton*)(e.widget))->getValue();
   if(e.widget->getName()=="Pantalla Completa" && value) {
      fullscreen = true;
      gui.setVisible(false);
      gui2.setVisible(false);
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
      gui2.setVisible(true);
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
