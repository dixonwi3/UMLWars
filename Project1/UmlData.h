/**
 * \file UmlData.h
 *
 * \author Team Hoare
 *
 * Class that implements reading and storage of Uml Data.
 *
 */

#pragma once

#include "UmlGame.h"
#include "XmlNode.h"
#include <memory>
#include <vector>
#include <string>

class CUmlGame;

/**
 * Class for generating UML data
 */
class CUmlData
{

public:
	/// default constructor (disabled)
	CUmlData() = delete;

	/**
	 * Create UML data
	 * \param game Pointer to our game
	 */
	CUmlData(CUmlGame* game);

	void CUmlData::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, const std::wstring msg);

	/**
	 * Setter for data
	 * \param val Data value of type of UML
	 */
	void SetDataValue(std::wstring val) { mValue = val; }

	/**
	 * Setter for data message
	 * \param mes Message that will be displayed upon collision with pen
	 */
	void SetDataMessage(std::wstring mes) { mMessage = mes; }


	/**
	 * Getter for data value
	 * \return Data value of type of UML
	 */
	std::wstring GetDataValue() { return mValue; }

	/**
	 * Getter for data message
	 * \return Message that will be displayed upon collision with pen
	 */
	std::wstring GetDataMessage() { return mMessage; }

private:

	/// The UmlGame this uml data belongs to
	CUmlGame *mGame;

	///	The value held by this data object
	std::wstring mValue = L"";

	///	The message held by this data object. If it is good, message default is "Unfair!"
	std::wstring mMessage = L"Unfair!";



};

