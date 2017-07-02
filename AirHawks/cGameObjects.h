#ifndef _CGAMEOBJECTS_H_
#define _CGAMEOBJECTS_H_

#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"

namespace FrameworkX
{
   class SexyVector2;
   class Image;

   class cGameObjects
   {
   protected:
      Image* mImg;
      SexyVector2 mPos;
      FRect mFRect;

   public:
      cGameObjects(Image* theImg,SexyVector2 thePos,FRect theFRect)
      {
	 mImg = theImg;
	 mPos = SexyVector2(thePos.x, thePos.y);
	 mFRect = theFRect;
      }
   };
}
#endif