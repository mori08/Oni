#include "SliceTexture.hpp"
#include "../MyLibrary.hpp"


namespace Oni
{

	SliceTexture::SliceTexture(const String& textureName, const Size& sliceSize)
		: mTextureName(textureName)
		, mSliceSize(sliceSize)
		, mMirror(false)
		, mChangeSpan(0)
		, mAnimationName(U"Default")
	{
		setAnimation(mAnimationName, Animation(PosOrder{ {0,Point::Zero()} }, false));
	}


	void SliceTexture::setTextureName(const String& textureName, const Size& sliceSize)
	{
		mTextureName = textureName;
		mSliceSize   = sliceSize;
	}


	bool SliceTexture::update()
	{
		mChangeSpan += Scene::DeltaTime();
		bool spanIsFinished = isFinished();

		// 画像がループするとき
		if (mAnimationMap.find(mAnimationName)->second.loop())
		{
			if (spanIsFinished)
			{
				mChangeSpan = 0;
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
		mChangeSpan = 0;
	}


	void SliceTexture::startAnotherAnimation(const String name)
	{
		if (name == mAnimationName) { return; }
		start(name);
	}


	TextureRegion SliceTexture::getTexture() const
	{
		const Point texturePos = mAnimationMap.find(mAnimationName)->second.getTexture(mChangeSpan);

		auto texture = TextureAsset(mTextureName)(texturePos * mSliceSize, mSliceSize);

		if (mMirror) { texture = texture.mirrored(); }

		return texture;
	}

}
