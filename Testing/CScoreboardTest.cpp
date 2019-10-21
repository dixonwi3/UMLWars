#include "pch.h"
#include "CppUnitTest.h"
#include "UmlGame.h"
#include "Scoreboard.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CScoreboardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestScoreboardConstruct)
		{
			CUmlGame game;
			CScoreboard board(&game);
		}
		TEST_METHOD(TestScoreboardRaiseScore)
		{
			CUmlGame game;

			// test incrementing correct score
			game.GetScoreboard()->RaiseCorrect();
			Assert::IsTrue(game.GetScoreboard()->GetCorrect() == 1, L"Testing raising Correct scores.");

			// test incrememnting missed score
			game.GetScoreboard()->RaiseMissed();
			Assert::IsTrue(game.GetScoreboard()->GetMissed() == 1, L"Testing raising Missed scores.");

			// test incrememnting missed score
			game.GetScoreboard()->RaiseUnfair();
			Assert::IsTrue(game.GetScoreboard()->GetUnfair() == 1, L"Testing raising Unfair scores.");
		}
	};
}