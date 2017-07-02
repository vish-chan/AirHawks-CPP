#ifndef _CAI_H_
#define _CAI_H_

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
   struct Idlemotion
   {
      bool Bool;
      int UP, DOWN;
   };

   class SexyVector2;
   class cGame;
   class Image;
   class Disc;
   class Graphics;

   class cAI:public cGameObjects, public Widget
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
      int mState;   //1:Attack 0:Defense
      Idlemotion mIdleMotion; 
      float mRadius;


   public:
      cAI(SexyVector2 thePos,Image* theImage,FRect theRect,int theMass,int theMoverate,bool theMoveBool[4],
	 int theScore, int theRightB, int theLeftB, cGame*);
      ~cAI();
      void DefenceState(Disc*);
      void IdleState();
      void AttackState(Disc*, int );
      void AIFollow(Disc*);
      void InitAttack(Disc*);
      void Predefence();
      void SetForwardvec(float,float);
      void SetMotion(KeyCode theKey);
      void ResetMotion(KeyCode theKey);
      void UpdateF(float theFrac);
      void Draw(Graphics*);
      void UpdateScore(int);
      void ResetPos(float,float);
      void BlockMotion();
      void UnblockMotion();

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
		  SexyVector2 forwardmag;
		  forwardmag = mForwardvec*float(mMoverate);
	      return forwardmag;
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