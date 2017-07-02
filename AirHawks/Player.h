#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cGame.h"
#include "Disc.h"
#include "cGameObjects.h"
#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"

namespace FrameworkX
{
   class SexyVector2;
   class cGame;
   class Disc;
   class Image;
   class Graphics;
   

   class Player:public cGameObjects, public Widget
   {
   private:
      int mMass;
      int mMoverate;
      bool mMoveBool[4];
      bool mMotionBool[4];
      int mScore;
      SexyVector2 mForwardvec;
      int mRightBound;
      int mLeftBound;
      float mFactor;
      float mWidth;
      float mHeight;
      cGame* mApp;
      float mRadius;

   public:
      Player(SexyVector2 thePos,Image* theImage,FRect theRect,int theMass,int theMoverate,bool theMoveBool[4], int theScore, int theRightB, int theLeftB, cGame*);
      ~Player();
      void SetMotion(KeyCode theKey);
      void ResetMotion(KeyCode theKey);
      void UpdateF(float theFrac);
      void Draw(Graphics*);
      void UpdateScore(int);
      void ResetPos(float,float);
      void BlockMotion();
      void UnblockMotion();
      void SetForwardvec(float,float);

      SexyVector2 get_pos()
      {
	 return mPos;
      }
      FRect get_rect()
      {
	 return mFRect;
      }
      int get_moverate()
      {
	 return mMoverate;
      }
      int get_mass()
      {
	 return mMass;
      }
      float get_radius()
      {
	 return mRadius;
      }
      SexyVector2 get_forwardvec()
      {
	 return mForwardvec;
      }
      SexyVector2 get_forwardmag()
      {
	 return mForwardvec*float(mMoverate);
      }
      float get_width()
      { 
	 return mWidth;
      }
      float get_height()
      {
	 return mHeight;
      }
	 int get_score()
	 {
		 return mScore;
	 }

      void set_factor(float theFactor)
      {
	 mFactor = theFactor;
      }
   };
}

#endif