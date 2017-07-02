#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"
#include "Res.h"

namespace FrameworkX
{
   class cGame;
   class Graphics;
   class WidgetManager;
   class ButtonWidget;

   class MainMenu:public Widget, public ButtonListener
   {
   protected:
      ButtonWidget* mSinglePlayer;
      ButtonWidget* mVS;
      ButtonWidget* mInstructions;
      ButtonWidget* mOptions;
      ButtonWidget* mExit;
      cGame* mApp;

   public:
      MainMenu(cGame*);
      ~MainMenu();
      void Draw(Graphics* g);
      virtual void ButtonDepress(int theId);
   };
}

#endif