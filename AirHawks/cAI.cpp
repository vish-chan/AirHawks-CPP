#include "cAI.h"
#include "Res.h"
#include "cGame.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Widget.h"
#include<stdlib.h>
#include<time.h>


using namespace FrameworkX;


int flag=0;
int l=0,UPPERBOUND,LOWERBOUND;
SexyVector2 CENTER_POINT_DEF(700.0,350.0);
SexyVector2 CENTER_POINT_ATT(760.0,350.0);




cAI::cAI(SexyVector2 thePos, Image *theImage, FRect theRect, int theMass, int theMoverate, bool theMoveBool[4],int theScore, int theRightB, int theLeftB,cGame* theApp)
: cGameObjects( theImage, thePos, theRect)
{
   mMass = theMass;
   mMoverate=theMoverate;
   for(int i=0;i<4;i++)
	{  
		mMoveBool[i] = theMoveBool[i];
		mMotionBool[i] = true;
   }
   mScore='0';
   mRadius = 20.0;
   mForwardvec = SexyVector2(0,0);
   mRightBound = theRightB;
   mLeftBound = theLeftB;
   mFactor = 1;
   mWidth = float(theRect.mWidth);
   mHeight = float(theRect.mHeight);
   mApp=theApp;
   mState = 0;
   mIdleMotion.Bool = false;
   mIdleMotion.UP=1;
   mIdleMotion.DOWN=0;
}

cAI::~cAI()
{
 
}


void cAI::DefenceState(Disc *disc)
{
   flag=0;
   if((disc->get_forwardvec()).x>0)
   {
      mMoverate = 250;
      mIdleMotion.Bool=false;
      if (mPos.x<690 || mPos.x>710 || mPos.y>470 || mPos.y<230)
		  Predefence();
      else
	  {
		  float xd,yd,vx,vy;
		  xd=(disc->get_pos()).x;
		  yd=(disc->get_pos()).y;
		  vx = (disc->get_forwardvec()).x;
		  vy = (disc->get_forwardvec()).y;
		  if(vy>0 || vy<=0)
		  {
			if (mPos.y>yd)
			   SetForwardvec(0,-1.0);
			else if(mPos.y<yd)
			   SetForwardvec(0,1.0);
			else
			   SetForwardvec(0,0);
		  }
      }
   }
   else
   {
      if (mPos.x<690 || mPos.x>710 || mPos.y>325 || mPos.y<375)
		  Predefence();
      else
      {
		  mIdleMotion.Bool = true;
		  mMoverate=100;
		  IdleState();
      }
   }
}

void cAI::IdleState()
{
   mMoverate = 100;
   if (mPos.y>=370)
    {
       mIdleMotion.UP=1;
       mIdleMotion.DOWN=0;
    }
            
   else if (mPos.y<=330)
    {
       mIdleMotion.UP=0;
       mIdleMotion.DOWN = 1;
    }
   if(mIdleMotion.UP)
       SetForwardvec(0,-1.0);
     
   else if(mIdleMotion.DOWN)
       SetForwardvec(0,1.0);
}


void cAI::AttackState(Disc* disc, int x)
{  
   int y;
   SexyVector2 cenvec;
   float xd,yd,D,F,xdisc,ydisc;
   xd = (disc->get_pos()).x; 
   yd = (disc->get_pos()).y;
   xdisc = (disc->get_forwardvec()).x;
   ydisc = (disc->get_forwardvec()).y;
   
   mState = 1;
   mMoverate = 900;
   if((disc->get_pos()).y>340)
      y = 560;
   else
      y=150;

   cenvec.x=mPos.x-xd;
   cenvec.y = mPos.y -yd;
   D = cenvec.x*xdisc + cenvec.y*ydisc;
   F = cenvec.MagnitudeSquared() - D*D;

   if (disc->get_moverate()==0)
   {
      if(!flag)
      {
		 srand((unsigned)time(NULL));
		 l = rand()%2;
		 flag = 1;
      }
      InitAttack(disc);
   }

   else if(D>0 && F<=pow(disc->get_radius()+mRadius,2))
      AIFollow(disc);

   else if(((disc->get_pos()).x + disc->get_radius())<mPos.x && disc->get_moverate() > 100)
   {
      flag = 0;
      float sumradii=mRadius + disc->get_radius();
      int v_disc_moverate = disc->get_moverate();
      SexyVector2 v_disc = disc->get_forwardmag();
      SexyVector2 n(x-mPos.x,y-mPos.y);
      SexyVector2 n_normalized=n.Normalize();
      SexyVector2 pd((disc->get_pos()).x - mPos.x,(disc->get_pos()).y - mPos.y);
      float pd_dist = pd.MagnitudeSquared();
      float d = pd.Dot(n_normalized);
      float perp_d = sqrt(pd_dist - pow(d,2));
      float costheta = (n.x*v_disc.x + n.y*v_disc.y)/(v_disc_moverate*n.Magnitude());
      float theta = acos(costheta);
      theta = (22/7) - theta;
      float sintheta = sin(theta);
      float d_dist=perp_d/sintheta;
      float puck_dist = sqrt(d_dist*d_dist-perp_d*perp_d);
      float hit_dist = d - puck_dist - (sumradii);
      float hit_time = d_dist/v_disc_moverate;
      float hit_time_puck = hit_dist/mMoverate;

      if(hit_time_puck>hit_time)
		  AIFollow(disc);
      else
		  SetForwardvec(n_normalized.x,n_normalized.y);
   }
   else if(disc->get_moverate()<=100)
      AIFollow(disc);

   else
   {
      if (mPos.x<755 || mPos.x>765 || mPos.y>470 || mPos.y<230)
		  Predefence();
      else
      {
		 mIdleMotion.Bool=true;
		 mMoverate=50;
		 IdleState();
      }
   }
}





