#ifndef _CGAME_H_
#define _CGAME_H_

#include "SexyAppFramework/XAppBase.h"
#include <STDLIB.H>
namespace FrameworkX
{
   class Board;
   class TitleScreen;
   class MainMenu;
   class Instructions;
   class OptionsDialog;
   class EndScreen;

   class cGame:public SexyAppBase
   {
   private:
      Board* mBoard;
      TitleScreen* mTitleScreen;
 
      OptionsDialog* mOptions;
      
      MainMenu* mMainMenu;

   public:
      cGame();
      ~cGame();
      virtual void Init();
      virtual void LoadingThreadProc();
      virtual void LoadingThreadCompleted();
      void TitleScreenFinished();
      void MainMenuHalted(int);
      void InitialiseSinglePlayerBoard();
      void InitialiseOptionsDialog();
      virtual void SwitchScreenMode(bool wantWindowed, bool is3d);
      virtual void DialogButtonDepress(int dialog_id, int button_id);
      //virtual Dialog* NewDialog(int theDialogId, bool isModal, const std::string& theDialogHeader, 
								//const std::string& theDialogLines, const std::string& theDialogFooter, int theButtonMode);
	  void ExitApplication()
	  {
		  exit(0);
	  }
   };
}

#endif _cGAME_H_