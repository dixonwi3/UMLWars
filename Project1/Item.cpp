/**
 * \file Item.cpp
 *
 * \author Team Hoare
 */

#include "pch.h"
#include "Item.h"
#include <string>

using namespace Gdiplus;
using namespace std;



/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/**
* Constructor
* \param playingArea The playing area we are using
*/
CItem::CItem(CPlayingArea* playingArea) : mPlayingArea(playingArea)
{
}


/**
* Destructor
*/
CItem::~CItem()
{

}

/**
 *  Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return bool if hit.
 */
bool CItem::HitTest(int x, int y)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image.
	// Subtracting the center makes x, y relative to the center of 
	// the image. Adding half the size makes x, y relative to the top 
	// corner of the image.
	double testX = x - mVector.X()+ wid / 2;
	double testY = y - mVector.Y() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mItemImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mItemImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}

