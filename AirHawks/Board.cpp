#include "SexyAppFramework\Widget.h"
#include "SexyAppFramework\WidgetManager.h"
#include "SexyAppFramework\Rect.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/SexyVector.h"
#include "cGame.h"
#include "Player.h"
#include "cAI.h"
#include "Disc.h"
#include "Res.h"
#include "Board.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include<string>
#include<sstream>

using namespace FrameworkX;


std::stringstream ss;
std::string Str;
int FLAG = 0, UPPER_BOUND = 400,LOWER_BOUND = 200,x;
bool collisionBool1,collisionBool2;
Tablerects Leftrects[2], Rightrects[2];
std::vector<Shocks> S(4); 

Tablerects leftrects[2],rightrects[2];


Board::Board(FrameworkX::cGame *theApp)
{
   mWidgetFlagsMod.mAddFlags |= WIDGETFLAGS_MARK_DIRTY;
   mApp = theApp;
   
   FRect rect(115,275,150,150);
   rect.mX = 100 - rect.mWidth/2;
   rect.mY = 350 - rect.mHeight/2;
   SexyVector2 thePos(float(rect.mX+rect.mWidth/2.0),float(rect.mY+rect.mHeight/2.0));
   bool movebool[4]={false,false,false,false};
   mPlayer = new Player(thePos, IMAGE_PLAYER_1, rect, 100, 350, movebool, 0,435,-20,theApp);
   
   
   rect.mX = 700-rect.mWidth/2.0;
   rect.mY = 350-rect.mHeight/2.0;
   thePos.x = float(rect.mX+rect.mWidth/2.0);
   thePos.y = float(rect.mY+rect.mHeight/2.0);
   mAI = new cAI(thePos, IMAGE_PLAYER_2, rect, 100, 900, movebool, 0,840,360,theApp);
   


   FRect rectd(0,0,33.0,33.0);
   rectd.mX = 600 - rectd.mWidth/2;
   rectd.mY = 350 - rectd.mHeight/2;
   thePos.x = float(rectd.mX+rectd.mWidth/2);
   thePos.y = float(rectd.mY+rectd.mHeight/2);
   mDisc = new Disc(thePos, IMAGE_DISC, rectd, 1, 0, movebool, 17.5, theApp);

   AddWidget(mPlayer);
   AddWidget(mAI);
   AddWidget(mDisc);

   

}

Board::~Board()
{
	RemoveAllWidgets();
	if(mPlayer!=NULL)
		delete mPlayer;
	if(mDisc!=NULL)
		delete mDisc;
	if(mAI!= NULL)
		delete mAI;
}


void Board::Update()
{
	if(mDisc->get_pos().x<=400)
	{
		FLAG = 1;
		mAI->DefenceState(mDisc);
	}
	
	else if(mDisc->get_pos().x>400)
	{
		if(FLAG==1)
		{
			srand((unsigned)time(NULL));
			x =  LOWER_BOUND + rand() % (UPPER_BOUND - LOWER_BOUND);
			FLAG = 0;
		}
		mAI->AttackState(mDisc,x);
	}

	mDisc->collision_check_table(leftrects, rightrects, S);
	
	int i;
	i=0;
	i = int(S.size());

	if(i>4)
		for(;i>4;i--)
			S.pop_back();


	
}


void Board::UpdateF(float theFrac)
{
	collisionBool1 = mDisc->collision_with_puck_AI(mAI, theFrac);
	collisionBool2 = mDisc->collision_with_puck_Player(mPlayer, theFrac);

}


void Board::Draw(Graphics* g)
{
	g->DrawImage(IMAGE_TABLE,0,0);
	g->SetColor(Color::White);
	g->SetFont(FONT_DEFAULT);
	ss<<mAI->get_score();
	ss>>Str;
	g->DrawString(StringToSexyString(_S(Str)),95,55);
	ss<<mPlayer->get_score();
	ss>>Str;
	g->DrawString(StringToSexyString(_S(Str)),255,55);

	std::vector<Shocks>::size_type itr;
	int i = 0;
	for(itr = 0; itr!=S.size(); ++itr,i++)
	{
		if(S[itr].frame>=0 && S[itr].frame<60)
		{
		
		if(S[itr].frame>=0 && S[itr].frame<10)
			g->DrawImageRotated(IMAGE_EFFECTS, int(S[itr].cord.x),int(S[itr].cord.y),(S[itr].dir),&Rect(0,0,300,300));
		else if(S[itr].frame>=10 && S[itr].frame<20)
			g->DrawImageRotated(IMAGE_EFFECTS,  int(S[itr].cord.x),int(S[itr].cord.y),S[itr].dir,&Rect(300,0,300,300));
		else if(S[itr].frame>=20 && S[itr].frame<30)
			g->DrawImageRotated(IMAGE_EFFECTS,  int(S[itr].cord.x),int(S[itr].cord.y),S[itr].dir,&Rect(600,0,300,300));
		else if(S[itr].frame>=30 && S[itr].frame<40)
			g->DrawImageRotated(IMAGE_EFFECTS, int(S[itr].cord.x),int(S[itr].cord.y),S[itr].dir,&Rect(900,0,300,300));
		else if(S[itr].frame>=40 && S[itr].frame<50)
			g->DrawImageRotated(IMAGE_EFFECTS, int(S[itr].cord.x),int(S[itr].cord.y),S[itr].dir,&Rect(1200,0,300,300));
		else if(S[itr].frame>=50 && S[itr].frame<60)
			g->DrawImageRotated(IMAGE_EFFECTS, int(S[itr].cord.x),int(S[itr].cord.y),S[itr].dir,&Rect(1500,0,300,300));
		S[itr].frame+=5;
		}
		
		else 
		{
			S.erase(S.begin()+i);
			i--;
			itr--;
		}
		
	}

	mPlayer->Draw(g);
	mAI->Draw(g);
	mDisc->Draw(g);

}


void Board::KeyDown(KeyCode theKey)
{
	mPlayer->SetMotion(theKey);
}

void Board::KeyUp(KeyCode theKey)
{
	mPlayer->ResetMotion(theKey);
}

