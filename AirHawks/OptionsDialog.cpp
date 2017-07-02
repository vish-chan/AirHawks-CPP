#include "OptionsDialog.h"
#include "Res.h"
#include "cGame.h"
#include "SexyAppFramework/XAppBase.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Checkbox.h"
#include "SexyAppFramework/Slider.h"

using namespace FrameworkX;

OptionsDialog::OptionsDialog(std::string theHeader, std::string theBody)
:Dialog(IMAGE_DIALOG_BOX, IMAGE_DIALOG_BUTTON, OptionsDialog::DIALOG_ID, true, StringToSexyStringFast(theHeader), StringToSexyStringFast(theBody), _S("CLOSE"), Dialog::BUTTONS_FOOTER)
{
	mWidgetFlagsMod.mAddFlags |= WIDGETFLAGS_MARK_DIRTY;
   mContentInsets = Insets(20,20,20,20);   //set insets
   mSpaceAfterHeader = 30;                 //set space after header

   /* set fonts for various sections */
   SetHeaderFont(FONT_DEFAULT);             
   SetLinesFont(FONT_DEFAULT);
   SetButtonFont(FONT_DEFAULT);

   /* set colours for various sections */
   SetColor(COLOR_HEADER, Color::Black);
   SetColor(COLOR_LINES, Color::Black);
   

   //create musicvolume slider
   mMusicVolumeSlider = new Slider(IMAGE_SLIDER_TRACK, IMAGE_SLIDER_THUMB, OptionsDialog::MUSIC_SLIDER_ID, this);
   mMusicVolumeSlider->SetValue(gSexyAppBase->GetMusicVolume());
   AddWidget(mMusicVolumeSlider);

   //create sound effects volume slider
   mSfxVolumeSlider = new Slider(IMAGE_SLIDER_TRACK, IMAGE_SLIDER_THUMB, OptionsDialog::SFX_SLIDER_ID, this);
   mSfxVolumeSlider->SetValue(gSexyAppBase->GetSfxVolume());
   AddWidget(mSfxVolumeSlider);


   //create checkboxes for 3d and fullscreen
   m3DCheckbox = new Checkbox(IMAGE_CHECKBOX, IMAGE_CHECKBOX, OptionsDialog::HARDWARE_CHECKBOX_ID, this);
   mFSCheckbox = new Checkbox(IMAGE_CHECKBOX, IMAGE_CHECKBOX, OptionsDialog::FS_CHECKBOX_ID, this);

   int checkWidth = IMAGE_CHECKBOX->GetWidth() / 2;
   int checkHeight = IMAGE_CHECKBOX->GetHeight(); 
   
   //define unchecked and checked part of images
   m3DCheckbox->mUncheckedRect = Rect(0, 0, checkWidth,checkHeight );
   m3DCheckbox->mCheckedRect = Rect(checkWidth, 0, checkWidth,checkHeight);

   mFSCheckbox->mUncheckedRect = Rect(0, 0, checkWidth, checkHeight);
   mFSCheckbox->mCheckedRect = Rect(checkWidth, 0, checkWidth, checkHeight);

   //set init values
   m3DCheckbox->mChecked = gSexyAppBase->Is3DAccelerated();
   mFSCheckbox->mChecked = !gSexyAppBase->mIsWindowed;

   AddWidget(m3DCheckbox);
   AddWidget(mFSCheckbox);
}

OptionsDialog::~OptionsDialog()
{
   RemoveAllWidgets();
   delete mMusicVolumeSlider;
   delete mSfxVolumeSlider;
   delete m3DCheckbox;
   delete mFSCheckbox;
}

void OptionsDialog::Draw(Graphics* g)
{
   Dialog::Draw(g);  //Draws dialogbox 

	g->SetFont(FONT_DEFAULT);
	g->SetColor(Color::Black);
	g->DrawString(_S("Music volume:"), mMusicVolumeSlider->mX, 
			mMusicVolumeSlider->mY - mMusicVolumeSlider->mHeight);

	g->DrawString(_S("Sound volume:"), mSfxVolumeSlider->mX, 
			mSfxVolumeSlider->mY - mSfxVolumeSlider->mHeight);

	g->DrawString(_S("3D Mode:"), m3DCheckbox->mX, m3DCheckbox->mY- m3DCheckbox->mHeight + 20);
	g->DrawString(_S("Full Screen:"), mFSCheckbox->mX, mFSCheckbox->mY - mFSCheckbox->mHeight + 20);

}

