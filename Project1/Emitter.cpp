/**
 * \file Emitter.cpp
 *
 * \author Team Hoare
 */


#include "pch.h"
#include "Emitter.h"
#include "UmlGame.h"
#include "UmlNode.h"
#include "UmlData.h"
#include "UmlGood.h"
#include "UmlBad.h"
#include <iostream>
#include <memory.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace Gdiplus;
using namespace xmlnode;
using namespace std;

/// Speed of node in x-direction for easy difficulty
const unsigned int EZ_SPEEDX = 6;
/// Speed of node in y-direction for easy difficulty
const unsigned int EZ_SPEEDY = 10;
/// Starting probability that bad Uml will spawn for easy difficulty
const double EZ_MOD = 100;

/// Speed of node in x-direction for medium difficulty
const unsigned int MED_SPEEDX = 12;
/// Speed of node in y-direction for medium difficulty
const unsigned int MED_SPEEDY = 20;
/// Starting probability that bad Uml will spawn for medium difficulty
const double MED_MOD = 75;

/// Speed of node in x-direction for hard difficulty
const unsigned int HARD_SPEEDX = 24;
/// Speed of node in y-direction for hard difficulty
const unsigned int HARD_SPEEDY = 40;
/// Starting probability that bad Uml will spawn for hard difficulty
const double HARD_MOD = 50;

/// Speed of node in x-direction for expert difficulty
const unsigned int EXPERT_SPEEDX = 30;
/// Speed of node in y-direction for expert difficulty
const unsigned int EXPERT_SPEEDY = 50;
/// Starting probability that bad Uml will spawn for expert difficulty
const double EXPERT_MOD = 25;
/// Emission angle correction
const double ANGLE_SAFETY = 1.3;

/**
 * Constructor
 * \param game The game that this emitter belongs to
 * \param graphics The graphics context the emitter draws in
 */
CEmitter::CEmitter(CUmlGame * game, Gdiplus::Graphics* graphics) : mGame(game) //Look here
{
	mGraphics = graphics;
}


/**
 * Destructor
 */
CEmitter::~CEmitter()
{
}

/**
 * Adjusts the difficulty settings
 * \param str String of difficulty
 */
void CEmitter::AdjustDifficulty(const std::wstring& str)
{
	// if easy difficulty
	if (str == L"Easy")
	{
		mSpawnModifier = EZ_MOD;
		SetMaxSpeedX(EZ_SPEEDX);
		SetMaxSpeedY(EZ_SPEEDY);
	}
	// if medium difficulty
	else if (str == L"Medium")
	{
		mSpawnModifier = MED_MOD;
		SetMaxSpeedX(MED_SPEEDX);
		SetMaxSpeedY(MED_SPEEDY);
	}
	// if hard difficulty
	else if (str == L"Hard")
	{
		mSpawnModifier = HARD_MOD;
		SetMaxSpeedX(HARD_SPEEDX);
		SetMaxSpeedY(HARD_SPEEDY);
	}
	// if expert difficulty
	else if (str == L"Expert")
	{
		mSpawnModifier = EXPERT_MOD;
		SetMaxSpeedX(EXPERT_SPEEDX);
		SetMaxSpeedY(EXPERT_SPEEDY);
	}
}

void CEmitter::SetModifier(double newValue )
{
	mSpawnModifier = newValue;
}


/**
 * Creates and emits a good node (a node that shouldn't be hit by a pen)
 * \param message The message to display when node is hit by pen
 * \param name The class name for the node
 * \param attributes The list of attributes to be displayed on node
 * \param operations The list of operations to be displayed on node
 */
