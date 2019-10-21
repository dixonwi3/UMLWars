
// Project1.h : main header file for the Project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject1App:
// See Project1.cpp for the implementation of this class
//

/**
 * Base class for our windows app for playing the game
 */
class CProject1App : public CWinApp
{
public:
	CProject1App() noexcept;


// Overrides
public:
	/**
	* Initialize the game
	* \return BOOL if starting
	*/
	virtual BOOL InitInstance();

	/**
	* Exit the game
	* \return int for exiting
	*/
	virtual int ExitInstance();

// Implementation

public:
	/// Message for app 
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

//	GDI+ Support
private:
	/// For drawing
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	/// Token for drawing
	ULONG_PTR gdiplusToken = 0;

};

extern CProject1App theApp;
