/**
 * \file UmlGood.h
 *
 * \author Team Hoare
 *
 * Class that implements a correct ("good") falling Uml node in the UML Game.
 *
 */

#pragma once
#include "Item.h"
#include "UmlNode.h"
#include "UmlGame.h"

 /**
  * Class for creating good UML nodes
  */
class CUmlGood : public CUmlNode
{
public:

	/**
	 * UML good constructor
	 * \param game The game UML is inside
	 */
	CUmlGood::CUmlGood(CUmlGame &game);

	/// Default constructor (disabled)
	CUmlGood() = delete;

	/// Copy constructor (disabled)
	CUmlGood(const CUmlGood&) = delete;

	/**
	 * Draws UML good
	 * \param graphics Pointer to the graphics package
	 */
	virtual void Draw(Gdiplus::Graphics* graphics);

};

