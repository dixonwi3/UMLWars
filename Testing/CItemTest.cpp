#include "pch.h"
#include "CppUnitTest.h"
#include "UmlGame.h"

#include "playingarea.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		CItemMock(CPlayingArea* playingarea) : CItem(playingarea) {}

	};
	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestItemConstructor)
		{
			CUmlGame game;
			CScoreboard board(&game);
			CPlayingArea playingArea(&game, game.GetScoreboard());
			CItemMock item(&playingArea);
		}


		TEST_METHOD(TestCItemLocation)
		{
			// Construct an item to test
			CUmlGame game;
			std::shared_ptr<CScoreboard> mScoreboard;
			CPlayingArea playingarea(&game, mScoreboard);
			CItemMock item(&playingarea);

//			Assert::AreEqual(0, item.
//				, 0);
			Assert::AreEqual(0, item.GetY(), 0);

			item.SetLocation(121.38, 121.38);
			Assert::AreEqual(121.38, item.GetX(), 0.0001);
			Assert::AreEqual(121.38, item.GetY(), 0.0001);
		};

		TEST_METHOD(TestCItemSpeed)
		{
			// Construct an item to test
			CUmlGame game;
			std::shared_ptr<CScoreboard> mScoreboard;
			CPlayingArea playingarea(&game, mScoreboard);
			CItemMock item(&playingarea);

			Assert::AreEqual(0, item.GetXSpeed(), 0);
			Assert::AreEqual(0, item.GetYSpeed(), 0);

			item.SetSpeed(121.38, 121.38);
			Assert::AreEqual(121.38, item.GetXSpeed(), 0.0001);
			Assert::AreEqual(121.38, item.GetYSpeed(), 0.0001);

		};

		TEST_METHOD(TestCItemAngle)
		{
			// Construct an item to test
			CUmlGame game;
			std::shared_ptr<CScoreboard> mScoreboard;
			CPlayingArea playingarea(&game, mScoreboard);
			CItemMock item(&playingarea);

			Assert::AreEqual(0, item.GetAngle(), 0);

			item.SetAngle(121.38);
			Assert::AreEqual(121.38, item.GetAngle(), 0.0001);


		};
	};
}
