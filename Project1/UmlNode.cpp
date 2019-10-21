/**
 * \file UmlNode.cpp
 *
 * \author Team Hoare
 */

#include "pch.h"
#include "item.h"
#include "UmlGame.h"
#include "UmlNode.h"
#include "XmlNode.h"
#include "UmlGood.h"
#include "UmlBad.h"
#include "ChildView.h"
#include "UmlData.h"
#include "PlayingArea.h"

#include <algorithm>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;



/// The rectangle used to determine size of node
RectF textRect;

/// The initilization of the text size rectangle
PointF* origin = new PointF(0.0f, 0.0f);

/// Space to put at the end of a node (width)
const int X_PADDING = 16;
/// Space to put at the end of a node (height)
const int Y_PADDING = 24;

/// space after lines in UML node
const int LINE_PADDING = 20;

/// for empty nodes
const int EMPTY_SPACING = 50;

/// Area we are working with
CPlayingArea* area;

/// default filename
const wstring filename = L"";

/**
 * Calculates or simply returns the height of the node
 * \returns the pixel height of the node
 */
double CUmlNode::GetNodeHeight()
{
	if (mNodeHeight > 0)
	{
		return mNodeHeight;
	}
	//	The font of writing in uml node
	FontFamily fontFamily(L"Arial");
	//	The font size of the uml node
	Gdiplus::Font font(&fontFamily, 12);

	mPlayingArea->GetGame()->GetGraphics()->MeasureString(L"Hello", -1, &font, *origin, &textRect);

	mNodeHeight = (mAttributes.size() + mOperations.size() + 1.0f)*textRect.Height;
	
	if ((mOperations.size() == 0 ) & (mAttributes.size() == 0))
	{
		mNodeHeight += EMPTY_SPACING;
	}
	
	return mNodeHeight;
}



/**
 * Calculates or simply returns the width of the node
 * \returns the pixel width of the node
 */
double CUmlNode::GetNodeWidth()
{
	if (mNodeWidth > 0)
	{
		return mNodeWidth;
	}

	// the font of text in uml node
	FontFamily fontFamily(L"Arial");

	// The font size of uml node text
	Gdiplus::Font font(&fontFamily, 12);


	//	Set maximum chars of the umlnode to that of the class name
	mPlayingArea->GetGame()->GetGraphics()->MeasureString(mName[0].GetDataValue().c_str(), -1, &font, *origin, &textRect);
	double max = textRect.Width;

	// Loop through all attributes 
	for (unsigned int i = 0; i < mAttributes.size(); i++)
	{
		// If the attribute's description is longer
		mPlayingArea->GetGame()->GetGraphics()->MeasureString(mAttributes[i].GetDataValue().c_str(), -1, &font, *origin, &textRect);
		if (textRect.Width > max)
		{
			max = textRect.Width;
		}
	}
	// Loop through all operations 
	for (unsigned int i = 0; i < mOperations.size(); i++)
	{
		// If the operation's description is longer than the longest we've seen so far
		mPlayingArea->GetGame()->GetGraphics()->MeasureString(mOperations[i].GetDataValue().c_str(), -1, &font, *origin, &textRect);
		if (textRect.Width> max)
		{
			max = textRect.Width;
		}
	}

	if ((mOperations.size() == 0) & (mAttributes.size() == 0))
	{
		max += EMPTY_SPACING;
	}

	mNodeWidth = max;
	return max;
}


/**
 * Constructor
 * \param game The game that the UmlNode belongs to.
 */
CUmlNode::CUmlNode(CUmlGame &game)	: CMovingItem(game.GetPlayingArea().get(), filename)
{

}


void CUmlNode::Update(double elapsed)
{
	SetLocation(GetX() + GetXSpeed() * elapsed, GetY() + GetYSpeed() * elapsed);
}


/**
 * Draws a CUmlNode with class name, attributes, and operations
 * \param graphics the graphics context to draw with
 */
