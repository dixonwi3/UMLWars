/**
 * \file PlayingArea.cpp
 *
 * \author Team Hoare
 */

#include "pch.h"
#include <math.h>
#include "PlayingArea.h"
#include "UmlGame.h"
#include "UmlNodeVisitor.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>

using namespace Gdiplus;
using namespace std;


/// Pen speed in pixels per second
const int penSpeed = 1000;
///	Spacing band around UML node
const double band = 10;


/**
 * Constructor
 * \param game The UmlGame object associated with the playing area 
 * \param board The scoreboard associated with the playing area
 */
CPlayingArea::CPlayingArea(CUmlGame * game, std::shared_ptr<CScoreboard> board) : mGame(game), mScoreboard(board)
{
	mGrader = make_shared<CGrader>(this);
	Add(mGrader);

	mGraderPen = make_shared<CGraderPen>(this);
	Add(mGraderPen);
}




/**
 * Adds a node to the playing Area
 * \param node The node to add
 */
void CPlayingArea::AddNode(std::shared_ptr<CUmlNode> node)
{
	mItems.push_back(node);
	mNumNodes++;
}


/**
 * Gets the number of nodes in the playing area.
 * \returns the number of nodes in the playing area
 */
int CPlayingArea::NumNodes()
{
	return mNumNodes;
}


/**
 * Remove a node from the playing area
 * \param node The node to remove
 */
void CPlayingArea::RemoveNode(std::shared_ptr<CUmlNode> node)
{
	auto loc = find(mItems.begin(), mItems.end(), node);
	if (loc != mItems.end())
	{
		mItems.erase(loc);
		mNumNodes--;
	}
}


/**
 * Add an item to the playing area
 * \param item The item to add
 */
void CPlayingArea::Add(shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
 * Destructor
 */
CPlayingArea::~CPlayingArea()
{
}


/**
 * Draws each item in the playing area
 * \param graphics The graphics context to draw with
 */
void CPlayingArea::OnDraw(Gdiplus::Graphics* graphics)
{
	// Draw the items on the playing area
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
}


/**
 * Handle a mouse move message
 *
 * Point the grader towards the mouse location
 * and angle the pen.
 *
 * \param x X location of mouse
 * \param y Y location of mouse
 */
void CPlayingArea::OnMouseMove(double x, double y)
{
	// Get the rotation angle of the point
	double opposite = mGrader->GetX() - x;
	double adjacent = mGrader->GetY() - y;
	double angle = atan(opposite / adjacent);

	// Check so the grader doesn't turn
	// the opposite direction of the mouse
	// when the mouse is under him
	if (y >= mGrader->GetY())
	{
		angle = -angle;
	}

	// Set the new angle for grader
	mGrader->SetAngle(angle - mGraderPen->Angle / 2.0f);
}




/**
 * Sends the pen out when the left mouse button goes down
 * \param x The x coordinate of the mouse at the time the button was pressed
 * \param y The y coordinate of the mouse at the time the button was pressed
 */
void CPlayingArea::OnLButtonDown(double x, double y)
{
	CVector mousePosition(x, y);
	CVector direction = mousePosition - mGraderPen->GetPositionVector();
	direction = direction.Normalize();

	// if the pen is frozen (has hit a node in the past second), don't emit it
	if (!mFreeze)
	{
		PenEmit(direction);
	}
}


/**
 * Update the playing area and all items in it
 *
 * \param outsided the constant to reset the pen if it goes outside the bounds of the screen
 */
void CPlayingArea::Update(double outsided)
{
	// update every item in the playing area
	for (auto item : mItems)
	{
		item->Update(outsided);
	}

	// update the playing area in specific detail
	UpdateDetail(outsided);
}

/**
 * Hit testing for items
 */
std::shared_ptr<CItem> CPlayingArea::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}
	return  nullptr;
}


/**
 * Emits the pen
 * \param direction the direction to emit the pen in
 */
void CPlayingArea::PenEmit(CVector direction)
{
	// if the pen isn't already currently being emitted
	if (!mEmission)
	{
		mGraderPen->SetSpeed(penSpeed * direction.X(), penSpeed * direction.Y());
		mEmission = !mEmission;
	}
}


/**
 * Update the playing area in detail
 * \param outsided The constant to reset the pen if it goes outside the bounds of the screen
 */
