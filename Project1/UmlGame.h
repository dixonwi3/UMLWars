/**
 * \file UmlGame.h
 *
 * \author Team Hoare
 *
 * Class that implements a UML Game
 *
 */


#pragma once

#include "Scoreboard.h"
#include "UmlData.h"
#include "Item.h"
#include "XmlNode.h"
#include "PlayingArea.h"
#include "Emitter.h"
#include <vector>
#include <memory>
#include <string>

/// Game area in virtual pixels
///const static int Width = 1250;

/// Game area height in virtual pixels
///const static int Height = 1000;

class CUmlData;
class CScoreboard;
class CEmitter;

/**
 * Base class for our entire game
 */
class CUmlGame
{
public:
	CUmlGame();

	virtual ~CUmlGame();

	/** The scale of the game
	* \returns Scale in pixels */
	float GetScale() { return mScale; }

	/** The x coordinate offset of the game
	 * \returns X offset */
	float GetXOffset() { return mXOffset; }

	/** The y coordinate offset of the game
	 * \returns Y offset */
	float GetYOffset() { return mYOffset; }


	/**
	* Draw the game area
	*
	* \param graphics The GDI+ graphics context to draw on
	* \param width Width of the client window
	* \param height Height of the client window
	*/
	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	void OnMouseMove(double x, double y);
	void OnLButtonDown(double x, double y);

	/**
	 * Updater
	 * \param elapsed How far it's travelled
	 */
	void Update(double elapsed);

	/**
	 * Difficulty setter
	 * \param difficulty String of difficulty
	 */
	void SetDifficulty(std::wstring difficulty);

	/**
	 * Difficulty getter
	 * \return mDifficulty The difficulty setting
	 */
	std::wstring GetDifficulty() { return mDifficulty; }

	/**
	 * Graphics adder
	 * \param graphics Pointer to the graphics
	 */
	void AddGraphics(Gdiplus::Graphics* graphics) { mGraphics = graphics; }

	/**
	 * Graphics getter
	 * \return mGraphics The graphics pointer
	 */
	Gdiplus::Graphics* GetGraphics() { return mGraphics; }

	/**
	 * Scoreboard getter
	 * \return mScoreboard The scoreboard
	 */
	std::shared_ptr<CScoreboard> GetScoreboard() { return mScoreboard; }

	/**
	 * Playing Area getter
	 * \return mPlayingArea The area our game is taking place in
	 */
	std::shared_ptr<CPlayingArea> GetPlayingArea() { return mPlayingArea; }

	/**
	 * UMl name getter
	 * \return mNames Vector of names of UML
	 */
	std::vector<CUmlData> GetUmlNames() { return mNames; }

	/**
	 * UMl attribute getter
	 * \return Attributes Vector of attributes of our UML
	 */
	std::vector<CUmlData> GetUmlAttributes() { return mAttributes; }

	/**
	 * UMl operation getter
	 * \return mOperations Vector of operations
	 */
	std::vector<CUmlData> GetUmlOperations() { return mOperations; }

	/**
	 * UMl name getter
	 * \return mNames Names of UML
	 */
	std::vector<CUmlData> GetUmlBadNames() { return mBadNames; }

	/**
	 * UMl bad attribute getter
	 * \return mBadAttributes Vector of bad attributes
	 */
	std::vector<CUmlData> GetUmlBadAttributes() { return mBadAttributes; }

	/**
	 * UMl bad operations getter
	 * \return mBadOperations Vector of bad operations
	 */
	std::vector<CUmlData> GetUmlBadOperations() { return mBadOperations; }

	///	Clear game function, empty all xml values that were previously loaded
	void Clear();

	/**
	 * File loader
	 * \param filename File to be loaded
	 */
	void Load(const std::wstring filename);

	void XmlData(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/**
	 * Used for adding data to a node
	 * \param dataItem Data to add
	 * \param flag Flag for adding
	 */
	void AddDataItem(CUmlData dataItem, int flag);

	/// Game area in virtual pixels
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

private:

	/// The scoreboard this game draws on
	std::shared_ptr<CScoreboard> mScoreboard;

	/// Pointer to graphics
	Gdiplus::Graphics* mGraphics;

	///	The list of good uml name data used to create our uml objects
	std::vector<CUmlData> mNames;

	///	The list of good uml attribute data used to create our uml objects
	std::vector<CUmlData> mAttributes;

	///	The list of good uml operations data used to create our uml objects
	std::vector<CUmlData> mOperations;

	///	The list of bad uml name data used to create our uml objects
	std::vector<CUmlData> mBadNames;

	///	The list of bad uml attribute data used to create our uml objects
	std::vector<CUmlData> mBadAttributes;

	///	The list of bad uml operations data used to create our uml objects
	std::vector<CUmlData> mBadOperations;

	/// The list of items in the Game
	std::vector<std::shared_ptr<CItem> > mItems;

	///	Our emitter
	std::shared_ptr<CEmitter> mEmitter;

	///	The current difficulty of the game
	std::wstring mDifficulty;

	/// scale for drawing to fit all screens
	float mScale = 0;

	/// offset for X positioning
	float mXOffset = 0;

	///offset for Y positioning
	float mYOffset = 0;

	/// Clock start time
	clock_t mEmitBegin = 0;

	/// Clock end time
	clock_t mEmitEnd = 0;

	/// Temporary bool for emitter testing
	bool mEmit = false;

	/// Playing area of the game
	std::shared_ptr<CPlayingArea> mPlayingArea;
};

