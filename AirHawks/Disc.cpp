#include "Disc.h"
#include "Res.h"
#include "cGame.h"
#include "cGameObjects.h"
#include "Board.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Widget.h"
#include <vector>
#include <math.h>
#include "cPhysics.h"

using namespace FrameworkX;
int BOTTOM_EDGE = 560;
int TOP_EDGE = 155;
int RIGHT_EDGE = 785;
int LEFT_EDGE = 14;
int DELTA = 2;
int MAX_SPEED = 900;
FRect shockrect(0,0,300.0,300.0);
Shocks Y;
cPhysics Physics; 

Disc::Disc(FrameworkX::SexyVector2 thePos, FrameworkX::Image *theImage, FrameworkX::FRect theRect, int theMass, int theMoverate, bool theMoveBool[], float theRadius, FrameworkX::cGame *theApp)
:cGameObjects(theImage, thePos, theRect)
{
   mMass = theMass;
   mMoverate=theMoverate;
   for(int i=0;i<4;i++)
	{  
		mMoveBool[i] = theMoveBool[i];
		mMotionBool[i] = true;
   }

   mRadius = theRadius;
   mForwardvec = SexyVector2(0,0);
   mWidth = float(theRect.mWidth);
   mHeight = float(theRect.mHeight);
   mApp=theApp;
   mMotion = false;
}

Disc::~Disc()
{
}

void Disc::UpdateF(float theFrac)
{
   if(mMotion)
   {
      mPos+=mForwardvec*float(mMoverate*theFrac);
      mFRect.mX = mPos.x - mWidth/2;
      mFRect.mY = mPos.y - mHeight/2;
      mMoverate-=int(float(mMoverate)*0.0005);
   }

   if(mMoverate<20)
   {
      mMotion = false;
      mMoverate = 0;
   }
}


void Disc::Draw(Graphics* g)
{
   g->TranslateF(float(mFRect.mX), float(mFRect.mY));
   if(mApp->Is3DAccelerated())
      g->DrawImageF(mImg,0,0);
   else
      g->DrawImage(mImg,0,0);
   g->TranslateF(float(-mFRect.mX),float( -mFRect.mY));
}


