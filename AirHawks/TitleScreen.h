#ifndef _TITLESCREEN_H_
#define _TITLESCREEN_H_

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"

namespace FrameworkX
{
   class cGame;
   class Graphics;
   class WidgetManager;
   class HyperlinkWidget;

   class TitleScreen: public Widget, public ButtonListener
   {
      private:
	cGame* mApp;
	HyperlinkWidget* mContinueLink;	

      public:
	 TitleScreen(cGame*);
	 ~TitleScreen();
	 void Draw(Graphics* g);
	 virtual void ButtonDepress(int);
	 void LoadingComplete();
   };
}




#endif 