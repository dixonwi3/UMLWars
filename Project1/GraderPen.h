/**
 * \file GraderPen.h
 *
 * \author Team Hoare
 *
 * Class that implements a grader's pen in the UML Game.
 *
 */


#pragma once

#include <string>
#include <memory>
#include "MovingItem.h"
#include "UmlNode.h"

class CUmlNode;


/**
 * Class derived from item to handle the grader's pen
 */
class CGraderPen : public CMovingItem
{
public:
	/// Constructor
	CGraderPen(CPlayingArea* game);

	/// Destructor
	virtual ~CGraderPen();

	/// Default construtor 
	CGraderPen() = delete;

	/// Default construtor
	CGraderPen(const CGraderPen&) = delete;

	/** If an emission
	* \return mEmission true if an emission
	*/
	bool IsEmission() { return mEmission; }

	/// Angle of pen
	const static float Angle;

	/// Distance of the pen from the grader in pixels
	const static double DistancePG;

	/** Accept a visitor
	 * \param visitor The visitor we accept 
	 */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGraderPen(this); }



private:
	/// Visible or not
	bool visible = true;

	///Emission or not
	bool mEmission = false;
};

