/**
 * \file ItemVisitor.h
 *
 * \author Team Hoare
 *
 * Item visitor base class.
 */


#pragma once

 // Forward references to all item types
class CMovingItem;
class CUmlNode;
class CGraderPen;
class CGrader;

/** Tile visitor base class */
class CItemVisitor
{


public:
	virtual ~CItemVisitor() {}

	/** Visit a CUmlNode object
	 * \param node Node we are visiting */
	virtual void VisitUmlNode(CUmlNode* node) {}

	/** Visit a CGraderPen object
	* \param pen grader pen item we are visiting */
	virtual void VisitGraderPen(CGraderPen* pen) {}

	/** Visit a CGrader object
	* \param grader Grader item we are visiting */
	virtual void VisitGrader(CGrader* grader) {}

};