#include "ButtonManager.hpp"


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

}
