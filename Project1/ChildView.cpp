
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include <string>

using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

/// Frame duration in milliseconds
const int FrameDuration = 10;


CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DIFFICULTY_EXPERT, &CChildView::OnDifficultyExpert)
	ON_COMMAND(ID_DIFFICULTY_HARD, &CChildView::OnDifficultyHard)
	ON_COMMAND(ID_DIFFICULTY_MEDIUM, &CChildView::OnDifficultyMedium)
	ON_COMMAND(ID_DIFFICULTY_EASY, &CChildView::OnDifficultyEasy)
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);


	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting
	
	CDoubleBufferDC dc(&paintDC); // device context for painting
	
	Graphics graphics(dc.m_hDC);
	
	CRect rect;
	GetClientRect(&rect);	
	
	mGame.AddGraphics(&graphics);
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());

	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages

	if (mFirst)
	{
		mFirst = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, frequency;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&frequency);

		mLastTime = time.QuadPart;
		mTimeFrequency = double(frequency.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFrequency;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);

}


/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}

/**
 * Set difficulty to expert
 */
void CChildView::OnDifficultyExpert()
{
	mGame.SetDifficulty(L"Expert");
}

/**
 * Set difficulty to hard
 */
void CChildView::OnDifficultyHard()
{
	mGame.SetDifficulty(L"Hard");
}

/**
 * Set difficulty to medium
 */
void CChildView::OnDifficultyMedium()
{
	mGame.SetDifficulty(L"Medium");
}

/**
 * Set difficulty to easy
 */
void CChildView::OnDifficultyEasy()
{
	mGame.SetDifficulty(L"Easy");
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMButtonDown(nFlags, point);
}

/** When mouse moved
* \param nFlags flag for change
* \param point where pointing
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mGame.OnMouseMove(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
	Invalidate();
}


/**
 * Handle a left button down mouse message
 * \param nFlags Message flags
 * \param point Mouse location
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mGame.OnLButtonDown(point.x, point.y);
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}
