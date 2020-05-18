#include "ButtonManager.hpp"
#include "../MyLibrary.hpp"


namespace Oni
{

	Oni::ButtonManager::ButtonManager()
		: mSelectedButtonPtr(nullptr)
	{
	}


	void ButtonManager::registerButton(const String& name, const Rect& region)
	{
		mButtonMap[name] = std::make_shared<Button>(name, region);

		// もともと空だったとき
		if (mButtonMap.size() == 1) { mSelectedButtonPtr = mButtonMap[name]; }
	}


	void ButtonManager::registerButton(const Button& button)
	{
		mButtonMap[button.getName()] = std::make_shared<Button>(button);

		// mButtonMapがもともと空だったとき
		if (mButtonMap.size() == 1) { mSelectedButtonPtr = mButtonMap[button.getName()]; }
	}


	void ButtonManager::setSelectedButton(const String& name)
	{
		if (!mButtonMap.count(name))
		{
			printDebug(U"[ButtonManager::setSelectedButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"name > " + name);
			return;
		}

		mSelectedButtonPtr = mButtonMap[name];
	}


	void ButtonManager::setOnClick(const String& name, ButtonOnClick onClick)
	{
		if (!mButtonMap.count(name))
		{
			printDebug(U"[ButtonManager::setSelectedButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"name > " + name);
			return;
		}

		mButtonMap[name]->setOnClick(onClick);
	}


	void ButtonManager::clearButtonList()
	{
		mSelectedButtonPtr = nullptr;
		mButtonMap.clear();
	}


	void ButtonManager::update()
	{
		// ボタンの選択
		for (const auto& button : mButtonMap)
		{
			if (!button.second->getRegion().mouseOver()) { continue; }
				
			mSelectedButtonPtr = button.second;
			
			if (MouseL.up()) { mSelectedButtonPtr->OnClick(); }

			break;
		}
	}

}
