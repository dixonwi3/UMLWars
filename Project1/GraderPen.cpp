/**
 * \file GraderPen.cpp
 *
 * \author Team Hoare
 */


#include "pch.h"
#include "GraderPen.h"
#include "playingArea.h"
#include "UmlGame.h"


#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>

 /// File name for the pen
const std::wstring filename = L"images/redpen.png";

/// Angle of pen
const float CGraderPen::Angle = -1.078f;

/// Distance of the pen from the grader in pixels
const double CGraderPen::DistancePG = 61.3;

/// Pen speed in pixels per second
const int Speed = 1000;

/// Pen initial X location in pixels
const int PositionX = 30;

/// Pen initial Y location in pixels
const int PositionY = 850;


/**
 * Constructor
 *
 * \param game The game this item is a member of
 */
CGraderPen::CGraderPen(CPlayingArea* game) : CMovingItem(game, filename)
{
	SetLocation(PositionX, PositionY);
}

/**
 * Destructor
 */
CGraderPen::~CGraderPen()
{
}
