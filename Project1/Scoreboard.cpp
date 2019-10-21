/**
 * \file Scoreboard.cpp
 *
 * \author Team Hoare
 */



#include "pch.h"
#include "Scoreboard.h"
#include <sstream>
#include <string>
#include <memory>
#include "Emitter.h"
#include "UmlGame.h"

using namespace std;
using namespace Gdiplus;

CScoreboard::CScoreboard(CUmlGame* game) : mGame(game)
{
}

void CScoreboard::AddPlayingArea(std::shared_ptr<CPlayingArea> area)
{
	mPlayingArea = area;
}

void CScoreboard::AdjustDifficulty(const std::wstring& difficulty)
{
	mDifficulty = difficulty;
	mCorrect = 0;
	mMissed = 0;
	mUnfair = 0;
}


/**
 * Function that draws the scoreboard for the UmlGame
 * \param graphics The GDI+ graphics context to draw on
 * \param width the width of the playing area
 * \param height the height of the playing area
 */
void CScoreboard::Draw(Gdiplus::Graphics* graphics, int width, int height)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 32, FontStyleBold);
	Gdiplus::Font scoreFont(&fontFamily, 48, FontStyleBold);

	SolidBrush green(Color(0, 200, 200));
	SolidBrush red(Color(200, 0, 0));
	
	wstringstream correct; wstringstream missed; wstringstream unfair;
	correct << mCorrect;
	missed << mMissed;
	unfair << mUnfair;

	// Draw the score values to the board
	graphics->DrawString(correct.str().c_str(), -1, &scoreFont, PointF(-spacingX, 10), &green);
	graphics->DrawString(missed.str().c_str(), -1, &scoreFont, PointF(0, 10), &green);
	graphics->DrawString(unfair.str().c_str(), -1, &scoreFont, PointF(spacingX, 10), &green);

	// Draw the score identifiers in correct color
	graphics->DrawString(L"Correct", -1, &font, PointF(-spacingX - 50, 70), &green);
	graphics->DrawString(L"Missed", -1, &font, PointF(-50, 70), &green);
	graphics->DrawString(L"Unfair", -1, &font, PointF(spacingX - 50, 70), &green);


	SolidBrush blue(Color(0, 200, 0));

	wstringstream difficulty;
	difficulty <<mDifficulty.c_str();

	// Draw the score values to the board
	graphics->DrawString(L"Difficulty", -1, &font, PointF(spacingX - 50, 820), &green);

	// If hard or expert, paint red, else green, also put each difficulty in the right place
	if (mDifficulty == L"Expert")
		graphics->DrawString(difficulty.str().c_str(), -1, &scoreFont, PointF(spacingX - 70, 870), &red);
	else if (mDifficulty == L"Hard")
		graphics->DrawString(difficulty.str().c_str(), -1, &scoreFont, PointF(spacingX - 40, 870), &red);
	else if (mDifficulty == L"Medium")
		graphics->DrawString(difficulty.str().c_str(), -1, &scoreFont, PointF(spacingX - 110, 870), &blue);
	else
		graphics->DrawString(difficulty.str().c_str(), -1, &scoreFont, PointF(spacingX - 40, 870), &blue);
}