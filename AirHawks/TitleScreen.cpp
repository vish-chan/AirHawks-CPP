#include "TitleScreen.h"
#include "cGame.h"
#include "Res.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/HyperlinkWidget.h"

using namespace FrameworkX;

TitleScreen::TitleScreen(cGame *theApp)
{
   mApp=theApp;
   
   (mWidgetFlagsMod).mAddFlags |= WIDGETFLAGS_MARK_DIRTY;
   
   //adding Hyperlink to titlescreen childwidget list
   mContinueLink = new HyperlinkWidget(1, this);
   mContinueLink->SetFont(FONT_DEFAULT);
   mContinueLink->mLabel = _S("CLICK TO CONTINUE");
   mContinueLink->mColor = Color(255, 255, 255);
   mContinueLink->mOverColor = Color(0, 255, 0);
   mContinueLink->mUnderlineSize = 1;
   int labelWidth = FONT_DEFAULT->StringWidth(mContinueLink->mLabel);
   int labelHeight = FONT_DEFAULT->GetHeight();
   mContinueLink->Resize(mApp->mWidth / 2 - labelWidth / 2, mApp->mHeight - labelHeight - 40, labelWidth, labelHeight+4);
   mContinueLink->mDoFinger = true;
   mContinueLink->SetVisible(false);
   mContinueLink->SetDisabled(true);
   AddWidget(mContinueLink);

}

TitleScreen::~TitleScreen()
{
   RemoveAllWidgets();
   delete mContinueLink;
}



void TitleScreen::Draw(Graphics *g)
{
	// for black/white,use Color::Black and Color::White.
	g->SetColor(Color::Black);
	g->FillRect(0, 0, mWidth, mHeight);
	int loaderBarWidth = IMAGE_LOADER_BAR->GetWidth();
	int drawWidth = (int) (mApp->GetLoadingThreadProgress() * (double)loaderBarWidth);
	if (drawWidth > 0)
	{
	   g->DrawImageF(IMAGE_LOADER_BAR, mWidth / 2 - loaderBarWidth / 2, 
	      400, 
	      Rect(0, 0, drawWidth, IMAGE_LOADER_BAR->GetHeight()));
	}

	// If our hyperlink widget is false, let's instead draw some
	// "Loading" text (er, actually in this case it's an image) where
	// it is located.
	if (mContinueLink->mVisible == false)
	{	g->DrawImage(IMAGE_LOADER_LOADINGTXT, mContinueLink->mX - 10, mContinueLink->mY - 80);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void TitleScreen::LoadingComplete()
{
	mContinueLink->SetVisible(true);
	mContinueLink->SetDisabled(false);
	
	
}

void TitleScreen::ButtonDepress(int theId)
{
	if (theId == 1)
	{
		mApp->mWidgetManager->RemoveWidget(this);
		mApp->SafeDeleteWidget(this);
		
		
		// Now let's tell the game app that it's ok to add the board widget:
		mApp->TitleScreenFinished();

	}
}

