#pragma once
#include "PrimitiveModel.h"
class Text :
	public Component
{
public:
	Text(int height, int width, bool italic = false);
	~Text();

	void Update();
	void Draw();
	void SetHeight(int y)							{ mFormatRect.top =y; }
	void SetText(LPCSTR text)						{ mText = text; }
	void SetColor(int r, int g, int b)				{ mColor = D3DCOLOR_XRGB(r, g, b); mR = r; mG = g; mB = b; }
	void SetColor(int a, int r, int g, int b)		{ mColor = D3DCOLOR_ARGB(a, r, g, b); mA = a; mR = r; mG = g; mB = b; }
	void SetFlashing(bool toggle)					{ mIsFlashing = toggle; }

private:
	Text();

	ID3DXFont* mFont;

	LPCSTR mText;
	D3DXFONT_DESC mFontDesc;
	RECT mFormatRect;
	D3DCOLOR mColor;

	bool mIsFlashing;
	float mFadeInTimer;
	float mFadeInSpeed;
	bool mIsFadingIn;
	int mA;
	int mR;
	int mG;
	int mB;

};