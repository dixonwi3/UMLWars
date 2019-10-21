/**
 * \file PlayingArea.h
 *
 * \author Team Hoare
 *
 * Class that implements a Playing Area in the UML Game.
 *
 */

#pragma once

#include <vector>
#include <memory>
#include "Grader.h"
#include "Item.h"
#include "UmlGame.h"
#include "UmlNode.h"
#include "Scoreboard.h"
#include "GraderPen.h"
#include <vector>

class CUmlGame;
class CScoreboard;
class CUmlNode;
class UmlGame;
class CGraderPen;

/**
 * Class to handle game display and boundaries
 */
class CPlayingArea
{
public:
	/// Default constructor (deleted0
	CPlayingArea() = delete;

	///Copy constructor (deleted)
	CPlayingArea(const CPlayingArea&) = delete;

	/* 
	* Destructor 
	*/
	virtual ~CPlayingArea();

	void OnDraw(Gdiplus::Graphics* graphics);

	void OnMouseMove(double x, double y);
	void OnLButtonDown(double x, double y);

	/**
	* For hit testing our game
	* \param x X position to check
	* \param y Y position to check
	* \return Pointer to an item being tested
	*/
	std::shared_ptr<CItem> HitTest(int x, int y);

	CPlayingArea(CUmlGame* game, std::shared_ptr<CScoreboard> board);

	void AddNode(std::shared_ptr<CUmlNode> node);

	void Add(std::shared_ptr<CItem> item);

	void RemoveNode(std::shared_ptr<CUmlNode> node);

	int NumNodes();

	/** Get the grader object in the playing area
	 * \return the grader object
	 */
	std::shared_ptr<CItem> GetGrader() { return mGrader; };

	/** Get the game object associated with playing area
	 * \return the game object
	 */
	CUmlGame* GetGame() { return mGame; }

	/** Get the items in the game
	 * \return mItems The list of items currently in the game
	 */
	std::vector<std::shared_ptr<CItem> > GetItems() { return mItems; };

	/** Test the AddItem function of Cplaying Area
	 * \return the number of item
	 */
	int Size() { return mItems.size(); }

	virtual void Update(double outsided);

	void UpdateDetail(double outsided);

	void RemoveNodeItem(CUmlNode* node);

	std::vector<CUmlNode *> GetNodes();

	void DrawNodeMessage(Gdiplus::Graphics* graphics, std::wstring message, double x, double y);

	void PenEmit(CVector direction);

	/** Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void CPlayingArea::Accept(CItemVisitor* visitor)
	{
		for (auto item : mItems)
		{
			item->Accept(visitor);
		}
	}

private:
	/// All the items in the display area
	std::vector<std::shared_ptr<CItem>> mItems;

	/// The grader in the display area
	std::shared_ptr<CGrader> mGrader;

	/// The grader's pen in the display area
	std::shared_ptr<CGraderPen> mGraderPen;

	/// list of UmlNodes currently displayed in playing area
	std::vector<std::shared_ptr<CUmlNode> > mNodes;

	/// The game
	CUmlGame* mGame;

	/// The scoreboard
	std::shared_ptr<CScoreboard> mScoreboard;

	/// How many nodes we have
	int mNumNodes = 0;

	/// If emitted
	bool mEmission = false;

	/// Pointer to current frozen uml node
	CUmlNode* mFrozenNode;

	/// Our one allowed list of items
	std::shared_ptr<CItem> mItem;

	/// If frozen
	bool mFreeze = false;
	
	/// Time of freeze start
	clock_t mFreezeBegin = 0;

	/// Time of freeze end
	clock_t mFreezeEnd = 0;
};