void Disc::collision_check_table(Tablerects Leftrects[], Tablerects Rightrects[], std::vector<Shocks> &S)
{
   if((mFRect.mY+mHeight>=BOTTOM_EDGE) && mForwardvec.y>0)
   {
      mFRect.mY=BOTTOM_EDGE - mHeight;
      mPos.x = float(mFRect.mX+mWidth/2);
      mPos.y = float(mFRect.mY+mHeight/2);
      SexyVector2 normal(mPos.x-mPos.x,mPos.y+mHeight/2-mPos.y);
      normal = normal.Normalize();
      mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
      float x,y;
      x = mPos.x;
      y = mPos.y+mHeight/2;
      shockrect.mX = x - 150;
      shockrect.mY = y - 300;
      Y.cord.x = float(shockrect.mX);
      Y.cord.y = float(shockrect.mY);
      Y.frame = 0;
      Y.dir = 180;
      S.push_back(Y);
   }
   
   else if((mFRect.mY<=TOP_EDGE) && mForwardvec.y<0)
   {
      mFRect.mY=TOP_EDGE;
      mPos.x = float(mFRect.mX+mWidth/2);
      mPos.y = float(mFRect.mY+mHeight/2);
      SexyVector2 normal(mPos.x-mPos.x,mPos.y-mHeight/2-mPos.y);
      normal = normal.Normalize();
      mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
      float x,y;
      x = mPos.x;
      y = mPos.y-mHeight/2;
      shockrect.mX = x - 150;
      shockrect.mY = y;
      Y.cord.x = float(shockrect.mX);
      Y.cord.y = float(shockrect.mY);
      Y.frame = 0;
      Y.dir = 0;
      S.push_back(Y);
   }

   //For Left boundaries
   if( Physics.point_inside_rect(mPos, Leftrects[0].upperrect))
   {
      if (Physics.pointintersect_circleandrect(this,Leftrects[0].rect,0) && (mForwardvec.x<0))
      {
	 mForwardvec = -mForwardvec + Leftrects[0].vector;
	 mForwardvec = mForwardvec.Normalize();
      }


      else if((mFRect.mX<=LEFT_EDGE)&&(mPos.y<=(Leftrects[0].rect.mY + Leftrects[0].rect.mHeight))&& mForwardvec.x<0)
      {
	 mFRect.mX=LEFT_EDGE;
	 mPos.x = float(mFRect.mX+mWidth/2);
	 mPos.y = float(mFRect.mY+mHeight/2);
	 SexyVector2 normal(mPos.x - mWidth/2-mPos.x,mPos.y-mPos.y);
	 normal = normal.Normalize();
	 mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
	 float x,y;
	 x = mPos.x - mWidth/2;
	 y = mPos.y;
	 shockrect.mX = x;
	 shockrect.mY = y - 150;
	 Y.cord.x = float(shockrect.mX);
	 Y.cord.y = float(shockrect.mY);
	 Y.frame = 0;
	 Y.dir = 90;
	 S.push_back(Y);
      }
   }
   else if( Physics.point_inside_rect(mPos, Leftrects[1].upperrect))
   {
      if (Physics.pointintersect_circleandrect(this,Leftrects[1].rect,1) && (mForwardvec.x<0))
      {
	 mForwardvec = -mForwardvec+Leftrects[1].vector;
	 mForwardvec = mForwardvec.Normalize();
      }


      else if((mFRect.mX<=LEFT_EDGE)&&(mPos.y>=Leftrects[1].rect.mY )&& mForwardvec.x<0)
      {
	 mFRect.mX=LEFT_EDGE;
	 mPos.x = float(mFRect.mX+mWidth/2);
	 mPos.y = float(mFRect.mY+mHeight/2);
	 SexyVector2 normal(mPos.x - mWidth/2-mPos.x,mPos.y-mPos.y);
	 normal = normal.Normalize();
	 mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
	 float x,y;
	 x = mPos.x - mWidth/2;
	 y = mPos.y;
	 shockrect.mX = x;
	 shockrect.mY = y - 150;
	 Y.cord.x = float(shockrect.mX);
	 Y.cord.y = float(shockrect.mY);
	 Y.frame = 0;
	 Y.dir = 90;
	 S.push_back(Y);
      }
   }


   //for right boundaries

   if( Physics.point_inside_rect(mPos, Rightrects[0].upperrect))
   {
      if (Physics.pointintersect_circleandrect(this,Rightrects[0].rect,2) && (mForwardvec.x>0))
      {
	 mForwardvec = -mForwardvec+Rightrects[0].vector;
	 mForwardvec = mForwardvec.Normalize();
      }


      else if(((mFRect.mX+mFRect.mWidth)>=RIGHT_EDGE)&&(mPos.y<=(Rightrects[0].rect.mY + Rightrects[0].rect.mHeight))&& mForwardvec.x>0)
      {
	 mFRect.mX=RIGHT_EDGE - mFRect.mWidth;
	 mPos.x = float(mFRect.mX+mWidth/2);
	 mPos.y = float(mFRect.mY+mHeight/2);
	 SexyVector2 normal(mPos.x + mWidth/2-mPos.x,mPos.y-mPos.y);
	 normal = normal.Normalize();
	 mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
	 float x,y;
	 x = mPos.x + mWidth/2;
	 y = mPos.y;
	 shockrect.mX = x - 300;
	 shockrect.mY = y - 150;
	 Y.cord.x = float(shockrect.mX);
	 Y.cord.y = float(shockrect.mY);
	 Y.frame = 0;
	 Y.dir = -90;
	 S.push_back(Y);
      }
   }
   else if( Physics.point_inside_rect(mPos, Rightrects[1].upperrect))
   {
      if (Physics.pointintersect_circleandrect(this,Rightrects[1].rect,3) && (mForwardvec.x>0))
      {
	 mForwardvec = -mForwardvec + Rightrects[1].vector;
	 mForwardvec = mForwardvec.Normalize();
      }


      else if(((mFRect.mX + mFRect.mWidth)>=RIGHT_EDGE)&&(mPos.y>=Rightrects[1].rect.mY )&& mForwardvec.x>0)
      {
	 mFRect.mX=RIGHT_EDGE - mFRect.mWidth;
	 mPos.x = float(mFRect.mX+mWidth/2);
	 mPos.y = float(mFRect.mY+mHeight/2);
	 SexyVector2 normal(mPos.x + mWidth/2-mPos.x,mPos.y-mPos.y);
	 normal = normal.Normalize();
	 mForwardvec = Physics.collision_sphere_plane(mForwardvec,normal);
	 float x,y;
	 x = mPos.x + mWidth/2;
	 y = mPos.y;
	 shockrect.mX = x - 300;
	 shockrect.mY = y - 150;
	 Y.cord.x = float(shockrect.mX);
	 Y.cord.y = float(shockrect.mY);
	 Y.frame = 0;
	 Y.dir = -90;
	 S.push_back(Y);
      }
   }
}


