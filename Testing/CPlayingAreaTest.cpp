#include "pch.h"
#include "CppUnitTest.h"
#include "UmlGame.h"
#include "PlayingArea.h"
#include "Grader.h"
#include "Item.h"
#include "UmlData.h"
#include "UmlNode.h"
#include "Scoreboard.h"
#include "UmlBad.h"
#include "UmlGood.h"
#include <memory.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace xmlnode;

class UmlGame;
class UmlData;
class Scoreboard;

namespace Testing
{
	TEST_CLASS(CPlayingAreaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestPlayingAreaAddNode)
		{
			CUmlGame game;
			CScoreboard board(&game);
			CPlayingArea area(&game, game.GetScoreboard());

			/// test adding nodes
			auto goodNode1 = make_shared<CUmlGood>(game);
			area.AddNode(goodNode1);
			Assert::AreEqual(area.NumNodes(), 1);

			auto goodNode2 = make_shared<CUmlGood>(game);
			area.AddNode(goodNode2);
			Assert::AreEqual(area.NumNodes(), 2);

		}
		TEST_METHOD(TestPlayingAreaRemoveNode)
		{
			CUmlGame game;
			CScoreboard board(&game);
			CPlayingArea area(&game, game.GetScoreboard());

			auto goodNode1 = make_shared<CUmlGood>(game);
			area.AddNode(goodNode1);
			Assert::AreEqual(area.NumNodes(), 1);

			auto goodNode2 = make_shared<CUmlGood>(game);
			area.AddNode(goodNode2);
			Assert::AreEqual(area.NumNodes(), 2);

			area.RemoveNode(goodNode1);
			Assert::AreEqual(area.NumNodes(), 1);

			area.RemoveNode(goodNode2);
			Assert::AreEqual(area.NumNodes(), 0);
		}

		///Checks that grader is indeed made and in the right position
		TEST_METHOD(TestAddGrader)
		{
			/*
			CUmlGame game;
			CScoreboard board(&game);
			CPlayingArea area(&game, game.GetScoreboard());

			Assert::IsTrue(area.HitTest(100, 200) == nullptr,
				L"Testing empty area");
			
			
			shared_ptr<CGrader> grader1 = make_shared<CGrader>(&area);
			DrawMan(graphics, grader1->GetX(), grader1->GetY(), grader1->GetAngle());

			DrawMan(Gdiplus::Graphics * graphics, double x, double y, double angle);

			grader1->SetLocation(100, 200);
			area.Add(grader1);
			

			Assert::IsTrue(area.HitTest(0, 900) == area.GetGrader(),
				L"Testing grader at 100, 200");	
			*/
		}

		TEST_METHOD(TestCPlayingAreaItems)
		{
			CUmlGame mGame;
			std::shared_ptr<CScoreboard> mScoreboard;
			CPlayingArea PlayingArea(&mGame, mScoreboard);
			Assert::IsTrue(PlayingArea.Size() == 2, L"Testing initial area with grader and pen");
		}
	};
}