void CEmitter::EmitGood(wstring message, vector<CUmlData> name, vector<CUmlData> attributes, vector<CUmlData> operations)
{
	//create new good UmlNode
	auto good = make_shared<CUmlGood>(*mGame);

	// set the location of the node to off the screen
	auto spawnX = (rand() % (int(200) + 1));

	// seed random number
	srand((unsigned int) time(NULL));

	auto negSpawnX = (rand() % 3);
	if (negSpawnX >= 1)
	{
		spawnX = -1 * spawnX;
	}

	good->SetLocation(spawnX, 0);

	// fill with appropriate values...
	good->SetName(name);
	good->SetAttributes(attributes);
	good->SetOperations(operations);
	
	// Add the node to the playing area (playing area draws node in Childview)
	srand((unsigned int) time(NULL));

	/// magnitude in x-direction for speed vector 
	auto rX = (rand() % (10 + 1)) + 1;
	/// magnitude in y-direction for speed vector 
	auto rY = (rand() % (10 + 1)) + 1;

	/// angle safety
	if (rY < int(ANGLE_SAFETY *rX))
	{
		rY = int(rX * (1 + 0.1 * (long(rand() % 5) + 1)));
	}

	// if we spawn too far to the right, object has to fall to left
	if (spawnX > 100)
	{
		rX = -1 * rX;
	}

	// if the item spawns between x -100 and 100
	if (spawnX < 100 && spawnX > -100)
	{
		// we can choose at random which x-direction it will fall in
		srand((unsigned int) time(NULL));
		auto negX = (rand() % 2);

		if (negX >= 1)
		{
			rX = -1 * rX;
		}
	}

	CVector direction;
	// set x and y direction vectors
	direction.Set(rX, rY);
	// set the speed
	good->SetSpeed(mSpeedX * rX, mSpeedX * rY);
	// add node to playing area
	mGame->GetPlayingArea()->AddNode(good);
}


/**
 * Creates and emits a bad node (a node that SHOULD be hit by a pen)
 * \param message The message to display when node is hit by pen
 * \param name The class name for the node
 * \param attributes The list of attributes to be displayed on node
 * \param operations The list of operations to be displayed on node
 */
void CEmitter::EmitBad(wstring message, vector<CUmlData> name, vector<CUmlData> attributes, vector<CUmlData> operations)
{
	auto bad = make_shared<CUmlBad>(*mGame);

	// set the location of the node to off the screen
	auto spawnX = (rand() % (int(200) + 1));

	srand((unsigned int) time(NULL));

	// determine if node will spawn on left or right half of screen
	auto negSpawnX = (rand() % 3);

	if (negSpawnX >= 1)
	{
		spawnX = -1 * spawnX;
	}
	// set spawn point
	bad->SetLocation(spawnX, 0);

	// fill with appropriate values...
	bad->SetName(name);
	bad->SetAttributes(attributes);
	bad->SetOperations(operations);
	bad->SetMessage(message);

	// Add the node to the playing area (playing area draws node in Childview)
	srand((unsigned int) time(NULL));

	/// magnitude in x-direction for speed vector 
	auto rX = (rand() % (10 + 1)) + 1;
	/// magnitude in y-direction for speed vector 
	auto rY = (rand() % (10 + 1)) + 1;

	/// angle safety
	if (rY < int(ANGLE_SAFETY * rX))
	{
		rY = int(rX*(1 + 0.1*(long(rand() % 5) + 1)));
	}

	// if we spawn too far to the right, object has to fall to left
	if (spawnX > 100)
	{
		rX = -1 * rX;
	}

	// if the item spawns between x -100 and 100
	if (spawnX < 100 && spawnX > -100)
	{
		// we can choose at random which x-direction it will fall in
		srand((unsigned int) time(NULL));
		auto negX = (rand() % 2);

		if (negX >= 1)
		{
			rX = -1 * rX;
		}
	}

	CVector direction;
	// set x and y direction vectors
	direction.Set(rX, rY);
	// set the speed
	bad->SetSpeed(mSpeedX * rX, mSpeedX * rY);
	// add node to playing area
	mGame->GetPlayingArea()->AddNode(bad);
}

