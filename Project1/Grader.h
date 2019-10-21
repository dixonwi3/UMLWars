/**
 * \file Grader.h
 *
 * \author Team Hoare
 *
 * Class that implements the grader in UML Game.
 * 
 */


#pragma once
#include <string>
#include "MovingItem.h"


 /**
  * Class to handle the rotating grader item
  */
class CGrader : public CMovingItem
{
public:

	/**
	 * Constructor
	 * \param game The game this item is a member of playing area
	 */
	CGrader(CPlayingArea* game);
	virtual ~CGrader();
	///Default
	CGrader() = delete;

	/// Copy Constructor
	CGrader(const CGrader&) = delete;

	//void SetAngle(double angle) { mAngle = angle; }


	/** Accept a visitor
	*\param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGrader(this); }


};

