/**
 * \file Emitter.h
 *
 * \author Team Hoare
 *
 * Class that implements an emitter of UML nodes in the UML Game.
 * 
 */


#pragma once
#include <string>
#include <memory>
#include <vector>
#include "UmlGame.h"
#include "UmlData.h"

class CUmlGame;
class CUmlData;

/**
 * Class to handle timing of UML generation and emission
 */
class CEmitter
{
public:
	/// constructor
	CEmitter(CUmlGame* game, Gdiplus::Graphics* graphics);
	virtual ~CEmitter();

	/// copy constructor (disabled)
	CEmitter(const CEmitter&) = delete;

	void AdjustDifficulty(const std::wstring& str);

	/**
	 * Set modifier on emission
	 * \param newValue new modifier
	 */
	void SetModifier(double newValue);

	/**
	 * Get modifier
	 * \return mSpawnModifier Current modifier on emission
	 */
	double GetModifier() { return mSpawnModifier; }

	void EmitGood(std::wstring message, std::vector<CUmlData> name, std::vector<CUmlData> attributes, std::vector<CUmlData> operations);
	
	void EmitBad(std::wstring message, std::vector<CUmlData> name, std::vector<CUmlData> attributes, std::vector<CUmlData> operations);

	/**
	* Spawn a node after doing some logic to decide what kind and what to put in
	* \param modifier The spawn modifier, to be read as the probability of emitting a bad node
	*/
	void Spawn(double modifier);

	/**
	* Grab count number of items from shuffled vector of UML data
	* \param dataVector The vector of data items we are shuffling and grabbing from for a node
	* \param count the number of items to pick up
	* \return std::vector<CUmlData> vector once shuffled
	*/
	std::vector<CUmlData> ShuffleGrab(std::vector<CUmlData> dataVector, int count);

	/**
	 * Sets max x for nodes
	 * \param speedX speed based on difficulty
	 */
	void SetMaxSpeedX(double speedX) { mSpeedX = speedX; }

	/**
	 * Sets max y for nodes
	 * \param speedY speed based on difficulty
	 */
	void SetMaxSpeedY(double speedY) { mSpeedY = speedY; }


private:
	/// the playing area of the scoreboard
	std::shared_ptr<CPlayingArea> mPlayingArea; //Look here

	/// The UmlGame this emitter belongs to
	CUmlGame* mGame;

	/// the graphics context
	Gdiplus::Graphics* mGraphics;

	///	The vector of every UML name we loaded in at runtime
	std::vector<CUmlData> mNames; 

	///	The vector of every UML attribute we loaded in at runtime
	std::vector<CUmlData> mAttributes;

	///	The vector of every UML operation we loaded in at runtime
	std::vector<CUmlData> mOperations;

	/// % spawn rate of bad Uml blocks
	double mSpawnModifier = 100;

	/// Base node speed on X axis
	double mSpeedX = 10;
	
	/// Base node speed on Y axis
	double mSpeedY = 10;
};

