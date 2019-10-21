/**
 * \file UmlNodeVisitor.h
 *
 * \author Team Hoare
 */


#include "ItemVisitor.h"
#include "Item.h"
#include "UmlNode.h"
#include "UmlGood.h"
#include "UmlBad.h"
#include <memory>
#include <vector>

#pragma once

class CUmlNode;


#pragma once

/**
 * Visitor class to view UmlNodes
 */
class CUmlNodeVisitor : public CItemVisitor
{
public:

	/**
	 * Node getter
	 * \return mNodes Vector of nodes
	 */
	std::vector<CUmlNode *> GetNodes() const { return mNodes; }


	/** Visit a CUmlNode object
	* \param node Node we are visiting
	*/
	void CUmlNodeVisitor::VisitUmlNode(CUmlNode* node);

private:
	/// List of nodes we are looking at
	std::vector<CUmlNode *> mNodes;

};

