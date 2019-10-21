/**
 * \file MovingItem.h
 *
 * \author Team Hoare
 *
 * Class that implements a moving item in the UML Game.
 * 
 */


#pragma once
#include <memory>
#include <string>
#include "Item.h"
#include <memory.h>


 /**
  * Class to handle items that are currently moving, such as nodes and the pen
  */
class CMovingItem : public CItem
{
public:
	/// Destructor
	virtual ~CMovingItem();

	///  Default constructor (disabled)
	CMovingItem() = delete;
	
	///  Copy constructor (disabled)
	CMovingItem(const CMovingItem&) = delete;

	void Draw(Gdiplus::Graphics* graphics);

protected:
	/** Item that is currently moving
	 * \param area The area we are viewing
	 * \param filename The file we are viewing
	 */
	CMovingItem::CMovingItem(CPlayingArea* area, std::wstring filename);

private:
	std::unique_ptr<Gdiplus::Bitmap> mMovingItem; ///< Image for this item
};





