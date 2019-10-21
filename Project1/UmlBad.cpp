
#include "pch.h"

#include "UmlBad.h"
#include "UmlData.h"
#include "UmlNode.h"
#include "UmlGame.h"
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

using namespace std;
using namespace Gdiplus;



CUmlBad::CUmlBad(CUmlGame& game) : CUmlNode(game)
{
	this->SetMessage(L"");
}

void CUmlBad::Draw(Gdiplus::Graphics* graphics)
{
	CUmlNode::Draw(graphics);
}