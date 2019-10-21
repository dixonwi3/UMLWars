#include "pch.h"
#include "CppUnitTest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "XmlNode.h"
#include "Scoreboard.h"
#include "UmlData.h"
#include "UmlGame.h"
#include "PlayingArea.h"
#include "UmlNode.h"
#include "UmlGood.h"
#include "UmlBad.h"
#include "Emitter.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;
using namespace xmlnode;


class UmlGame;
class UmlData;
class Emitter;

namespace Testing
{
	TEST_CLASS(CUmlNodeTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}


		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring & filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		/**
		* Test to ensure an aquarium .aqua file is empty
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());


			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<xml/>")));
		}


		/**
		* Test to ensure successful load vectors mNames, mAttributes,
		* mOperations into uml game object
		*/
		TEST_METHOD(TestCUmlGameLoad)
		{

			//	Declare alternate file names for loading of game1 uml values
			const wstring file2 = L"data/umlTest.xml";

			//	Create game
			CUmlGame game1;


			//	Assert correct placement of xml data we just loaded at runtime
			//	Good data
			Assert::IsTrue(game1.GetUmlNames().size() == 4, L"Testing successful load into mNames vector.");
			Assert::IsTrue(game1.GetUmlAttributes().size() == 6, L"Testing successful load into mAttributes vector.");
			Assert::IsTrue(game1.GetUmlOperations().size() == 7, L"Testing successful load into mOperations vector.");
			
			//	Bad data
			Assert::IsTrue(game1.GetUmlBadNames().size() == 4, L"Testing successful load into mNames vector.");
			Assert::IsTrue(game1.GetUmlBadAttributes().size() == 10, L"Testing successful load into mAttributes vector.");
			Assert::IsTrue(game1.GetUmlBadOperations().size() == 3, L"Testing successful load into mOperations vector.");
			
			
			
			//	Load a new file into game, clearing out the data we just loaded from file1
			game1.Load(file2);


			//	Assert correct placement of xml data we just loaded (also ensure we cleared out the last)
			Assert::IsTrue(game1.GetUmlNames().size() == 4, L"Testing successful loading of new file into mNames vector.");
			Assert::IsTrue(game1.GetUmlAttributes().size() == 0, L"Testing successful loading of new file into mAttributes vector.");
			Assert::IsTrue(game1.GetUmlOperations().size() == 0, L"Testing successful loading of new file into mOperations vector.");
			//	Assert correct placement of xml data we just loaded (also ensure we cleared out the last)
			Assert::IsTrue(game1.GetUmlNames().size() == 4, L"Testing successful loading of new file into mNames vector.");
			Assert::IsTrue(game1.GetUmlAttributes().size() == 0, L"Testing successful loading of new file into mAttributes vector.");
			Assert::IsTrue(game1.GetUmlOperations().size() == 0, L"Testing successful loading of new file into mOperations vector.");



			//	Load absolutely nothing, blank filename
			game1.Clear();

			//	Assert empty on each container after loading an empty file
			Assert::IsTrue(game1.GetUmlNames().empty(), L"Testing empty mNames vector.");
			Assert::IsTrue(game1.GetUmlAttributes().empty(), L"Testing empty mAttributes vector.");
			Assert::IsTrue(game1.GetUmlOperations().empty(), L"Testing empty mOperations vector.");
			

		}

		/**
		* Test to ensure successful creation of uml nodes, good and bad
		*/
		TEST_METHOD(TestCUmlNodeCreate)
		{
			//	Create game
			CUmlGame game1;
			CPlayingArea *area;
			CScoreboard board(&game1);

			//	Initialize good node variables
			wstring message = L"Unfair!";
			vector<CUmlData> goodName{ game1.GetUmlNames()[0] };
			vector<CUmlData> goodAttributes{ game1.GetUmlAttributes()[0] };
			vector<CUmlData> goodOperations{ game1.GetUmlOperations()[0] };


			//	Create a good node object
			CUmlGood goodNode1(game1);

			//	Set values
			goodNode1.SetName(goodName);
			goodNode1.SetAttributes(goodAttributes);
			goodNode1.SetOperations(goodOperations);


			//	Create a bad node object
			CUmlGood badNode1(game1);

			//	Initialize bad node variables
			wstring badMessage = L"Language Artifact";
			vector<CUmlData> badName{ game1.GetUmlBadNames()[0] };
			vector<CUmlData> badAttributes{ game1.GetUmlAttributes()[0] };
			
			//	Set values
			badNode1.SetMessage(badMessage);
			badNode1.SetName(badName);
			badNode1.SetAttributes(badAttributes);


			//	Asserts to demonstrate successful setting and getting, creation of good node
			Assert::IsTrue(goodNode1.GetMessageW() == message, L"Testing successful creation of a goodNode item, message getter");
			Assert::IsTrue(goodNode1.GetAttributes().size() == 1, L"Testing successful creation of a goodNode item, attribute get and set");
			Assert::IsTrue(goodNode1.GetOperations().size() == 1, L"Testing successful creation of a goodNode item, operation get and set");
			
			//	Asserts to demonstrate successful setting and getting, creation of bad node
			Assert::IsTrue(badNode1.GetMessageW() == badMessage, L"Testing successful creation of a badNode item, name get and set");
			Assert::IsTrue(badNode1.GetName().size() == 1, L"Testing successful creation of a badNode item, name get and set");
			Assert::IsTrue(badNode1.GetAttributes().size() == 1, L"Testing successful creation of a badNode item, attribute get and set");
			

		}


	};
}