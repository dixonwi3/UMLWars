/**
 * \file Item.h
 *
 * \author Team Hoare
 *
 * Class that implements an item on the screen in UML Game.
 * 
 */

#pragma once

#include "Vector.h"
#include "ItemVisitor.h"
#include <string>
#include <memory>

class CPlayingArea;

/**
 * Base class for any item in our game
 */
class CItem
{
public:
	/// default constructor disabled
	CItem() = delete;

	/// copy constructor disabled
	CItem(const CItem&) = delete;

	/// Destructor
	virtual ~CItem();


	/** Draw the graph or UML
	 *\param graphics as the graphics loaded in
	 */
	virtual void Draw(Gdiplus::Graphics* graphics) {};


	/** Update the playingArea
	 *\param elapsed How much the item has traveled
	 */
	virtual void Update(double elapsed) {}

	bool HitTest(int x, int y);

	/**
	 * The X location of Item
	 *\returns X location
	 */
	double GetX() const { return mPosition.X(); }

	/**
	* The Y location of Item
	*\returns Y location
	*/
	double GetY() const { return mPosition.Y(); }


	 /** Set the X,Y position
	  *\param x X position to be set
	  *\param y Y position to be set
	  */
	void SetLocation(double x, double y) { mPosition.SetX(x), mPosition.SetY(y); }
	
	/** Set the angle
	 *\param angle Angle in radians
	 */
	void SetAngle(double angle) { mAngle = angle; }
	
	/** The angle of the item
	 *\return Angle in radians
	 */
	double GetAngle() { return mAngle; }


	/** The X speed of the item
	 *\returns X speed in pixels per second 
	 */
	double GetXSpeed() const { return mSpeed.X(); }

	/** The Y speed of the item
	 *\returns Y speed in pixels per second 
	 */
	double GetYSpeed() const { return mSpeed.Y(); }

	/** Set the item speed
	 *\param x X speed
	 *\param y Y speed
	 */
	void SetSpeed(double x, double y) { mSpeed.SetX(x); mSpeed.SetY(y); }

	/** Get the position of the vector
	 *\return mPosition as the position of vector
	 */
	CVector GetPositionVector() { return mPosition; }
	
	/** Accept a visitor
	*\param visitor The visitor we accept 
	*/
	virtual void Accept(CItemVisitor* visitor) {};


protected:

	CItem(CPlayingArea* playingArea);

	/** Get the pointer of CPlayingArea
	 *\return mPlayingArea as the pointer of CPlayingArea
	 */
	CPlayingArea* GetPlayingArea() { return mPlayingArea; }

	/// the playing area of the item
	CPlayingArea* mPlayingArea;

private:
	/// The image tied to our item
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// vector for keeping track of position
	CVector mVector = CVector(0, 0);

	/// Item Location
	CVector mPosition;

	/// Item Speed
	CVector mSpeed;


	/// Item Angle 
	double mAngle = 0;
};

