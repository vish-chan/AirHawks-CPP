#include "Res.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace FrameworkX;

#pragma warning(disable:4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool FrameworkX::ExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName,"Game")==0) return ExtractGameResources(theManager);
	if (strcmp(theName,"Init")==0) return ExtractInitResources(theManager);
	if (strcmp(theName,"TitleScreen")==0) return ExtractTitleScreenResources(theManager);
	return false;
}

FrameworkX::ResourceId FrameworkX::GetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string,int> MyMap;
	static MyMap aMap;
	if(aMap.empty())
	{
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[GetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

// Game Resources
Image* FrameworkX::IMAGE_BUTTON_DOWN;
Image* FrameworkX::IMAGE_BUTTON_NORMAL;
Image* FrameworkX::IMAGE_BUTTON_OVER;
Image* FrameworkX::IMAGE_CHECKBOX;
Image* FrameworkX::IMAGE_CHOOSE_ARENA;
Image* FrameworkX::IMAGE_CHOOSE_ARENA_BUTTON_DOWN;
Image* FrameworkX::IMAGE_CHOOSE_ARENA_BUTTON_NORMAL;
Image* FrameworkX::IMAGE_CHOOSE_ARENA_BUTTON_OVER;
Image* FrameworkX::IMAGE_DEFEAT;
Image* FrameworkX::IMAGE_DIALOG_BOX;
Image* FrameworkX::IMAGE_DIALOG_BUTTON;
Image* FrameworkX::IMAGE_DISC;
Image* FrameworkX::IMAGE_EFFECTS;
Image* FrameworkX::IMAGE_GOAL;
Image* FrameworkX::IMAGE_INSTRUCTIONS;
Image* FrameworkX::IMAGE_MAIN_MENU;
Image* FrameworkX::IMAGE_PLAYER_1;
Image* FrameworkX::IMAGE_PLAYER_2;
Image* FrameworkX::IMAGE_SLIDER_THUMB;
Image* FrameworkX::IMAGE_SLIDER_TRACK;
Image* FrameworkX::IMAGE_TABLE_1;
Image* FrameworkX::IMAGE_TABLE_2;
Image* FrameworkX::IMAGE_TABLE_3;
Image* FrameworkX::IMAGE_TABLE_4;
Image* FrameworkX::IMAGE_VICTORY;
int FrameworkX::SOUND_MUTATOR;
int FrameworkX::SOUND_TIMER;

bool FrameworkX::ExtractGameResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BUTTON_DOWN = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN");
		IMAGE_BUTTON_NORMAL = aMgr.GetImageThrow("IMAGE_BUTTON_NORMAL");
		IMAGE_BUTTON_OVER = aMgr.GetImageThrow("IMAGE_BUTTON_OVER");
		IMAGE_CHECKBOX = aMgr.GetImageThrow("IMAGE_CHECKBOX");
		IMAGE_CHOOSE_ARENA = aMgr.GetImageThrow("IMAGE_CHOOSE_ARENA");
		IMAGE_CHOOSE_ARENA_BUTTON_DOWN = aMgr.GetImageThrow("IMAGE_CHOOSE_ARENA_BUTTON_DOWN");
		IMAGE_CHOOSE_ARENA_BUTTON_NORMAL = aMgr.GetImageThrow("IMAGE_CHOOSE_ARENA_BUTTON_NORMAL");
		IMAGE_CHOOSE_ARENA_BUTTON_OVER = aMgr.GetImageThrow("IMAGE_CHOOSE_ARENA_BUTTON_OVER");
		IMAGE_DEFEAT = aMgr.GetImageThrow("IMAGE_DEFEAT");
		IMAGE_DIALOG_BOX = aMgr.GetImageThrow("IMAGE_DIALOG_BOX");
		IMAGE_DIALOG_BUTTON = aMgr.GetImageThrow("IMAGE_DIALOG_BUTTON");
		IMAGE_DISC = aMgr.GetImageThrow("IMAGE_DISC");
		IMAGE_EFFECTS = aMgr.GetImageThrow("IMAGE_EFFECTS");
		IMAGE_GOAL = aMgr.GetImageThrow("IMAGE_GOAL");
		IMAGE_INSTRUCTIONS = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS");
		IMAGE_MAIN_MENU = aMgr.GetImageThrow("IMAGE_MAIN_MENU");
		IMAGE_PLAYER_1 = aMgr.GetImageThrow("IMAGE_PLAYER_1");
		IMAGE_PLAYER_2 = aMgr.GetImageThrow("IMAGE_PLAYER_2");
		IMAGE_SLIDER_THUMB = aMgr.GetImageThrow("IMAGE_SLIDER_THUMB");
		IMAGE_SLIDER_TRACK = aMgr.GetImageThrow("IMAGE_SLIDER_TRACK");
		IMAGE_TABLE_1 = aMgr.GetImageThrow("IMAGE_TABLE_1");
		IMAGE_TABLE_2 = aMgr.GetImageThrow("IMAGE_TABLE_2");
		IMAGE_TABLE_3 = aMgr.GetImageThrow("IMAGE_TABLE_3");
		IMAGE_TABLE_4 = aMgr.GetImageThrow("IMAGE_TABLE_4");
		IMAGE_VICTORY = aMgr.GetImageThrow("IMAGE_VICTORY");
		SOUND_MUTATOR = aMgr.GetSoundThrow("SOUND_MUTATOR");
		SOUND_TIMER = aMgr.GetSoundThrow("SOUND_TIMER");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// Init Resources
Font* FrameworkX::FONT_DEFAULT;
Font* FrameworkX::FONT_NGAGE1;
Font* FrameworkX::FONT_NGAGE2;
Font* FrameworkX::FONT_NGAGE3;
Image* FrameworkX::IMAGE_CUSTOM_DRAGGING;
Image* FrameworkX::IMAGE_CUSTOM_HAND;
Image* FrameworkX::IMAGE_CUSTOM_POINTER;
Image* FrameworkX::IMAGE_CUSTOM_TEXT;
Image* FrameworkX::IMAGE_HUNGARR_LOGO;

bool FrameworkX::ExtractInitResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_DEFAULT = aMgr.GetFontThrow("FONT_DEFAULT");
		FONT_NGAGE1 = aMgr.GetFontThrow("FONT_NGAGE1");
		FONT_NGAGE2 = aMgr.GetFontThrow("FONT_NGAGE2");
		FONT_NGAGE3 = aMgr.GetFontThrow("FONT_NGAGE3");
		IMAGE_CUSTOM_DRAGGING = aMgr.GetImageThrow("IMAGE_CUSTOM_DRAGGING");
		IMAGE_CUSTOM_HAND = aMgr.GetImageThrow("IMAGE_CUSTOM_HAND");
		IMAGE_CUSTOM_POINTER = aMgr.GetImageThrow("IMAGE_CUSTOM_POINTER");
		IMAGE_CUSTOM_TEXT = aMgr.GetImageThrow("IMAGE_CUSTOM_TEXT");
		IMAGE_HUNGARR_LOGO = aMgr.GetImageThrow("IMAGE_HUNGARR_LOGO");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// TitleScreen Resources
Image* FrameworkX::IMAGE_LOADER_BAR;
Image* FrameworkX::IMAGE_LOADER_BAR_BASE;
Image* FrameworkX::IMAGE_LOADER_LOADINGTXT;
Image* FrameworkX::IMAGE_TITLE_SCREEN;
int FrameworkX::SOUND_CONTINUE;

bool FrameworkX::ExtractTitleScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_LOADER_BAR = aMgr.GetImageThrow("IMAGE_LOADER_BAR");
		IMAGE_LOADER_BAR_BASE = aMgr.GetImageThrow("IMAGE_LOADER_BAR_BASE");
		IMAGE_LOADER_LOADINGTXT = aMgr.GetImageThrow("IMAGE_LOADER_LOADINGTXT");
		IMAGE_TITLE_SCREEN = aMgr.GetImageThrow("IMAGE_TITLE_SCREEN");
		SOUND_CONTINUE = aMgr.GetSoundThrow("SOUND_CONTINUE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

static void* gResources[] =
{
	&FONT_DEFAULT,
	&FONT_NGAGE1,
	&FONT_NGAGE2,
	&FONT_NGAGE3,
	&IMAGE_CUSTOM_POINTER,
	&IMAGE_CUSTOM_HAND,
	&IMAGE_CUSTOM_DRAGGING,
	&IMAGE_CUSTOM_TEXT,
	&IMAGE_HUNGARR_LOGO,
	&IMAGE_LOADER_BAR,
	&IMAGE_LOADER_LOADINGTXT,
	&IMAGE_TITLE_SCREEN,
	&IMAGE_LOADER_BAR_BASE,
	&SOUND_CONTINUE,
	&SOUND_MUTATOR,
	&SOUND_TIMER,
	&IMAGE_MAIN_MENU,
	&IMAGE_INSTRUCTIONS,
	&IMAGE_CHECKBOX,
	&IMAGE_CHOOSE_ARENA,
	&IMAGE_TABLE_2,
	&IMAGE_TABLE_3,
	&IMAGE_TABLE_4,
	&IMAGE_BUTTON_DOWN,
	&IMAGE_BUTTON_OVER,
	&IMAGE_BUTTON_NORMAL,
	&IMAGE_CHOOSE_ARENA_BUTTON_DOWN,
	&IMAGE_CHOOSE_ARENA_BUTTON_OVER,
	&IMAGE_CHOOSE_ARENA_BUTTON_NORMAL,
	&IMAGE_DIALOG_BOX,
	&IMAGE_DIALOG_BUTTON,
	&IMAGE_SLIDER_TRACK,
	&IMAGE_SLIDER_THUMB,
	&IMAGE_PLAYER_1,
	&IMAGE_PLAYER_2,
	&IMAGE_DISC,
	&IMAGE_TABLE_1,
	&IMAGE_EFFECTS,
	&IMAGE_VICTORY,
	&IMAGE_DEFEAT,
	&IMAGE_GOAL,
	NULL
};

Image* FrameworkX::LoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image**)gResources[theId]) = theManager->LoadImage(GetStringIdById(theId)));
}

