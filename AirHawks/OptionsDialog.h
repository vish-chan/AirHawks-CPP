#ifndef _OPTIONS_DIALOG_H_
#define _OPTIONS_DIALOG_H_

#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/SliderListener.h"
#include "SexyAppFramework/CheckboxListener.h"

namespace FrameworkX
{

	class Graphics;
	class Slider;
	class Checkbox;

class OptionsDialog : public Dialog, public SliderListener, public CheckboxListener
{
	
	protected:

		Slider*			mMusicVolumeSlider;
		Slider*			mSfxVolumeSlider;	


	public:
		enum
		{
			MUSIC_SLIDER_ID,
			SFX_SLIDER_ID,
			FS_CHECKBOX_ID,
			HARDWARE_CHECKBOX_ID,
			MESSAGE_BOX_ID,
			DIALOG_ID
		};

		//declared in public section so that mApp can access them directly
		Checkbox*		m3DCheckbox;			// Toggle 3D enhanced mode
		Checkbox*		mFSCheckbox;			// Toggle fullscreen mode

	
	public:	
		OptionsDialog(std::string theHeader, std::string theBody);
		virtual ~OptionsDialog();
		virtual void Draw(Graphics* g);
		virtual void Update();	
		//virtual void ButtonDepress(int theId);		
		virtual void Resize(int theX, int theY, int theWidth, int theHeight);
		virtual void SliderVal(int theId, double theVal); //slider event handler
		void CheckboxChecked(int theId, bool checked);       //CheckBox event handler
};
}
#endif