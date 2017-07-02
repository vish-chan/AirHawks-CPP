#ifndef _BOARD_H_
#define _BOARD_H_

#include "SexyAppFramework\Widget.h"
#include "SexyAppFramework\Rect.h"
#include "SexyAppFramework\SexyVector.h"
#include "cGame.h"
#include "Player.h"
#include "cAI.h"
#include "Disc.h"

namespace FrameworkX
{

class cGame;
class Image;
class Graphics;
class Player;
class cAI;
class Disc;
class SexyVector2;

struct Tablerects
{
	FRect upperrect;
	FRect rect;
	SexyVector2 vector;
};

struct Shocks
{
	int frame;
	double dir;
	SexyVector2 cord;
};



class Board : public Widget, public ButtonListener
{

private:
	cGame* mApp;
	Player* mPlayer;
	cAI* mAI;
	Disc* mDisc;

public:

	Board(cGame* theApp);
	virtual ~Board();

	void		Update();
	void		UpdateF(float);
	void		Draw(Graphics* g);
	//void		ButtonDepress(int id);
	//void		DrawOverlay(Graphics* g);
	virtual void KeyDown(KeyCode theKey);
	virtual void KeyUp(KeyCode theKey);
};

}

#endif //__BOARD_H__
