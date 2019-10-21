/**
 * \file Grader.cpp
 *
 * \author Team Hoare
 */



#include "pch.h"
#include "Grader.h"
#include <string>
using namespace std;

///The image that need to be loaded
const wstring filename = L"images/harold.png";
///initial x position of grader
const int graderX = 0;
///initial y position of grader
const int graderY = 900;


/* Constructor
 * \param game a member of this member
 */
CGrader::CGrader(CPlayingArea* game) : CMovingItem(game, filename)
{
	SetLocation(graderX, graderY);
}

CGrader::~CGrader()
{
}