void cAI::AIFollow(Disc* disc)
{
   if((mPos.x - mWidth)>(disc->get_pos()).x)
   {
      float y1=mPos.y+mWidth/2;
      float x1=mPos.x;
      SexyVector2 d_pos=disc->get_pos();
      float xd = d_pos.x; float yd = d_pos.y; 
      float wd = disc->get_width();
      float hd = disc->get_height();
      xd-=wd/2;
      yd+=hd/2;
      SexyVector2 n(xd-x1,yd-y1);
      SexyVector2 v;
      v = mForwardvec+n;
      SetForwardvec(v.x,v.y);
   }
   else
      DefenceState(disc);
}

     
void cAI::InitAttack(Disc* disc)
{
   mMoverate = 250;
   if(l==0)
      if(mPos.y<=420)
	 SetForwardvec(700-mPos.x, 420-mPos.y);
   else if(l==1)
      if(mPos.y>290)
	 SetForwardvec(700-mPos.x, 290- mPos.y);
   else if(l==2)
   {
      mMoverate = 500;
      SetForwardvec((disc->get_pos()).x-mPos.x, (disc->get_pos()).y - mPos.y);

      }
   if(mPos.y>=420 || mPos.y<=290)
      l=2;
   mForwardvec = mForwardvec.Normalize();
}



void cAI::Predefence()
{  SexyVector2 CENTER_POINT(0,0);
   mMoverate = 500;
   if(mState == 0)
      CENTER_POINT+=CENTER_POINT_DEF;
   else
      CENTER_POINT+=CENTER_POINT_ATT;
   SetForwardvec(CENTER_POINT.x-mPos.x,CENTER_POINT.y-mPos.y);
   mForwardvec = mForwardvec.Normalize();
}



void cAI::SetForwardvec(float x, float y)
{
   mForwardvec.x=x;
   mForwardvec.y=y;
   mForwardvec = mForwardvec.Normalize();
}

     

void cAI::UpdateF(float theFrac)
{ 
   if(!mState)
   {
      UPPERBOUND=270;
      LOWERBOUND=440;
   }
   else if(mState)
   {
      UPPERBOUND = 155;
      LOWERBOUND = 560;
   }
   
   if (mFRect.mX<mLeftBound)
   {
      mFRect.mX = double(mLeftBound);
      mMotionBool[0]=false;
      if(mForwardvec.x<0)
		  mForwardvec.x = 0;
	  else
		  mMotionBool[0]=true;

   if (mFRect.mX + mFRect.mWidth>mRightBound)
   {
      mFRect.mX = mRightBound - mWidth;
      mMotionBool[1]=false;
	  if(mForwardvec.x>0)
		  mForwardvec.x=0;
   }
   else
      mMotionBool[1]=true;

   if (mFRect.mY<UPPERBOUND)
   {
      mMotionBool[2]=false;
      mFRect.mY = UPPERBOUND;
      if(mForwardvec.y<0)
		  mForwardvec.y=0;
   }
   else
      mMotionBool[2]=true;

   if ((mFRect.mY + mFRect.mHeight)>LOWERBOUND)
   {
      mFRect.mY = LOWERBOUND - mHeight;
      mMotionBool[3]=false;
      if(mForwardvec.y>0)
		  mForwardvec.y=0;
	  else
		  mMotionBool[3]=true;

   float centerx1,centery1;
   centerx1 = mPos.x;
   centery1 = mPos.y;
   mPos+=mForwardvec*float(mMoverate*theFrac*mFactor);
   mFRect.mX = mPos.x - mWidth/2;
   mFRect.mY = mPos.y - mHeight/2;

   float centerx2,centery2;
   centerx2 = mPos.x; 
   centery2 = mPos.y;
   mForwardvec.x = centerx2-centerx1;
   mForwardvec.y = centery2-centery1;
   }
   }
}


void cAI::Draw(Graphics* g)
{
   g->TranslateF(float(mFRect.mX),float(mFRect.mY));
   if(mApp->Is3DAccelerated())
      g->DrawImageF(mImg,0,0);
   else
      g->DrawImage(mImg,0,0);
   g->TranslateF(float(-mFRect.mX), float(-mFRect.mY));
}



void cAI::UpdateScore(int a)
{
   mScore+=a;
}

void cAI::ResetPos(float x, float y)
{
   mPos = SexyVector2(x,y);
   mFRect = FRect(double(x)-mWidth/2.0,double(y)-mHeight/2.0,double(mWidth),double(mHeight));
   mForwardvec.x=0;
   mForwardvec.y=0;
   mMoverate=0;
}

void cAI::BlockMotion()
{
   mMoverate=0;
   mForwardvec.x=0;
   mForwardvec.y=0;
   for(int i=0;i<4;i++)
      mMoveBool[i]=false;
}