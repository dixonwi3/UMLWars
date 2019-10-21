
#pragma once

#include "pch.h"
#include "UmlNodeVisitor.h"
#include "ItemVisitor.h"
#include "UmlNode.h"


void CUmlNodeVisitor::VisitUmlNode(CUmlNode* node)
{
	mNodes.push_back(node);
}

