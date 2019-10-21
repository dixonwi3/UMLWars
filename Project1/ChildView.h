
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "UmlGame.h"

// CChildView window

/**
 * Class that handles user interactions with the game
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

private:
	/// an object that describes our game
	CUmlGame mGame;

	/// True until the first time we draw
	bool mFirst = true;

	/// Last time we read the timer
	long long mLastTime;

	/// Rate the timer updates
	double mTimeFrequency;

/// Operations
public:

/// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

/// Implementation
public:
	virtual ~CChildView();

	/// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDifficultyExpert();
	afx_msg void OnDifficultyHard();
	afx_msg void OnDifficultyMedium();
	afx_msg void OnDifficultyEasy();

	/** When mouse button pressed
	* \param nFlags flag for change
	* \param point where pointing
	*/
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/** On timer function
	* \param nIDEvent pointer to event
	*/
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

