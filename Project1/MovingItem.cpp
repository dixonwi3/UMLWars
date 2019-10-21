/**
 * \file MovingItem.cpp
 *
 * \author Team Hoare
 */


#include "pch.h"
#include "MovingItem.h"




using namespace std;
using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

CMovingItem::~CMovingItem()
{
}


/**
* Draw this item
* \param graphics The graphics context to draw on
*/
void CMovingItem::Draw(Gdiplus::Graphics* graphics)
{
	float wid = (float)mMovingItem->GetWidth();
	float hit = (float)mMovingItem->GetHeight();

	auto state = graphics->Save();
	graphics->TranslateTransform((float)GetX(), (float)GetY());
	graphics->RotateTransform((float)(-GetAngle() * RtoD));
	graphics->DrawImage(mMovingItem.get(), -wid / 2, -hit / 2,
		wid, hit);
	graphics->Restore(state);
}

CMovingItem::CMovingItem(CPlayingArea* area, std::wstring filename) : CItem(area)
{
	mMovingItem = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mMovingItem->GetLastStatus() != Ok && filename != L"")
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}