void CPlayingArea::UpdateDetail(double outsided)
{
	vector<CUmlNode *> toDelete;

	//	If our pen has been shot and is within bounds
	if (mEmission && mGraderPen->GetX() < CUmlGame::Width / 2 && mGraderPen->GetX() > -CUmlGame::Width / 2
		&& mGraderPen->GetY() < CUmlGame::Height && mGraderPen->GetY() > 0)
	{
		//	Set the location of the pen to the appropriate X, Y value
		mGraderPen->SetLocation(mGraderPen->GetX() + mGraderPen->GetXSpeed() * outsided, mGraderPen->GetY() + mGraderPen->GetYSpeed() * outsided);
		
		//	Iterate through temporary list of nodes that are in mItems
		for (auto node : GetNodes())
		{
			//	Check for a collision using X, Y values for both as well as node dimensions
			if ((mGraderPen->GetX() < (node->GetX() + node->GetNodeWidth() + band)) &&
				(mGraderPen->GetX() > (node->GetX() - band)) &&
				(mGraderPen->GetY() < (node->GetY() + node->GetNodeHeight() + band)) &&
				(mGraderPen->GetY() > (node->GetY() - band)))
			{

				//	We have collided with a node in the playing area
				//	Set bool to false as we don't want to register any more hits until we shoot again
				mEmission = false;

				mFreeze = true;
				mFreezeBegin = clock();

				//	Stop the pen in place by dropping the X, Y speed both to 0
				mGraderPen->SetSpeed(0, 0);
				//	Also stop the node we just hit in place by dropping the X, Y speed both to 0
				node->SetSpeed(0, 0);
				mFrozenNode = node;

				// if we hit a Good node
				if (node->GetMessageW() == L"Unfair!")
				{
					mScoreboard->RaiseUnfair();
				}
				// if we hit a bad node
				else
				{
					mScoreboard->RaiseCorrect();
				}
				break;
			}
		}
	}
	// if the pen is out of bounds
	else
	{
		// if the pen isn't frozen (hit a node in the last second)
		if (!mFreeze)
		{
			//	We missed all UML nodes currently on screen
			//	Disable emission status, 
			mEmission = false;
			mGraderPen->SetSpeed(0, 0);

			//	Find the offsets of the pen relative
			//	to the grader's rotation angle
			double xOffset = mGraderPen->DistancePG * cos(GetGrader()->GetAngle() - mGraderPen->Angle);
			double yOffset = mGraderPen->DistancePG * sin(GetGrader()->GetAngle() - mGraderPen->Angle);

			//	Update angle and location of Pen
			mGraderPen->SetAngle(GetGrader()->GetAngle() + mGraderPen->Angle);
			mGraderPen->SetLocation(xOffset, GetGrader()->GetY() - yOffset);
		}
	}

	// if a node was recently hit
	if (mFreeze)
	{
		mFreezeEnd = clock();
		double elapsed_secs = double((long)(mFreezeEnd - mFreezeBegin)) / CLOCKS_PER_SEC;

		// if it been 1 second since it was hit
		if (elapsed_secs > 1)
		{
			//	Add it to the list of nodes to delete
			toDelete.push_back(mFrozenNode);
			mFreeze = false;
			mFrozenNode = nullptr;

			//	Find the offsets of the pen relative to the grader's rotation angle
			double xOffset = mGraderPen->DistancePG * cos(GetGrader()->GetAngle() - mGraderPen->Angle);
			double yOffset = mGraderPen->DistancePG * sin(GetGrader()->GetAngle() - mGraderPen->Angle);

			// Update angle and location of Pen
			mGraderPen->SetAngle(GetGrader()->GetAngle() + mGraderPen->Angle);
			mGraderPen->SetLocation(xOffset, GetGrader()->GetY() - yOffset);
		}
		// if it hasn't been a second yet
		else
		{
			//	We are going to display the message here
				//	Get the message
			auto nodeMessage = mFrozenNode->GetMessageW();

			//	Get the X value for centering the message
			auto nodeX = mFrozenNode->GetX();

			//	Get the Y value for centering the message
			auto nodeY = mFrozenNode->GetY();

			//	Get graphics from game
			auto graphics = mGame->GetGraphics();

			//	Display the message
			DrawNodeMessage(graphics, nodeMessage, nodeX, nodeY);
		}
	}
	//	Check for any nodes that have gone off screen now that our pen emission has resolved
	for (auto node : GetNodes())
	{
		auto difficulty = mGame->GetDifficulty();
		//	If left side hits the left side or right side hits right side of bounds
		//	And is in in the upper half of the playing area while difficulty is easy or medium 
		if 
		(
			((((mGame->GetDifficulty() == L"Easy") || (mGame->GetDifficulty() == L"Medium"))
			&& (	( ( (node->GetX()) + (node->GetNodeWidth()) ) > (CUmlGame::Width / 2) )
			|| (	(node->GetX() + band) < -(CUmlGame::Width / 2)	) )	)
			&& ((node->GetY() + node->GetNodeHeight()) < CUmlGame::Height / 2)	)
		) 
		{
			//	Reverse direction of node, bouncing it 
			node->SetSpeed(-(node->GetXSpeed()), (node->GetYSpeed()) );
		}

		//	If our node far left edge is out of the playing area X bound 
		else if ((node->GetX() - (node->GetNodeWidth() / 2) ) > (CUmlGame::Width / 2) ||
			(node->GetX() + (node->GetNodeWidth()) + band) < -(CUmlGame::Width / 2) ||
			(node->GetY() - node->GetNodeHeight() / 2) > CUmlGame::Height)
		{
			if (node->GetMessageW() == L"Unfair!")
			{
				mScoreboard->RaiseCorrect();
			}
			else
			{
				mScoreboard->RaiseMissed();
			}
			//	Push it back onto the temporary list of nodes to delete
			toDelete.push_back(node);
		}








	}
	
	//	We are done iterating. Time to delete the nodes we added to our list
	for (auto n : toDelete)
	{
		RemoveNodeItem(n);
	}
}


