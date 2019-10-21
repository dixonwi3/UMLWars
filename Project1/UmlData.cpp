
#include "pch.h"
#include "UmlData.h"
#include "XmlNode.h"
#include "UmlGame.h"
#include <iostream>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;


CUmlData::CUmlData(CUmlGame* game)
{
	mGame = game;
}



/**
 * Load the value for a data item.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the item from
 * \param msg The message for the node
 */
void CUmlData::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, const std::wstring msg)
{
	//	Set the value
	wstring str = L"";

	for (auto child : node->GetChildren())
	{
		if (child->GetType() == NODE_TEXT)
		{
			str += child->GetValue();
		}
	}
	mValue = str;
	//	Set the message if there is one, otherwise will default to "Unfair!"
	if (msg != L"")
	{
		mMessage = msg;
	}
}