void FrameworkX::ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage)
{
	theManager->ReplaceImage(GetStringIdById(theId),theImage);
	*(Image**)gResources[theId] = theImage;
}

Image* FrameworkX::GetImageById(int theId)
{
	return *(Image**)gResources[theId];
}

Font* FrameworkX::GetFontById(int theId)
{
	return *(Font**)gResources[theId];
}

int FrameworkX::GetSoundById(int theId)
{
	return *(int*)gResources[theId];
}

Image*& FrameworkX::GetImageRefById(int theId)
{
	return *(Image**)gResources[theId];
}

Font*& FrameworkX::GetFontRefById(int theId)
{
	return *(Font**)gResources[theId];
}

int& FrameworkX::GetSoundRefById(int theId)
{
	return *(int*)gResources[theId];
}

static FrameworkX::ResourceId GetIdByVariable(const void *theVariable)
{
	typedef std::map<int,int> MyMap;
	static MyMap aMap;
	if(gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[*(int*)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((int)theVariable);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

FrameworkX::ResourceId FrameworkX::GetIdByImage(Image *theImage)
{
	return GetIdByVariable(theImage);
}

FrameworkX::ResourceId FrameworkX::GetIdByFont(Font *theFont)
{
	return GetIdByVariable(theFont);
}

FrameworkX::ResourceId FrameworkX::GetIdBySound(int theSound)
{
	return GetIdByVariable((void*)theSound);
}

const char* FrameworkX::GetStringIdById(int theId)
{
	switch(theId)
	{
		case FONT_DEFAULT_ID: return "FONT_DEFAULT";
		case FONT_NGAGE1_ID: return "FONT_NGAGE1";
		case FONT_NGAGE2_ID: return "FONT_NGAGE2";
		case FONT_NGAGE3_ID: return "FONT_NGAGE3";
		case IMAGE_CUSTOM_POINTER_ID: return "IMAGE_CUSTOM_POINTER";
		case IMAGE_CUSTOM_HAND_ID: return "IMAGE_CUSTOM_HAND";
		case IMAGE_CUSTOM_DRAGGING_ID: return "IMAGE_CUSTOM_DRAGGING";
		case IMAGE_CUSTOM_TEXT_ID: return "IMAGE_CUSTOM_TEXT";
		case IMAGE_HUNGARR_LOGO_ID: return "IMAGE_HUNGARR_LOGO";
		case IMAGE_LOADER_BAR_ID: return "IMAGE_LOADER_BAR";
		case IMAGE_LOADER_LOADINGTXT_ID: return "IMAGE_LOADER_LOADINGTXT";
		case IMAGE_TITLE_SCREEN_ID: return "IMAGE_TITLE_SCREEN";
		case IMAGE_LOADER_BAR_BASE_ID: return "IMAGE_LOADER_BAR_BASE";
		case SOUND_CONTINUE_ID: return "SOUND_CONTINUE";
		case SOUND_MUTATOR_ID: return "SOUND_MUTATOR";
		case SOUND_TIMER_ID: return "SOUND_TIMER";
		case IMAGE_MAIN_MENU_ID: return "IMAGE_MAIN_MENU";
		case IMAGE_INSTRUCTIONS_ID: return "IMAGE_INSTRUCTIONS";
		case IMAGE_CHECKBOX_ID: return "IMAGE_CHECKBOX";
		case IMAGE_CHOOSE_ARENA_ID: return "IMAGE_CHOOSE_ARENA";
		case IMAGE_TABLE_2_ID: return "IMAGE_TABLE_2";
		case IMAGE_TABLE_3_ID: return "IMAGE_TABLE_3";
		case IMAGE_TABLE_4_ID: return "IMAGE_TABLE_4";
		case IMAGE_BUTTON_DOWN_ID: return "IMAGE_BUTTON_DOWN";
		case IMAGE_BUTTON_OVER_ID: return "IMAGE_BUTTON_OVER";
		case IMAGE_BUTTON_NORMAL_ID: return "IMAGE_BUTTON_NORMAL";
		case IMAGE_CHOOSE_ARENA_BUTTON_DOWN_ID: return "IMAGE_CHOOSE_ARENA_BUTTON_DOWN";
		case IMAGE_CHOOSE_ARENA_BUTTON_OVER_ID: return "IMAGE_CHOOSE_ARENA_BUTTON_OVER";
		case IMAGE_CHOOSE_ARENA_BUTTON_NORMAL_ID: return "IMAGE_CHOOSE_ARENA_BUTTON_NORMAL";
		case IMAGE_DIALOG_BOX_ID: return "IMAGE_DIALOG_BOX";
		case IMAGE_DIALOG_BUTTON_ID: return "IMAGE_DIALOG_BUTTON";
		case IMAGE_SLIDER_TRACK_ID: return "IMAGE_SLIDER_TRACK";
		case IMAGE_SLIDER_THUMB_ID: return "IMAGE_SLIDER_THUMB";
		case IMAGE_PLAYER_1_ID: return "IMAGE_PLAYER_1";
		case IMAGE_PLAYER_2_ID: return "IMAGE_PLAYER_2";
		case IMAGE_DISC_ID: return "IMAGE_DISC";
		case IMAGE_TABLE_1_ID: return "IMAGE_TABLE_1";
		case IMAGE_EFFECTS_ID: return "IMAGE_EFFECTS";
		case IMAGE_VICTORY_ID: return "IMAGE_VICTORY";
		case IMAGE_DEFEAT_ID: return "IMAGE_DEFEAT";
		case IMAGE_GOAL_ID: return "IMAGE_GOAL";
		default: return "";
	}
}

