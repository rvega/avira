#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class Renderer{
   public:
      explicit Renderer();
      virtual ~Renderer();
      void gotMessage(ofMessage& msg);
      void setTitle1(string val);
      void setTitle2(string val);
      void setTitle3(string val);
      void setTitle4(string val);
      void setTitle5(string val);
      void setImgOutput(ofxCvColorImage val);
      void setImg1(ofxCvGrayscaleImage val);
      // void setImg2(ofxCvGrayscaleImage val);
      // void setImg3(ofxCvGrayscaleImage val);
      // void setImg4(ofxCvGrayscaleImage val);
      // void setImg5(ofxCvGrayscaleImage val);
      void draw();

   private:
      bool fullscreen;
      string title1;
      // string title2;
      // string title3;
      // string title4;
      // string title5;
      ofxCvGrayscaleImage img1;
      // ofxCvGrayscaleImage img2;
      // ofxCvGrayscaleImage img3;
      // ofxCvGrayscaleImage img4;
      // ofxCvGrayscaleImage img5;
      ofxCvColorImage imgOutput;
      template<class imageType>
         void drawImage(int x, int y, string title, imageType img);
      void drawImage(int x, int y, string title, ofxCvColorImage img);
      Renderer(const Renderer& other);
      Renderer& operator=(const Renderer& other);
};
