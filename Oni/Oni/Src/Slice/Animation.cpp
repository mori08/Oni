#include "Animation.hpp"


namespace Oni
{

	Animation::Animation(const PosOrder& posOrder, bool isLoop)
		: mTotalSecond(getTotalSecond(posOrder))
		, mPosOrder(getPosOrder(posOrder))
		, mIsLoop(isLoop)
	{
	}


	Point Animation::getTexture(double animSecond) const
	{
		if (mPosOrder.begin()->first < animSecond)
		{
			// �ŏ��̉摜
			return mPosOrder.begin()->second;
		}

		if (mPosOrder.rbegin()->first > animSecond)
		{
			// �Ō�̉摜
			return mPosOrder.rbegin()->second;
		}

		// �񕪒T���ŉ摜��I��
		size_t l = 0, g = mPosOrder.size() - 1;
		while (g - l > 1)
		{
			size_t mid = (l + g) / 2;
			if (mPosOrder[mid].first < animSecond)
			{
				g = mid;
			}
			else
			{
				l = mid;
			}
		}
		return mPosOrder[g].second;
	}


	double Animation::getTotalSecond(const PosOrder& posOrder)
	{
		double rtn = 0;
		for (const auto& p : posOrder) { rtn += p.first; }
		return rtn;
	}


	PosOrder Animation::getPosOrder(PosOrder posOrder)
	{
		for (int32 i = 1; i < posOrder.size(); ++i)
		{
			posOrder[i].first += posOrder[i - 1].first;
		}
		return std::move(posOrder);
	}

}