bool Disc::collision_with_puck_AI(cAI* t, float theFrac)
      {  
	 SexyVector2 puck_pos = t->get_pos();
	 float factor = 1.0;
	 t->set_factor(factor);
	 SexyVector2 fd = get_forwardmag();
	 SexyVector2 fp = t->get_forwardmag();
	 SexyVector2 reld = fd-fp;
	 SexyVector2 C(puck_pos.x - mPos.x,puck_pos.y - mPos.y);
	 float dist=C.Magnitude();
	 float sumradii = float(mRadius + t->get_radius() + 0.1);
	 dist-=sumradii;
	 if((reld.Magnitude()*theFrac)<dist)
	    return false;
	 SexyVector2 N;
	 N = reld.Normalize();
	 float D = N.Dot(C);
	 if(D<=0)
	    return false;
	 float lengthC=C.MagnitudeSquared();
	 float F = lengthC - D*D;
	 float sumRadiiSquared = sumradii*sumradii;
	 if(F>=sumRadiiSquared)
	    return false;

	 float T = sumRadiiSquared - F;

	 if(T<0)
	    return false;

	 float distance = D - sqrt(T);
	 if(distance > (reld.Magnitude()*theFrac))
	    return false;
	 collision_reaction_AI(t);
	 factor = distance/(reld.Magnitude()*theFrac);
	 t->set_factor(factor);
	 return true;
      }



      
void Disc::collision_reaction_AI(cAI *t)
      {
	 SexyVector2 vp;
	 mForwardvec = Physics.collision_circles_AI(this,t,vp);
	 mMoverate = int(mForwardvec.Magnitude());
	 if(mMoverate>MAX_SPEED)
	    mMoverate = MAX_SPEED;
	 mForwardvec = mForwardvec.Normalize();
	 t->SetForwardvec(vp.x,vp.y);
	 SexyVector2 vpuck=t->get_forwardvec();
	 float vx,vy,x,y,xd,yd;
	 vx = vpuck.x; vy = vpuck.y;
	 SexyVector2 puckpos=t->get_pos();
	 x = puckpos.x;   y = puckpos.y;
	 xd = mPos.x;     yd = mPos.y;
	 if((vx<0 && x>xd)||(vx>0 && x<xd)||(vy>0 && y<yd)|| (vy<0 && y>yd))
	 {
	    if(mMoverate<900)
	       mMoverate = 900;
	 }

	 if(!mMotion)
	    mMotion = true;
      }


bool Disc::collision_with_puck_Player(Player* t, float theFrac)
      {  
	 SexyVector2 puck_pos = t->get_pos();
	 float factor = 1.0;
	 t->set_factor(factor);
	 SexyVector2 fd = get_forwardmag();
	 SexyVector2 fp = t->get_forwardmag();
	 SexyVector2 reld = fd-fp;
	 SexyVector2 C(puck_pos.x - mPos.x,puck_pos.y - mPos.y);
	 float dist=C.Magnitude();
	 float sumradii = float(mRadius + t->get_radius() + 0.1);
	 dist-=sumradii;
	 if((reld.Magnitude()*theFrac)<dist)
	    return false;
	 SexyVector2 N;
	 N = reld.Normalize();
	 float D = N.Dot(C);
	 if(D<=0)
	    return false;
	 float lengthC=C.MagnitudeSquared();
	 float F = lengthC - D*D;
	 float sumRadiiSquared = sumradii*sumradii;
	 if(F>=sumRadiiSquared)
	    return false;

	 float T = sumRadiiSquared - F;

	 if(T<0)
	    return false;

	 float distance = D - sqrt(T);
	 if(distance > (reld.Magnitude()*theFrac))
	    return false;
	 collision_reaction_Player(t);
	 factor = distance/(reld.Magnitude()*theFrac);
	 t->set_factor(factor);
	 return true;
      }



      
void Disc::collision_reaction_Player(Player *t)
      {
	 SexyVector2 vp;
	 mForwardvec = Physics.collision_circles_Player(this,t,vp);
	 mMoverate = int(mForwardvec.Magnitude());
	 if(mMoverate>MAX_SPEED)
	    mMoverate = MAX_SPEED;
	 mForwardvec = mForwardvec.Normalize();
	 t->SetForwardvec(vp.x,vp.y);
	 SexyVector2 vpuck=t->get_forwardvec();
	 float vx,vy,x,y,xd,yd;
	 vx = vpuck.x; vy = vpuck.y;
	 SexyVector2 puckpos=t->get_pos();
	 x = puckpos.x;   y = puckpos.y;
	 xd = mPos.x;     yd = mPos.y;
	 if((vx<0 && x>xd)||(vx>0 && x<xd)||(vy>0 && y<yd)|| (vy<0 && y>yd))
	 {
	    if(mMoverate<900)
	       mMoverate = 900;
	 }

	 if(!mMotion)
	    mMotion = true;
      }




void Disc::reset_pos(float x, float y)
{
   mPos.x = x;
   mPos.y = y;
   mFRect.mX = x - mWidth/2;
   mFRect.mY = y - mHeight/2;
   mMoverate = 0;
   mForwardvec.x = 0;
   mForwardvec.y = 0;
   mMotion = false;
}

