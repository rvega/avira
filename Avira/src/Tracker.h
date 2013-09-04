#pragma once

class aviraApp;

class Tracker{
   public:
      explicit Tracker();
      virtual ~Tracker();

      void setApp(aviraApp& app);
      void draw();
   
   private:
      aviraApp& app;

      Tracker(const Tracker&);
      Tracker& operator=(const Tracker&);
};
