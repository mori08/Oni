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


	void ButtonManager::setVerticalAdjacentButton(const String& upName, const String& downName)
	{
		if (!mButtonMap.count(upName))
		{
			printDebug(U"[ButtonManager::setVerticalAdjacentButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"upName > " + upName);
			return;
		}

		if (!mButtonMap.count(downName))
		{
			printDebug(U"[ButtonManager::setVerticalAdjacentButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"downName > " + downName);
			return;
		}

		ButtonPtr upButton   = mButtonMap[upName];
		ButtonPtr downButton = mButtonMap[downName];

		upButton->  setAdjacentButton(KeyDown, downButton);
		downButton->setAdjacentButton(KeyUp  , upButton  );
	}


	void ButtonManager::setHorizontalAdjacentButton(const String& leftName, const String& rightName)
	{
		if (!mButtonMap.count(leftName))
		{
			printDebug(U"[ButtonManager::setHorizontalAdjacentButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"leftName > " + leftName);
			return;
		}

		if (!mButtonMap.count(rightName))
		{
			printDebug(U"[ButtonManager::setHorizontalAdjacentButton]");
			printDebug(U"存在しないボタンが指定されました");
			printDebug(U"rightName > " + rightName);
			return;
		}

		ButtonPtr leftButton  = mButtonMap[leftName];
		ButtonPtr rightButton = mButtonMap[rightName];

		leftButton ->setAdjacentButton(KeyRight, rightButton);
		rightButton->setAdjacentButton(KeyLeft , leftButton );
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
		if (auto buttonOpt = mSelectedButtonPtr->getAdjacentButton())
		{
			mSelectedButtonPtr = buttonOpt.value();
		}

		// 決定キーを押したときの処理
		if (KeyZ.up())
		{
			mSelectedButtonPtr->OnClick();
		}
	}

}
