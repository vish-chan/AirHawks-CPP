#include "MainMenu.h"
#include "cGame.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/ButtonWidget.h"

using namespace FrameworkX;

MainMenu::MainMenu(cGame* theApp)
{
   mApp = theApp;

   mWidgetFlagsMod.mAddFlags |= WIDGETFLAGS_MARK_DIRTY;  //make mainmenu dirty each frame

//*********Single player button***********
   mSinglePlayer = new ButtonWidget(1, this);
   mSinglePlayer->SetFont(FONT_DEFAULT);
   mSinglePlayer->mLabel = _S("Single Player");
   
   int Bwidth=FONT_DEFAULT->StringWidth(mSinglePlayer->mLabel);
   int Bheight=FONT_DEFAULT->GetHeight();
   
   mSinglePlayer->Resize(mApp->mWidth/2-Bwidth/2, 240, Bwidth+10, Bheight+5);
   mSinglePlayer->mOverImage = IMAGE_BUTTON_OVER;
   mSinglePlayer->mDownImage = IMAGE_BUTTON_DOWN;
   mSinglePlayer->mButtonImage = IMAGE_BUTTON_NORMAL;
   AddWidget(mSinglePlayer);

////********VS mode button****************
//   mVS = new ButtonWidget(2, this);
//   mVS->SetFont(FONT_DEFAULT);
//   mVS->mLabel = _S("Versus Mode");
//   
//   Bwidth=FONT_DEFAULT->StringWidth(mVS->mLabel);
//   
//   mVS->Resize(mApp->mWidth/2-Bwidth/2, 240+Bheight+10, Bwidth+10, Bheight+5);
//   mVS->mOverImage = IMAGE_BUTTON_OVER;
//   mVS->mDownImage = IMAGE_BUTTON_DOWN;
//   mVS->mButtonImage = IMAGE_BUTTON_NORMAL;
//   AddWidget(mVS);

//*********Instructions button**********
  /* mInstructions = new ButtonWidget(3, this);
   mInstructions->SetFont(FONT_DEFAULT);
   mInstructions->mLabel = _S("Instructions");
   
   int Bwidth=FONT_DEFAULT->StringWidth(mInstructions->mLabel);
   int Bheight=FONT_DEFAULT->GetHeight();
   
   mInstructions->Resize(mApp->mWidth/2-Bwidth/2, 240+2*Bheight+10, Bwidth+10, Bheight+5);
   mInstructions->mOverImage = IMAGE_BUTTON_OVER;
   mInstructions->mDownImage = IMAGE_BUTTON_DOWN;
   mInstructions->mButtonImage = IMAGE_BUTTON_NORMAL;
   AddWidget(mInstructions);*/

//********Options Button***************
   mOptions = new ButtonWidget(4, this);
   mOptions->SetFont(FONT_DEFAULT);
   mOptions->mLabel = _S("Options");
   
   Bwidth=FONT_DEFAULT->StringWidth(mOptions->mLabel);
   Bheight=FONT_DEFAULT->GetHeight();
   
   mOptions->Resize(mApp->mWidth/2-Bwidth/2, 240+3*Bheight+10, Bwidth+10, Bheight+5);
   mOptions->mOverImage = IMAGE_BUTTON_OVER;
   mOptions->mDownImage = IMAGE_BUTTON_DOWN;
   mOptions->mButtonImage = IMAGE_BUTTON_NORMAL;
   AddWidget(mOptions);

//*************Exit Button************ 
   mExit = new ButtonWidget(5, this);
   mExit->SetFont(FONT_DEFAULT);
   mExit->mLabel = _S("Exit");
   
   Bwidth=FONT_DEFAULT->StringWidth(mExit->mLabel);
   Bheight=FONT_DEFAULT->GetHeight();
   
   mExit->Resize(mApp->mWidth/2-Bwidth/2, 240+4*Bheight+10, Bwidth+10, Bheight+5);
   mExit->mOverImage = IMAGE_BUTTON_OVER;
   mExit->mDownImage = IMAGE_BUTTON_DOWN;
   mExit->mButtonImage = IMAGE_BUTTON_NORMAL;
   AddWidget(mExit);

}


MainMenu::~MainMenu()
{
   RemoveAllWidgets();
   delete mSinglePlayer;
   /*delete mVS;*/
   /*delete mInstructions;*/
   delete mOptions;
   delete mExit;
}



void MainMenu::Draw(FrameworkX::Graphics *g)
{
   if (mApp->Is3DAccelerated())
      g->DrawImageF(IMAGE_MAIN_MENU,0,0);
   else
      g->DrawImage(IMAGE_MAIN_MENU,0,0);
}


void MainMenu::ButtonDepress(int theId)
{
   if(theId==1)
   {
      mApp->mWidgetManager->RemoveWidget(this);
      mApp->SafeDeleteWidget(this);
      mApp->InitialiseSinglePlayerBoard();
   }
   /*if(theId==2)
   {
      mApp->mWidgetManager->RemoveWidget(this);
      mApp->SafeDeleteWidget(this);
      mApp->InitializeVersusBoard();
   }*/
   /*if(theId==3)
   {
      mApp->InitializeInstructionsScreen();
   }*/
   if(theId==4)
   {
      mApp->InitialiseOptionsDialog();
   }
   if(theId==2)
   {
      mApp->mWidgetManager->RemoveWidget(this);
      mApp->SafeDeleteWidget(this);
      mApp->ExitApplication();
   }
}