/**
 * Remove a node from the playing area
 * \param node the node to remove
 */
void CPlayingArea::RemoveNodeItem(CUmlNode* node)
{
	//	Cast as item for locating it in list of items within playing area
	for (auto loc = mItems.begin(); loc != mItems.end(); loc++)
	{
		if (loc->get() == node)
		{
			mItems.erase(loc);
			break;
		}
	}
}

/**
 * Return temporary vector containing all uml nodes currently in the 
 * list of items in playing area at the time of being called
 * \return a vector of all of the nodes in the playing area
 */
std::vector<CUmlNode *> CPlayingArea::GetNodes()
{
	//	Initialize return vector
	vector<CUmlNode> activeNodes;

	//	Create a vector
	CUmlNodeVisitor visitor;
	Accept(&visitor);

	//	Fill with nodes from mItems
	return visitor.GetNodes();
}


/**
 * Draws the node's message on top of it once it's been hit
 * \param graphics The graphics context we're drawing with
 * \param message The message to display
 * \param x X position of the node
 * \param y y position of the node
 */
void CPlayingArea::DrawNodeMessage(Gdiplus::Graphics* graphics, wstring message, double x, double y)
{


	////	Our text will be green by default
	//SolidBrush text(Color(0,130,0));


	//if (message == L"Unfair!")
	//{
	//	//	The brush used to paint the text is going to be red
	//	SolidBrush textRed(Color(255, 0, 0));
	//}


	//	The font of writing in uml node
	FontFamily fontFamily(L"Arial");

	//	The font size of the uml node
	Gdiplus::Font font(&fontFamily, 24, FontStyleBold);


	//	Our text will be green by default
	//SolidBrush text(Color(0,130,0));


	if (message == L"Unfair!")
	{
		//	The brush used to paint the text is going to be red
		SolidBrush textRed(Color(255, 0, 0));
		graphics->DrawString(
			message.c_str(),								// String to draw
			-1,												// String length, -1 means it is inherited from message size
			&font,											// The font to use
			PointF((Gdiplus::REAL)(x), (Gdiplus::REAL)y), // Where to draw (top left corner)
			&textRed);											// The brush to draw the text with);
	}

	else
	{
		//	The brush used to paint the text is going to be red
		SolidBrush text(Color(0, 130, 0));
		graphics->DrawString(
			message.c_str(),								// String to draw
			-1,												// String length, -1 means it is inherited from message size
			&font,											// The font to use
			PointF((Gdiplus::REAL)(x), (Gdiplus::REAL)y), // Where to draw (top left corner)
			&text);
	}


}