void OptionsDialog::Update()
{
   Dialog::Update();
}


void OptionsDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
	Dialog::Resize(theX, theY, theWidth, theHeight);
	mMusicVolumeSlider->Resize(mContentInsets.mLeft, 140,mWidth - mContentInsets.mLeft - mContentInsets.mRight, IMAGE_SLIDER_THUMB->GetHeight());
	mSfxVolumeSlider->Layout(LAY_SameLeft | LAY_Below | LAY_SameWidth | LAY_SameHeight, 
								mMusicVolumeSlider, 0, 40, 0, 0);

	m3DCheckbox->Layout(LAY_SameLeft | LAY_Below, mSfxVolumeSlider, 0, 40, 0, 0);
	m3DCheckbox->Resize(m3DCheckbox->mX, m3DCheckbox->mY,
						IMAGE_CHECKBOX->mWidth / 2, IMAGE_CHECKBOX->mHeight);

	mFSCheckbox->Layout(LAY_SameTop | LAY_SameWidth | LAY_SameHeight, m3DCheckbox);
	mFSCheckbox->Resize(m3DCheckbox->mX + 200, mFSCheckbox->mY,
						mFSCheckbox->mWidth, mFSCheckbox->mHeight);


}


void OptionsDialog::SliderVal(int theId, double theVal)
{
	if (theId == OptionsDialog::MUSIC_SLIDER_ID)
	{
		// Let's set the music volume to whatever the slider position is
		gSexyAppBase->SetMusicVolume(theVal);
	}
	else if (theId == OptionsDialog::SFX_SLIDER_ID)
	{
		// Set the sound value
		gSexyAppBase->SetSfxVolume(theVal);

		//play a ding sound when slider is released
		if (!mSfxVolumeSlider->mDragging)
			gSexyAppBase->PlaySample(SOUND_TIMER);
	}
}




void OptionsDialog::CheckboxChecked(int theId, bool checked)
{
	// We'll wait until the dialog box is closed before actually applying any effects,
	// since it's rather jarring if as soon as a user clicks the 3d or fullscreen
	// toggle buttons to change right then and there.

	if (theId == m3DCheckbox->mId)
	{
		if (checked)
		{
			if (!gSexyAppBase->Is3DAccelerationSupported())
			{
				m3DCheckbox->SetChecked(false);
				gSexyAppBase->DoDialog(OptionsDialog::MESSAGE_BOX_ID, true, _S("Not Supported"), 
							_S("Hardware acceleration can not be enabled on this computer. \nYour\
							video card does not meet the minimum requirements for this game."),
							_S("OK"), Dialog::BUTTONS_FOOTER);
			}
			else if(!gSexyAppBase->Is3DAccelerationRecommended())
			{
				gSexyAppBase->DoDialog(OptionsDialog::MESSAGE_BOX_ID, true, _S("Warning"), 
					_S("Your video card may not fully support this feature.\n\
					If you experience slower performance, please disable Hardware Acceleration."),
					_S("OK"), Dialog::BUTTONS_FOOTER);
			}
			
		}
	}
	else if (theId == mFSCheckbox->mId)
	{
		if (gSexyAppBase->mForceFullscreen && !checked)
		{
			gSexyAppBase->DoDialog(OptionsDialog::MESSAGE_BOX_ID, true, _S("No Windowed Mode"),
			_S("Windowed mode is only available if your desktop is running in\n\
			either 16 bit or 32 bit color mode, which it is not."), _S("OK"), Dialog::BUTTONS_FOOTER);

			// re-check the box to indicate that fullscreen is still the selected mode:
			mFSCheckbox->SetChecked(true);
		}
	}
}

