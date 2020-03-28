#include "Record.hpp"


namespace
{
	// ���̍ő�l
	constexpr int32 MAX_DIGIT = 30;
}


namespace Oni
{

	Record::Record(int32 digit, int32 defaultValue)
		: mDigit(Clamp(digit, 1, MAX_DIGIT))
		, mDefaultValue(Clamp(defaultValue, 0, (1 << digit) - 1))
		, mValue(mDefaultValue)
	{
		sDigitTotal += mDigit;
	}


	void Record::addRecordToEncryptionList(std::list<int32>& dataList) const
	{
		for (int32 i = 0; i < mDigit; ++i)
		{
			// i���ڂ�ǉ�
			dataList.emplace_back((mValue >> i) & 1);
		}
	}


	void Record::setValueFromDecryption(std::list<int32>& dataList)
	{
		mValue = 0;

		for (int32 i = 0; i < mDigit; ++i)
		{
			if (dataList.empty()) { return; }

			// i���ڂɒǉ�
			mValue |= dataList.front() << i;
			dataList.pop_front();
		}
	}

}
