/**
 * \file UmlBad.h
 *
 * \author Team Hoare
 *
 * Class that implements an incorrect ("bad") UML node in the UML Game.
 * 
 */


#pragma once
#include "Item.h"
#include "UmlNode.h"
#include "UmlGame.h"

 /**
  * Class that creates bad uml objects
  */
class CUmlBad : public CUmlNode
{

public:

	/**
	 * Create bad uml
	 * \param game Pointer to our game
	 */
	CUmlBad(CUmlGame& game);

	/**
	 * On drawing UML bad
	 * \param graphics Pointer for graphics package
	 */
	virtual void Draw(Gdiplus::Graphics* graphics);

private:

	/// the message displayed when this node is hit with a pen
	std::string mMessage;
};

