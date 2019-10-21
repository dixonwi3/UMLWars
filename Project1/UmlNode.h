/**
 * \file UmlNode.h
 *
 * \author Team Hoare
 *
 * Class that implements a falling UML node in the UML Game. 
 * This does not apply to any other items in our UML Game.
 */

#pragma once

#include "MovingItem.h"
#include "Item.h"
#include "Emitter.h"
#include "XmlNode.h"
#include "UmlGame.h"
#include "UmlData.h"
#include "Scoreboard.h"
#include <string>
#include <vector>
#include <memory>


class CUmlData;
class CUmlGame;

/**
 * Base class for any UML Node in our game
 */
class CUmlNode : public CMovingItem
{
public:
	/// Default constructor (disabled)
	CUmlNode() = delete;

	/// Copy constructor (disabled)
	CUmlNode(const CUmlNode&) = delete;
	
	/**
	* Message getter
	* \return mMessage The message we are getting
	*/
	std::wstring CUmlNode::GetMessage() { return mMessage; }

	/** Gets name of node
	* \return mName Name of the node
	*/
	std::vector<CUmlData> GetName() { return this->mName; }

	/** Get attributes of the node
	* \return mAttributes The attributes of the node
	*/
	std::vector<CUmlData> GetAttributes() { return this->mAttributes; }

	/** Gets operations of the node
	* \return mOperations The operations of the node
	*/
	std::vector<CUmlData> GetOperations() { return this->mOperations; }


	/** For adding graphics
	* \param graphics Our graphics package
	* \return graphics That same package
	*/
	void AddGraphics(Gdiplus::Graphics* graphics) { mGraphics = graphics; };

	/** Sets name of node
	* \param name Name to be set
	*/
	void SetName(std::vector<CUmlData> name) { mName = name; }

	/** Sets attributes for node
	* \param attributes Attributes we are adding
	*/
	void SetAttributes(std::vector<CUmlData> attributes) { mAttributes = attributes; }

	/** Sets operations for node
	* \param operations Operations we are adding to the node
	*/
	void SetOperations(std::vector<CUmlData> operations) { mOperations = operations; }

	/**
	* \param message Message we are adding to the node
	*/
	void SetMessage(std::wstring message) { this->mMessage = message; }

	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Creates node width
	double GetNodeWidth();

	/// Creates node height
	double GetNodeHeight();

	/** For updating nodes
	* \param elapsed How far it's traveled  */
	virtual void Update(double elapsed);


	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override	{ visitor->VisitUmlNode(this);  }


protected: 
	CUmlNode(CUmlGame &game);
	
private:
	/// the message displayed when this node is hit with a pen
	std::wstring mMessage;

	/// The UML object vector of the name to draw (1 per object)
	std::vector<CUmlData> mName;

	/// The UML object vector of the attributes to draw (0-3 per object)
	std::vector<CUmlData> mAttributes;

	/// The UML object vector of the operations to draw (0-3 per object)
	std::vector<CUmlData> mOperations;

	/// Graphics package
	Gdiplus::Graphics* mGraphics;

	/// Uml node width
	double mNodeWidth = 0;

	/// UML node hieght
	double mNodeHeight = 0;
};

