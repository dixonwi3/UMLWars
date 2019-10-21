/**
 * \file Scoreboard.h
 *
 * \author Team Hoare
 *
 * Class that implements a scoreboard in the UML Game.
 *
 */

#pragma once

#include "PlayingArea.h"
#include "UmlGame.h"
#include <memory>
#include <string>

/// The spacing between score listings on the window in UmlGame
const int spacingX = 450;

class CUmlGame;


/**
 * Class to handle scoreboard points and painting
 */
class CScoreboard
{
public:

	/// default constructor (disabled)
	CScoreboard() = delete;

	/**
	 * Scoreboard constructor
	 * \param game Game pointer
	 */
	CScoreboard(CUmlGame* game);

	/// Copy constructor (disabled)
	CScoreboard(const CScoreboard&) = delete;

	void Draw(Gdiplus::Graphics* graphics, int width, int height);

	/**
	* Adds plaing area
	* \param area Area to add
	*/
	void AddPlayingArea(std::shared_ptr<CPlayingArea> area);

	/**
	* Correct score getter
	* \return Number correct
	*/
	int GetCorrect() { return mCorrect; };

	/**
	* Missed score getter
	* \return Number missed
	*/
	int GetMissed() { return mMissed; };

	/**
	* Unfair score getter
	* \return Number unfair
	*/
	int GetUnfair() { return mUnfair; };

	///Raises correct score
	void RaiseCorrect() { mCorrect++; };
	///Raises missed score
	void RaiseMissed() { mMissed++; };
	///Raises unfair score
	void RaiseUnfair() { mUnfair++; };

	/**
	 * Set difficulty, reset scoreboard
	 * \param difficulty Difficulty setting
	 */
	void AdjustDifficulty(const std::wstring& difficulty);

protected:

private:
	/// the playing area of the scoreboard
	std::shared_ptr<CPlayingArea> mPlayingArea;

	/// The UmlGame this scoreboard belongs to
	CUmlGame* mGame;

	/// number of correct hits
	int mCorrect = 0;
	
	/// number of bad Uml nodes missed
	int mMissed = 0;

	/// number of good Uml nodes hit
	int mUnfair = 0;

	/// String of difficulty of game
	std::wstring mDifficulty = L"Easy";
};

