#include "Player.h"
#include "Res.h"
#include "cGame.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Widget.h"


using namespace FrameworkX;

int TOP_BOUND = 108;
int BOTTOM_BOUND = 605;


Player::Player(SexyVector2 thePos, Image *theImage, FRect theFRect, int theMass, int theMoverate, bool theMoveBool[4],int theScore, int theRightB, int theLeftB,cGame* theApp)
:cGameObjects( theImage, thePos, theFRect)
{
   mMass = theMass;
   mMoverate=theMoverate;
   for(int i=0;i<4;i++)
	{  
		mMoveBool[i] = theMoveBool[i];
		mMotionBool[i] = true;
   }

   
   mScore=0;
   mForwardvec = SexyVector2(0,0);
   mRightBound = theRightB;
   mLeftBound = theLeftB;
   mFactor = 1;
   mWidth = float(theFRect.mWidth);
   mHeight = float(theFRect.mHeight);
   mApp=theApp;
   mRadius = 20.0;
}

Player::~Player()
{
  
}


void Player::SetMotion(KeyCode theKey)
{
   if(theKey==KEYCODE_LEFT)
   {
      mMoveBool[0]= true;
      mMoveBool[1]= false;
   }

   if(theKey==KEYCODE_RIGHT)
   {
      mMoveBool[1]= true;
      mMoveBool[0]= false;
   }
   if(theKey==KEYCODE_UP)
   {
      mMoveBool[2]= true;
      mMoveBool[3]= false;
   }
   if(theKey==KEYCODE_DOWN)
   {
      mMoveBool[3]= true;
      mMoveBool[2]= false;
   }
}

void Player::ResetMotion(KeyCode theKey)
{
   if(theKey==KEYCODE_LEFT)
      mMoveBool[0]=false;
   if(theKey==KEYCODE_RIGHT)
      mMoveBool[1]=false;
   if(theKey==KEYCODE_UP)
      mMoveBool[2]=false;
   if(theKey==KEYCODE_DOWN)
      mMoveBool[3]=false;
}


void Player::UpdateF(float theFrac)
{
   if (mFRect.mX<mLeftBound)
      mMotionBool[0]=false;
   else
      mMotionBool[0]=true;

   if (mFRect.mX + mFRect.mWidth>mRightBound)
      mMotionBool[1]=false;
   else
      mMotionBool[1]=true;

   if (mFRect.mY<TOP_BOUND)
      mMotionBool[2]=false;
   else
      mMotionBool[2]=true;

   if (mFRect.mY + mFRect.mHeight>BOTTOM_BOUND)
      mMotionBool[3]=false;
   else
      mMotionBool[3]=true;

   float centerx1,centery1;
   centerx1 = mPos.x;
   centery1 = mPos.y;

   if(mMotionBool[0])
      if( mMoveBool[0])
      {
	 mForwardvec.x = -1.0;
	 mForwardvec = mForwardvec.Normalize();
	 mPos+=mForwardvec*float(mMoverate*theFrac*mFactor);
      }

   if(mMotionBool[1])
      if( mMoveBool[1])
      {
	 mForwardvec.x = 1.0;
	 mForwardvec = mForwardvec.Normalize();
	 mPos+=mForwardvec*float(mMoverate*theFrac*mFactor);
      }

   if(mMotionBool[2])
      if( mMoveBool[2])
      {
	 mForwardvec.y = -1.0;
	 mForwardvec = mForwardvec.Normalize();
	 mPos+=mForwardvec*float(mMoverate*theFrac*mFactor);
      }

   if(mMotionBool[3])
      if( mMoveBool[3])
      {
	 mForwardvec.y = 1.0;
	 mForwardvec = mForwardvec.Normalize();
	 mPos+=mForwardvec*float(mMoverate*theFrac*mFactor);
      }

   mFRect.mX = mPos.x - (mWidth/2.0);
   mFRect.mY = mPos.y - (mHeight/2.0);

   float centerx2,centery2;
   centerx2 = mPos.x; 
   centery2 = mPos.y;
   mForwardvec.x = centerx2-centerx1;
   mForwardvec.y = centery2-centery1;

}


void Player::Draw(Graphics* g)
{
   g->TranslateF(float(mFRect.mX), float(mFRect.mY));
   if(mApp->Is3DAccelerated())
      g->DrawImageF(mImg,0,0);
   else
      g->DrawImage(mImg,0,0);
   g->TranslateF(float(-mFRect.mX),float( -mFRect.mY));
}



void Player::UpdateScore(int a)
{
   mScore+=a;
}

void Player::ResetPos(float x, float y)
{
   mPos = SexyVector2(x,y);
   mFRect = FRect(x-mWidth/2,y-mHeight/2,mWidth,mHeight);
   mForwardvec.x=0;
   mForwardvec.y=0;
   mMoverate=0;
}

void Player::BlockMotion()
{
   mMoverate=0;
   mForwardvec.x=0;
   mForwardvec.y=0;
   for(int i=0;i<4;i++)
      mMoveBool[i]=false;
}


void Player::SetForwardvec(float x, float y)
{
   mForwardvec.x=x;
   mForwardvec.y=y;
   mForwardvec = mForwardvec.Normalize();
}