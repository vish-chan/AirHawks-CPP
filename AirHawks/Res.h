#ifndef __Res_H__
#define __Res_H__

namespace FrameworkX
{
	class ResourceManager;
	class Image;
	class Font;

	Image* LoadImageById(ResourceManager *theManager, int theId);
	void ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage);
	bool ExtractResourcesByName(ResourceManager *theManager, const char *theName);

	// Game Resources
	bool ExtractGameResources(ResourceManager *theMgr);
	extern Image* IMAGE_BUTTON_DOWN;
	extern Image* IMAGE_BUTTON_NORMAL;
	extern Image* IMAGE_BUTTON_OVER;
	extern Image* IMAGE_CHECKBOX;
	extern Image* IMAGE_CHOOSE_ARENA;
	extern Image* IMAGE_CHOOSE_ARENA_BUTTON_DOWN;
	extern Image* IMAGE_CHOOSE_ARENA_BUTTON_NORMAL;
	extern Image* IMAGE_CHOOSE_ARENA_BUTTON_OVER;
	extern Image* IMAGE_DEFEAT;
	extern Image* IMAGE_DIALOG_BOX;
	extern Image* IMAGE_DIALOG_BUTTON;
	extern Image* IMAGE_DISC;
	extern Image* IMAGE_EFFECTS;
	extern Image* IMAGE_GOAL;
	extern Image* IMAGE_INSTRUCTIONS;
	extern Image* IMAGE_MAIN_MENU;
	extern Image* IMAGE_PLAYER_1;
	extern Image* IMAGE_PLAYER_2;
	extern Image* IMAGE_SLIDER_THUMB;
	extern Image* IMAGE_SLIDER_TRACK;
	extern Image* IMAGE_TABLE_1;
	extern Image* IMAGE_TABLE_2;
	extern Image* IMAGE_TABLE_3;
	extern Image* IMAGE_TABLE_4;
	extern Image* IMAGE_VICTORY;
	extern int SOUND_MUTATOR;
	extern int SOUND_TIMER;

	// Init Resources
	bool ExtractInitResources(ResourceManager *theMgr);
	extern Font* FONT_DEFAULT;
	extern Font* FONT_NGAGE1;
	extern Font* FONT_NGAGE2;
	extern Font* FONT_NGAGE3;
	extern Image* IMAGE_CUSTOM_DRAGGING;
	extern Image* IMAGE_CUSTOM_HAND;
	extern Image* IMAGE_CUSTOM_POINTER;
	extern Image* IMAGE_CUSTOM_TEXT;
	extern Image* IMAGE_HUNGARR_LOGO;

	// TitleScreen Resources
	bool ExtractTitleScreenResources(ResourceManager *theMgr);
	extern Image* IMAGE_LOADER_BAR;
	extern Image* IMAGE_LOADER_BAR_BASE;
	extern Image* IMAGE_LOADER_LOADINGTXT;
	extern Image* IMAGE_TITLE_SCREEN;
	extern int SOUND_CONTINUE;

	enum ResourceId
	{
		FONT_DEFAULT_ID,
		FONT_NGAGE1_ID,
		FONT_NGAGE2_ID,
		FONT_NGAGE3_ID,
		IMAGE_CUSTOM_POINTER_ID,
		IMAGE_CUSTOM_HAND_ID,
		IMAGE_CUSTOM_DRAGGING_ID,
		IMAGE_CUSTOM_TEXT_ID,
		IMAGE_HUNGARR_LOGO_ID,
		IMAGE_LOADER_BAR_ID,
		IMAGE_LOADER_LOADINGTXT_ID,
		IMAGE_TITLE_SCREEN_ID,
		IMAGE_LOADER_BAR_BASE_ID,
		SOUND_CONTINUE_ID,
		SOUND_MUTATOR_ID,
		SOUND_TIMER_ID,
		IMAGE_MAIN_MENU_ID,
		IMAGE_INSTRUCTIONS_ID,
		IMAGE_CHECKBOX_ID,
		IMAGE_CHOOSE_ARENA_ID,
		IMAGE_TABLE_2_ID,
		IMAGE_TABLE_3_ID,
		IMAGE_TABLE_4_ID,
		IMAGE_BUTTON_DOWN_ID,
		IMAGE_BUTTON_OVER_ID,
		IMAGE_BUTTON_NORMAL_ID,
		IMAGE_CHOOSE_ARENA_BUTTON_DOWN_ID,
		IMAGE_CHOOSE_ARENA_BUTTON_OVER_ID,
		IMAGE_CHOOSE_ARENA_BUTTON_NORMAL_ID,
		IMAGE_DIALOG_BOX_ID,
		IMAGE_DIALOG_BUTTON_ID,
		IMAGE_SLIDER_TRACK_ID,
		IMAGE_SLIDER_THUMB_ID,
		IMAGE_PLAYER_1_ID,
		IMAGE_PLAYER_2_ID,
		IMAGE_DISC_ID,
		IMAGE_TABLE_1_ID,
		IMAGE_EFFECTS_ID,
		IMAGE_VICTORY_ID,
		IMAGE_DEFEAT_ID,
		IMAGE_GOAL_ID,
		RESOURCE_ID_MAX
	};

	Image* GetImageById(int theId);
	Font* GetFontById(int theId);
	int GetSoundById(int theId);

	Image*& GetImageRefById(int theId);
	Font*& GetFontRefById(int theId);
	int& GetSoundRefById(int theId);

	ResourceId GetIdByImage(Image *theImage);
	ResourceId GetIdByFont(Font *theFont);
	ResourceId GetIdBySound(int theSound);
	const char* GetStringIdById(int theId);
	ResourceId GetIdByStringId(const char *theStringId);

} // namespace FrameworkX


#endif
