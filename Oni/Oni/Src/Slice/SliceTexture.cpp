#include "SliceTexture.hpp"
#include "../MyLibrary.hpp"


namespace Oni
{

	SliceTexture::SliceTexture(const String& textureName, const Size& sliceSize, const Point& pos)
		: mTextureName(textureName)
		, mSliceSize(sliceSize)
		, mMirror(false)
		, mChangeSpan(0, 0)
		, mAnimationName(U"Default")
	{
		setAnimation(mAnimationName, Animation(0, Array<Point>{pos}, false));
	}


	void SliceTexture::setTextureName(const String& textureName, const Size& sliceSize)
	{
		mTextureName = textureName;
		mSliceSize   = sliceSize;
	}


	bool SliceTexture::changeTexture()
	{
		bool spanIsFinished = mChangeSpan.update();

		// 画像がループするとき
		if (mAnimationMap.find(mAnimationName)->second.IS_LOOP)
		{
			if (spanIsFinished)
			{
				mChangeSpan.restart();
			}

			return true;
		}

		return spanIsFinished;
	}


	void SliceTexture::start(const String name)
	{
		if (!mAnimationMap.count(name))
		{
			printDebug(U"[SliceTexture::start]");
			printDebug(U"登録されていないアニメーションです");
			printDebug(U"mTextureName > " + mTextureName);
			printDebug(U"name > " + name);
			return;
		}

		mAnimationName = name;
		mChangeSpan 
			= Linearly<double>
				(
					mAnimationMap.find(name)->second.TIME, 
					(double)mAnimationMap.find(name)->second.POS_LIST.size()
				);
	}


	void SliceTexture::startAnotherAnimation(const String name)
	{
		if (name == mAnimationName) { return; }
		start(name);
	}


	TextureRegion SliceTexture::getTexture() const
	{
		const auto& POS_LIST = mAnimationMap.find(mAnimationName)->second.POS_LIST;

		Point texturePos = POS_LIST[Min(POS_LIST.size() - 1, (size_t)mChangeSpan.getValue())];

		auto texture = TextureAsset(mTextureName)(texturePos * mSliceSize, mSliceSize);

		if (mMirror) { texture = texture.mirrored(); }

		return texture;
	}

}
