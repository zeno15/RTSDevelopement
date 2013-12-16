#include "FontManager.h"


FontManager::FontManager(void) :
	mFonts(FontID::NUMFONTS, nullptr)
{
	mFilepaths.push_back("Resources/Fonts/OpenSans-Bold.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-BoldItalic.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-ExtraBold.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-ExtraBoldItalic.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-Italic.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-Light.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-LightItalic.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-Regular.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-Semibold.ttf");
	mFilepaths.push_back("Resources/Fonts/OpenSans-SemiboldItalic.ttf");
}

FontManager::~FontManager(void)
{
	unloadAllFonts();
	mFilepaths.clear();
}


void FontManager::loadAllFonts(void)
{
	for (unsigned int i = 0; i < mFonts.size(); i += 1)
	{
		if (mFonts.at(i) != nullptr) continue;

		mFonts.at(i) = new sf::Font();
		mFonts.at(i)->loadFromFile(mFilepaths.at(i));
	}
}
void FontManager::unloadAllFonts(void)
{
	for (unsigned int i = 0; i < mFonts.size(); i += 1)
	{
		if (mFonts.at(i) == nullptr) continue;

		delete mFonts.at(i);
		mFonts.at(i) = nullptr;
	}
}

sf::Font *FontManager::getFont(FontID _id)
{
	return mFonts.at(_id);
}