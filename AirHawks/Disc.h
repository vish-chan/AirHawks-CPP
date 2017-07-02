#ifndef _DISC_H_
#define _DISC_H_

#include "Board.h"
#include "cGame.h"
#include "Player.h"
#include "cAI.h"
#include "cGameObjects.h"
#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include<vector>

namespace FrameworkX
{
   class SexyVector2;
   class cGame;
   class Image;
   class Graphics;
   class Player;
   struct Tablerects;
   struct Shocks;
  

   class Disc:public cGameObjects, public Widget
   {
   private:
      int mMass;
      int mMoverate;
      bool mMoveBool[4];
      bool mMotionBool[4];
      SexyVector2 mForwardvec;
      float mWidth;
      float mHeight;
      cGame* mApp;
      float mRadius;
      bool mMotion;
    
   
   
   public:

      Disc(SexyVector2 thePos, Image *theImage, FRect theRect, int theMass, int theMoverate, bool theMoveBool[4], float theRadius, cGame*);
      ~Disc();
      void UpdateF(float);
      void Draw(Graphics*);
      void collision_check_table(Tablerects Leftrects[], Tablerects Rightrects[], std::vector<Shocks>&);
      
      
      bool collision_with_puck_AI(cAI *t, float theFrac);
      void collision_reaction_AI(cAI *t);
      
      bool collision_with_puck_Player(Player *t, float theFrac);
      void collision_reaction_Player(Player *t);

      
      
      void reset_pos(float, float);
      
      
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
   };
}

#endif