#ifndef _CPHYSICS_H_
#define _CPHYSICS_H


#include "Player.h"
#include "cAI.h"
#include "Disc.h"
#include "cGameObjects.h"
#include "SexyAppFramework/SexyVector.h"
#include "SexyAppFramework/Rect.h"
#include<vector>

namespace FrameworkX
{
	class cPhysics
	{
	public:
		SexyVector2 collision_sphere_plane(SexyVector2 forvec,SexyVector2 normal);
		SexyVector2 collision_circles_AI(Disc* disc, cAI* t, SexyVector2& vp);
		SexyVector2 collision_circles_Player(Disc* disc, Player* t, SexyVector2& vp);
		bool point_inside_rect(SexyVector2 point,FRect rect);
		bool pointintersect_circleandrect(Disc* circle, FRect rect , int Case);
		bool circle_rect_intersection(Disc* circle, FRect rect, int Case);
	};

	
}

  

#endif