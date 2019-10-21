/**
 * \file UmlGame.cpp
 *
 * \author Team Hoare	
 *
 */

#include "pch.h"
#include "UmlGame.h"
#include "PlayingArea.h"
#include "Scoreboard.h"
#include <ctime>
#include "Emitter.h"

using namespace xmlnode;
using namespace Gdiplus;
using namespace std;

CUmlGame::CUmlGame()
{
	Load(L"data/uml.xml");
	mScoreboard = make_shared<CScoreboard>(this);
	mPlayingArea = make_shared<CPlayingArea>(this, mScoreboard);
	mScoreboard->AddPlayingArea(mPlayingArea);
	mEmitter = make_shared<CEmitter>(this, mGraphics); //Look Here
	mDifficulty = L"Easy";	//	Default difficulty
}


CUmlGame::~CUmlGame()
{
}




/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CUmlGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
	// Fill the background with white
	SolidBrush brush(Color::White);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = 0;
	if (height > Height* mScale) {
		mYOffset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// From here on you are drawing virtual pixels
	
	CUmlData classname(this);
	classname.SetDataValue(L"Animal");
	
	if (!mEmit)
	{
		//	Testing spawn real quick
		mEmitter->Spawn(mEmitter->GetModifier());
		mEmit = true;
		mEmitBegin = clock();
	}
	else
	{
		mEmitEnd = clock();
		double elapsed_secs = double((long)mEmitEnd - (long)mEmitBegin) / CLOCKS_PER_SEC;
		if (elapsed_secs > 2)
		{
			mEmit = false;
		}
	}

	mPlayingArea->OnDraw(graphics);
	mScoreboard->Draw(graphics, width, height);
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
void CUmlGame::OnMouseMove(double x, double y)
{
	double virtualX = (x - mXOffset) / mScale;
	double virtualY = (y - mYOffset) / mScale;
	mPlayingArea->OnMouseMove(virtualX, virtualY);
}

/**
 * Handle a left button mouse message
 *
 * Throw the pen.
 *
 * \param x X location of mouse
 * \param y Y location of mouse
 */
void CUmlGame::OnLButtonDown(double x, double y)
{
	double virtualX = (x - mXOffset) / mScale;
	double virtualY = (y - mYOffset) / mScale;
	mPlayingArea->OnLButtonDown(virtualX, virtualY);
}

void CUmlGame::Update(double outsided)
{
	mPlayingArea->Update(outsided);
}


void CUmlGame::Clear()
{
	mNames.clear();
	mAttributes.clear();
	mOperations.clear();
}


void CUmlGame::Load(const std::wstring filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"class")
			{
				for (auto child : node->GetChildren())
				{
					XmlData(child);
				}

			}
		}

	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}


/**
* Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CUmlGame::XmlData(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	// A pointer for the item we are loading
	CUmlData dataItem(this);

	// We have an item. What type?
	wstring name = node->GetName();

	//	Handle xml nodes that are name item descriptors
	if (name == L"name")
	{
		//	Get the message, default to empty string if no bad attribute exists
		wstring message = node->GetAttributeValue(L"bad", L"");

		//	Load the values we just pulled from xml into the data item
		dataItem.XmlLoad(node, message);

		//	Add the data item to a list
		//	If we have a message, it's a bad node
		if (message != L"")
		{
			AddDataItem(dataItem, 1);
		}
		else
		{
			AddDataItem(dataItem, 0);
		}

	}

	//	Handle xml nodes that are attribute item descriptors
	else if (name == L"attribute")
	{
		//	Get the message, default to empty string if no bad attribute exists
		wstring message = node->GetAttributeValue(L"bad", L"");

		//	Load the values we just pulled from xml into the data item
		dataItem.XmlLoad(node, message);

		//	Add the data item to a list
		//	If we have a message, it's a bad node
		if (message != L"")
		{
			AddDataItem(dataItem, 3);
		}
		else
		{
			AddDataItem(dataItem, 2);
		}

		

	}

	//	Handle xml nodes that are attribute item descriptors
	else if (name == L"operation")
	{
		//	Get the message, default to empty string if no bad attribute exists
		wstring message = node->GetAttributeValue(L"bad", L"");

		//	Load the values we just pulled from xml into the data item
		dataItem.XmlLoad(node, message);

		//	Add the data item to a list
		//	If we have a message, it's a bad node
		if (message != L"")
		{
			AddDataItem(dataItem, 5);
		}
		else
		{
			AddDataItem(dataItem, 4);
		}
		

	}

}

void CUmlGame::AddDataItem(CUmlData dataItem, int flag)
{
	switch (flag)
	{
		//	Data item is a name
		case 0:
			mNames.push_back(dataItem);
			break;
		//	Data item is a bad name
		case 1:
			mBadNames.push_back(dataItem);
			break;
		//	Data item is an attribute
		case 2:
			mAttributes.push_back(dataItem);
			break;
		//	Data item is a bad attribute
		case 3:
			mBadAttributes.push_back(dataItem);
			break;
		//	Data item is an operation
		case 4:
			mOperations.push_back(dataItem);
			break;		
		//	Data item is a bad operation
		case 5:
			mBadOperations.push_back(dataItem);
			break;
	}
	
}


/**
 * Set difficulty
 */
void CUmlGame::SetDifficulty(std::wstring difficulty)
{
	//	Set the difficulty to the appropriate string value

	mDifficulty = difficulty;
	mEmitter->AdjustDifficulty(mDifficulty);
	mScoreboard->AdjustDifficulty(mDifficulty);
}
