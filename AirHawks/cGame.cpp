#include "cGame.h"
#include "TitleScreen.h"
#include "Board.h"
#include "MainMenu.h"
#include "OptionsDialog.h"
#include "Res.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/SWTri.h"

#include "SexyAppFramework/Checkbox.h"

// We will be accessing the resource manager in this demo, so include it's header
#include "SexyAppFramework/ResourceManager.h"

// Required for playing music
#include "SexyAppFramework/BassMusicInterface.h"

// Contains all the resources from the resources.xml file in our
// properties directory. See that file for more information.
#include "Res.h"
#include "SexyAppFramework/Dialog.h"

using namespace FrameworkX;

cGame::cGame()
{
   
	mProdName = "AirHawks";	
	mProductVersion = "1.0";	
	mTitle = StringToSexyStringFast("AirHawks: " +  mProductVersion);
	mRegKey = "PopCap\\SexyAppFramework\\AirHawks";
	mWidth = 800;
	mHeight = 600;
	mAutoEnable3D = true;
	mBoard = NULL;
	mTitleScreen = NULL;
	mMainMenu=NULL;
	/*mEndScreen = NULL;*/
	SWTri_AddAllDrawTriFuncs();
	mNoSoundNeeded=true; 
	
}

cGame::~cGame()
{
   if (mBoard != NULL)
      mWidgetManager->RemoveWidget(mBoard);
   delete mBoard;
   if (mTitleScreen != NULL)
      mWidgetManager->RemoveWidget(mTitleScreen);
   delete mTitleScreen;
   if (mMainMenu != NULL)
      mWidgetManager->RemoveWidget(mMainMenu);
   delete mMainMenu;
  
   
}


void cGame::Init()
{
   SexyAppBase::Init();
   LoadResourceManifest();
   if (!mResourceManager->LoadResources("Init"))
	{
		mLoadingFailed = true;
		ShowResourceError(true); //true if error in main thread
		return;
	}

   if (!ExtractInitResources(mResourceManager))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}

   if (!mResourceManager->LoadResources("TitleScreen"))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}
   if (!ExtractTitleScreenResources(mResourceManager))
	{
		mLoadingFailed = true;
		ShowResourceError(true);
		return;
	}

   mWidgetManager->mDefaultBelowModalFlagsMod.mRemoveFlags |= WIDGETFLAGS_UPDATE;

   mTitleScreen= new TitleScreen(this);
   mTitleScreen->Resize(0, 0, mWidth, mHeight);
   mWidgetManager->AddWidget(mTitleScreen);
   
   //for music 
   mMusicInterface->LoadMusic(0, "music/music.mo3");

   //for crossfading
   mMusicInterface->LoadMusic(1,"music/music.mo3");
   
   //to smoothly fadein the song
   mMusicInterface->FadeIn(0, 0, 0.002, false);
   
   //No. of resources for loading thread to display the loading bar
   mNumLoadingThreadTasks = mResourceManager->GetNumResources("Game");

}


void cGame::LoadingThreadProc()
{
   mResourceManager->StartLoadResources("Game");
   
   while(mResourceManager->LoadNextResource())
   {
      mCompletedLoadingThreadTasks++;  //tracks the no. of completed tasks and gives the percentage of loading bar
      if(mShutdown)                    //in case of error this variable is automatically set to True
	     return;
   }

   if (mResourceManager->HadError() || !ExtractGameResources(mResourceManager))
	{		
		ShowResourceError(false);
		mLoadingFailed = true;
		return;
	}
	
}


void cGame::LoadingThreadCompleted()
{
   SexyAppBase::LoadingThreadCompleted();
   
   if(mLoadingFailed)             //in case of error just return
      return;

   mTitleScreen->LoadingComplete();  // To display the Hyperlink
  (mTitleScreen->mWidgetFlagsMod).mAddFlags |= WIDGETFLAGS_MARK_DIRTY;
}



void cGame::TitleScreenFinished()
{  
   //remove titlescreen
   mTitleScreen = NULL;
   mResourceManager->DeleteResources("TitleScreen");
   
   //add mainmenu
   mMainMenu = new MainMenu(this);
   mMainMenu->Resize(0,0,mWidth,mHeight);
   mWidgetManager->AddWidget(mMainMenu);
   mWidgetManager->SetFocus(mMainMenu);
   
   //stop the intro song
   mMusicInterface->FadeOut(0);
   
   //fade in the main menu music
   mMusicInterface->FadeIn(1, 9, 0.002, false);

}

void cGame::SwitchScreenMode(bool wantWindowed, bool is3d)
{
	// Let the app handle the actual details of this call...
	SexyAppBase::SwitchScreenMode(wantWindowed, is3d);

	// We can see if the options dialog is up with a call to
	// GetDialog. You pass GetDialog the unique ID of the dialog box,
	// and if it exists it is returned to you, otherwise NULL is returned.
	OptionsDialog* d = (OptionsDialog*) GetDialog(OptionsDialog::DIALOG_ID);

	// Set the checkbox state to our windowed state
	if ((d != NULL) && (d->mFSCheckbox != NULL))      //in case user uses ALT+Return to switch screen mode
		d->mFSCheckbox->SetChecked(!wantWindowed);

}


void cGame::DialogButtonDepress(int dialog_id, int button_id)
{
   if(dialog_id==OptionsDialog::MESSAGE_BOX_ID)
      if(button_id == Dialog::ID_OK)
		  SexyAppBase::KillDialog(dialog_id);

   if(dialog_id==OptionsDialog::DIALOG_ID)
      if(button_id==Dialog::ID_FOOTER)
      {
		  SwitchScreenMode(!mOptions->mFSCheckbox->mChecked, mOptions->m3DCheckbox->mChecked);
		  SexyAppBase::KillDialog(dialog_id);
      }

}


void cGame::InitialiseSinglePlayerBoard()
{
   mMainMenu=NULL;
   mBoard = new Board(this);
   mBoard->Resize(0,0,mWidth,mHeight);
   mWidgetManager->AddWidget(mBoard);
   mWidgetManager->SetFocus(mBoard);
}

//void cGame::InitialiseVersusBoard()
//{
//   mMainMenu=NULL;
//   mBoardVersus = new BoardVersus(this);
//   mBoardVersus->Resize(0,0,mWidth,mHeight);
//   mWidgetManager->AddWidget(mBoardVersus);
//   mWidgetManager->SetFocus(mBoardVersus);
//}

//void cGame::InitialiseInstructionsScreen()
//{
//   mInstructions = new Instructions(this);
//   mInstructions->Resize(0,0,mWidth,mHeight);
//   mWidgetManager->AddWidget(mInstructions);
//   mWidgetManager->SetFocus(mInstructions);
//}


void cGame::InitialiseOptionsDialog()
{
   mOptions = new OptionsDialog("Options","Make some adjustments");
   mOptions->Resize(100,100,300,400);
   AddDialog(OptionsDialog::DIALOG_ID,mOptions);
}
