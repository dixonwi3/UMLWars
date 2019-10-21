#include "pch.h"
#include "CppUnitTest.h"
#include "UmlGame.h"
#include "Scoreboard.h"
#include "playingarea.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{

	class CItemMock : public CItem
	{
	public:
		CItemMock(CPlayingArea* playingarea) : CItem(playingarea) {}
	};

	TEST_CLASS(CUmlGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestUmlGameConstruct)
		{
			CUmlGame game;
		}

		TEST_METHOD(TestScoreboardConstruct)
		{
			CUmlGame game;
			CScoreboard board(&game);
		}


	};
}