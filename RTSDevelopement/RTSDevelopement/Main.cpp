#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "FontManager.h"

int main()
{
	_CrtMemState &state1 = _CrtMemState();
	_CrtMemState &state2 = _CrtMemState();
	_CrtMemState &state3 = _CrtMemState();
	_CrtMemCheckpoint(&state1);

	///////////////////////////////////
	//
	// Call all code in between the two _CrtMemCheckpoint's to check for memory leaks
	//
	///////////////////////////////////

	FontManager *mFontManager = new FontManager();
	mFontManager->loadAllFonts();
	delete mFontManager;

	_CrtMemCheckpoint(&state2);

	if (_CrtMemDifference(&state3, &state1, &state2))
	{
		_CrtDumpMemoryLeaks();
	}
	
	return 0;
}