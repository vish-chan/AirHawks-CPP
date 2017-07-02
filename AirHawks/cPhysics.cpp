#include "Player.h"
#include "cPhysics.h"
#include "cAI.h"
#include "Disc.h"
#include "cGameObjects.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include <vector>




using namespace FrameworkX;

SexyVector2 cPhysics::collision_sphere_plane(SexyVector2 forvec,SexyVector2 normal)
   {
      forvec = forvec-normal*(2*forvec.Dot(normal));
      return forvec;
   }


   
   SexyVector2 cPhysics::collision_circles_AI(Disc* disc, cAI* t, SexyVector2& vp)
   {
      SexyVector2 n(t->get_pos().x-disc->get_pos().x,t->get_pos().y-disc->get_pos().y);
      n = n.Normalize();
      SexyVector2 forvec_disc = disc->get_forwardmag();
      SexyVector2 forvec_puck = t->get_forwardmag();
      double a1 = forvec_disc.Dot(n);
      double a2 = forvec_puck.Dot(n);
      double p = (2.0*(a1-a2))/(disc->get_mass()+t->get_mass());
      SexyVector2 vd = forvec_disc - n*float(p * t->get_mass());
      vp = forvec_puck + n*float(p * disc->get_mass()) ;
      return vd;
   }

   SexyVector2 cPhysics::collision_circles_Player(Disc* disc, Player* t, SexyVector2& vp)
   {
      SexyVector2 n(t->get_pos().x-disc->get_pos().x,t->get_pos().y-disc->get_pos().y);
      n = n.Normalize();
      SexyVector2 forvec_disc = disc->get_forwardmag();
      SexyVector2 forvec_puck = t->get_forwardmag();
      double a1 = forvec_disc.Dot(n);
      double a2 = forvec_puck.Dot(n);
      double p = (2.0*(a1-a2))/(disc->get_mass()+t->get_mass());
      SexyVector2 vd = forvec_disc - n*float(p * t->get_mass());
      vp = forvec_puck + n*float(p * disc->get_mass()) ;
      return vd;
   }



   bool  cPhysics::pointintersect_circleandrect(Disc* circle, FRect rect , int Case)
   {
      double xc,yc,x,y;
      xc = circle->get_pos().x;
      yc = circle->get_pos().y;
      double dist,r = pow(circle->get_radius(),2);
      
      if(Case==0)
      {
		  x = rect.mX+rect.mWidth;
		  y = rect.mY+rect.mHeight;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<r)
			  return true;
		  
			  return false;
      }

      if(Case==1)
	  {
		  x = rect.mX+rect.mWidth;
		  y = rect.mY;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<r)
			  return true;
		  
			  return false;
      }

      if(Case==2)
      {
		  x = rect.mX;
		  y = rect.mY+rect.mHeight;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<r)
			  return true;
		  
			  return false;
      }

      if(Case==3)
      {
		  x = rect.mX;
		  y = rect.mY;
		  dist = pow(xc-x,2)+pow(yc-y,2);
		  if(dist<r)
			  return true;
		 
			  return false;
      }
	  return false;
   }

   bool cPhysics::point_inside_rect(SexyVector2 point,FRect rect)
   {

		if (point.x>=rect.mX && point.x<=(rect.mX+rect.mWidth))
		{
			if (point.y>=rect.mY && point.y<=(rect.mY+rect.mHeight))
				return true;
		}
		return false;
   }


   bool  cPhysics::circle_rect_intersection(Disc* circle, FRect rect, int Case)
   {
      double xc,yc,x,r,dist;
      xc = circle->get_pos().x;
      yc = circle->get_pos().y;
      r = circle->get_radius()+2;
      if(Case==0)
      {
		  x = rect.mX+rect.mWidth;
		  dist = xc-x;
		  if(dist<=r)
			  return true;
		  
			  return false;
      }

      if(Case==1)
      {
		  x = rect.mX;
		  dist = x - xc;
		  if(dist<=r)
			  return true;
		  return false;
      }
	  return false;
   }
