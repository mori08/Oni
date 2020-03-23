#include "ButtonManager.hpp"
#include "../MyLibrary.hpp"


namespace Oni
{

	void ButtonManager::registerButton(const String& name, const Rect& region)
	{
		mButtonMap[name] = std::make_shared<Button>(name, region);

		// ���Ƃ��Ƌ󂾂����Ƃ�
		if (mButtonMap.size() == 1) { mSelectedButtonPtr = mButtonMap[name]; }
	}


	void ButtonManager::registerButton(const Button& button)
	{
		mButtonMap[button.getName()] = std::make_shared<Button>(button);

		// mButtonMap�����Ƃ��Ƌ󂾂����Ƃ�
		if (mButtonMap.size() == 1) { mSelectedButtonPtr = mButtonMap[button.getName()]; }
	}


	void ButtonManager::setSelectedButton(const String& name)
	{
		if (!mButtonMap.count(name))
		{
			printDebug(U"[ButtonManager::setSelectedButton]");
			printDebug(U"���݂��Ȃ��{�^�����w�肳��܂���");
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
			printDebug(U"���݂��Ȃ��{�^�����w�肳��܂���");
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
		// �}�E�X���d�˂��{�^����I��
		for (const auto& button : mButtonMap)
		{
			if (button.second->getRegion().mouseOver())
			{
				mSelectedButtonPtr = button.second;
				break;
			}
		}

		// �I�𒆂̃{�^�����N���b�N�����Ƃ�
		if (mSelectedButtonPtr->getRegion().leftClicked())
		{
			mSelectedButtonPtr->OnClick();
		}
	}

}