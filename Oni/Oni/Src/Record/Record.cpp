#include "Record.hpp"


namespace
{
	// åÖÇÃç≈ëÂíl
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
			// iåÖñ⁄Çí«â¡
			dataList.emplace_back((mValue >> i) & 1);
		}
	}


	void Record::setValueFromDecryption(std::list<int32>& dataList)
	{
		mValue = 0;

		for (int32 i = 0; i < mDigit; ++i)
		{
			if (dataList.empty()) { return; }

			// iåÖñ⁄Ç…í«â¡
			mValue |= dataList.front() << i;
			dataList.pop_front();
		}
	}

}