void CUmlNode::Draw(Gdiplus::Graphics* graphics)
{
	// The pen used to Draw uml boundary
	Pen pen(Color(0, 0, 0), 3);

	// The pen used to draw lines in Umlnode
	Pen black(Color(0, 0, 0));

	// The brush used to paint the node
	SolidBrush brush(Color(250, 250, 180));

	// The brush used to paint the text
	SolidBrush text(Color(0, 0, 0));

	// the font family of the text in uml node
	FontFamily fontFamily(L"Arial");

	// The bolded font object for writing the name in uml node in uml node
	Gdiplus::Font nameFont(&fontFamily, 12, FontStyleBold);

	// The font object for writing attributes and operations in uml node
	Gdiplus::Font font(&fontFamily, 12);

	// Determine the text height
	graphics->MeasureString(L"Hello", -1, &font, *origin, &textRect);
	double textHeight = (double)textRect.Height;

	// Get the class name's text width
	graphics->MeasureString
	(
		mName[0].GetDataValue().c_str(),
		-1,
		&font,
		*origin,
		&textRect
	);
	double textWidth = (double)textRect.Width;

	// pixel width of node
	double nodeWidth = GetNodeWidth();
	// pixel height of node
	double nodeHeight = GetNodeHeight();

	// Draw the UmlNode rectangle
	graphics->DrawRectangle
	(
		&pen, 
		(int)GetX(),
		(int)GetY(), 
		(int)nodeWidth + X_PADDING, 
		(int)nodeHeight + Y_PADDING
	);

	//	Fill the rectangle
	graphics->FillRectangle
	(
		&brush, 
		(int)GetX(),
		(int)GetY(), 
		(int)nodeWidth + X_PADDING, 
		(int)nodeHeight + Y_PADDING
	);

	//	Line drawn after the name section
	graphics->DrawLine
	(
		&black,
		(int)GetX(),
		(int)GetY() + (mName.size() + 1) + Y_PADDING,
		(int)GetX() + (int)nodeWidth + X_PADDING,
		(int)GetY() + (mName.size() + 1) + Y_PADDING
	);

	//	Line drawn after the attributes section
	if (	(mAttributes.size() > 0)	&&	(mOperations.size() > 0)	)
	{
		graphics->DrawLine
		(
			&black, 
			(int)GetX(), 
			(int)GetY() + (int)textHeight*(mAttributes.size()+1) + Y_PADDING, 
			(int)GetX() + (int)nodeWidth + X_PADDING, 
			(int)GetY() + (int)textHeight * (mAttributes.size()+1) + Y_PADDING
		);
	}

	
	// Draw the Class Name
	graphics->DrawString
	(
		mName[0].GetDataValue().c_str(),								// String to draw
		-1,																// String length, -1 means inherit from size of input
		&nameFont,														// The font to use
		PointF															// Where to draw (top left corner)
		(
			(Gdiplus::REAL)(GetX() + (nodeWidth/2) - (textWidth/2)), 
			(Gdiplus::REAL)GetY()
		),											
		&text															// The brush to draw the text with
	);    
	
	// Draw the attributes 
	for (unsigned int i = 0; i < mAttributes.size(); i++)
	{
		graphics->DrawString
		(
			mAttributes[i].GetDataValue().c_str(),						// String to draw
			-1,															// String length, -1 means inherit from size of input
			&font,														// The font to use
			PointF														// Where to draw (top left corner)
			(
				(Gdiplus::REAL)(GetX()), 
				(Gdiplus::REAL)(GetY() + textHeight*(i + 1.0f) + LINE_PADDING)
			),			
			&text														// The brush to draw the text with
		);
	}

	// Draw the operations line by line
	for (unsigned int i = 0; i < mOperations.size(); i++)
	{
		if (mAttributes.size())
		{
			graphics->DrawString
			(
				mOperations[i].GetDataValue().c_str(),					// String to draw
				-1,														// String length, -1 means inherit from size of input
				&font,													// The font to use
				PointF													// Where to draw (top left corner
				(
					(Gdiplus::REAL)(GetX()),
					(Gdiplus::REAL)(GetY() + (mAttributes.size() * textHeight) + (textHeight * (i + 1.0f)) + LINE_PADDING)
				),
				&text													// The brush to draw the text with
			);
		}
		else
		{
			graphics->DrawString
			(
				mOperations[i].GetDataValue().c_str(),					// String to draw
				-1,														// String length, -1 means inherit from size of input
				&font,													// The font to use
				PointF													// Where to draw (top left corner
				(
					(Gdiplus::REAL)(GetX()),
					(Gdiplus::REAL)(GetY() + (mAttributes.size() * textHeight) + (textHeight * (i + 1.0f)) + LINE_PADDING)
				),
				&text													// The brush to draw the text with
			);
		}
	}
}



