#include "Text.h"

const float FADE_IN_SPEED = 0.042f;
const float DELTA_TIME_COEFF = 10;

Text::Text(int height, int width, bool italic)
: Component()
, mText("")
, mFormatRect({ 0, 0, 800, 600 })
, mIsFlashing(false)
, mIsFadingIn(false)
, mFadeInSpeed(FADE_IN_SPEED)
, mFadeInTimer(0)
, mA(255)
, mR(255)
, mB(0)
, mG(0)
{
	mFontDesc.Height = height;
	mFontDesc.Width = width;
	mFontDesc.Weight = FW_BOLD;
	mFontDesc.MipLevels = 0;
	mFontDesc.Italic = italic;
	mFontDesc.CharSet = DEFAULT_CHARSET;
	mFontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	mFontDesc.Quality = DEFAULT_QUALITY;
	mFontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy(mFontDesc.FaceName, _T("Times New Roman"));

	D3DXCreateFontIndirect(gD3DDevice, &mFontDesc, &mFont);
	mColor = D3DCOLOR_XRGB(255, 0, 0);
}

void Text::Update()
{
	if (mIsFlashing)
	{
		mFadeInTimer += DELTA_TIME_COEFF*gTimer->GetDeltaTime();
		if (mFadeInTimer >= mFadeInSpeed)
		{
			mFadeInTimer -= mFadeInSpeed;
			if (mIsFadingIn)
			{
				mFadeInTimer -= mFadeInSpeed;
				if (this->mA + 1 <= 255)
				{
					this->mA += 1;
				}
				else
				{
					mIsFadingIn = false;
				}
			}
			else
			{
				if (this->mA - 1 > 0)
				{
					this->mA -= 1;
				}
				else
				{
					mIsFadingIn = true;
				}
			}
			SetColor(mA, mR, mG, mB);
		}
	}
}


Text::~Text()
{
	ReleaseCOM(mFont);
}

void Text::Draw()
{
	mFont->DrawText(0, _T(mText), -1,
		&mFormatRect, DT_CENTER | DT_VCENTER,
		mColor);
}