//	Here we decide what type of node to spawn based off of random value and passed in modifier
//	builds vectors for each characteristic of node and set the message. Decrement spawn modifier at the end
void CEmitter::Spawn(double modifier)
{
	//	Initialize our variables
	wstring message = L"";
	vector<CUmlData> name;
	vector<CUmlData> attributes;
	vector<CUmlData> operations;

	//	Get a random number from 0 to 100, 
	srand((unsigned int) time(NULL));
	int r = (rand() % 100) + 1;

	//	Everything less than or equal to our modifier will be a bad node
	if (r <= modifier)
	{
		//	We are creating a bad node.
		//	In order to decide what node is bad (and dictates message), we generate a random number 1-3
		int r = (rand() % 3) + 1;
		
		//	We have a bad name
		if (r == 1)
		{
			//	Shuffle and grab one bad name from the list
			name = ShuffleGrab(mGame->GetUmlBadNames(), 1);

			//	Set our message value to the message held by the bad name
			message = name[0].GetDataMessage();

			//	Also we will grab 0-3 good attributes
			attributes = ShuffleGrab(mGame->GetUmlAttributes(), (rand() % 4) );

			//	And 0-3 good operations
			operations = ShuffleGrab(mGame->GetUmlOperations(), (rand() % 4) );

		}
		//	We have a bad attribute
		else if (r == 2)
		{

			//	Shuffle and grab one good name from the list.
			name = ShuffleGrab(mGame->GetUmlNames(), 1);

			//	Shuffle and grab one bad attribute from the list.
			attributes = ShuffleGrab(mGame->GetUmlBadAttributes(), 1);

			//	Set our message value to the message held by the bad attribute
			message = attributes[0].GetDataMessage();

			//	Also we will grab 0-2 good attributes
			vector <CUmlData> goodAttributes = ShuffleGrab(mGame->GetUmlAttributes(), (rand() % 3) );
			
			//	put them in with the bad one
			attributes.insert( attributes.begin(), goodAttributes.begin(), goodAttributes.end() );

			//	And 0-3 good operations
			operations = ShuffleGrab(mGame->GetUmlOperations(), (rand() % 4) );

		}
		//	We have a bad operation
		else 
		{

			//	Shuffle and grab one good name from the list.
			name = ShuffleGrab(mGame->GetUmlNames(), 1);

			//	Also we will grab 0-3 good attributes
			attributes = ShuffleGrab(mGame->GetUmlAttributes(), (rand() % 4) );

			//	Shuffle and grab one bad operation from the list.
			operations = ShuffleGrab(mGame->GetUmlBadOperations(), 1);

			//	Set our message value to the message held by the bad operation
			message = operations[0].GetDataMessage();

			//	Also we will grab 0-2 good operations
			vector <CUmlData> goodOperations = ShuffleGrab(mGame->GetUmlOperations(), (rand() % 3));

			//	put them in with the bad one
			operations.insert(operations.begin(), goodOperations.begin(), goodOperations.end());
		}

		//	Emit the node we just spawned values for
		EmitBad(message, name, attributes, operations);

		//	Modify our spawn probability for next node
		SetModifier(GetModifier() - 1);

	}
	//	Else, we emit a good node
	else
	{
		//	Shuffle and grab one good name from the list.
		name = ShuffleGrab(mGame->GetUmlNames(), 1);

		//	Also we will grab 0-3 good attributes
		attributes = ShuffleGrab(mGame->GetUmlAttributes(), (rand() % 4));

		//	And 0-3 good operations
		operations = ShuffleGrab(mGame->GetUmlOperations(), (rand() % 4));


		//	Emit the node we just spawned values for
		EmitGood(L"Unfair!", name, attributes, operations);

		//	Modify our spawn probability for next node
		SetModifier(GetModifier() - 1);
	}

}

//	Shuffle the vector and grab the first count number of items
std::vector<CUmlData> CEmitter::ShuffleGrab(std::vector<CUmlData> dataVector, int count)
{

	//	shuffle input vector
	random_shuffle(dataVector.begin(), dataVector.end());

	vector<CUmlData> nodeData;

	for (auto i = 0; i != count; i++)
	{
		nodeData.push_back(dataVector[i]);
	}

	//	Return the new vector to be inserted into node
	return nodeData;
}


