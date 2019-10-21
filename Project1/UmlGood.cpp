/**
 * \file UmlGood.cpp
 *
 * \author Team Hoare
 */

#include "pch.h"
#include "UmlData.h"
#include "UmlGood.h"
#include "UmlNode.h"
#include "UmlGame.h"
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

using namespace std;
using namespace Gdiplus;



CUmlGood::CUmlGood(CUmlGame &game)	: CUmlNode(game)
{
	this->SetMessage(L"Unfair!");
}

void CUmlGood::Draw(Gdiplus::Graphics* graphics)
{
	CUmlNode::Draw(graphics);
}