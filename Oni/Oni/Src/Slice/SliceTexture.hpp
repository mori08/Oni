#pragma once


#include "Linearly.hpp"
#include "Animation.hpp"


namespace Oni
{

	/// <summary>
	/// 1枚の画像を複数の画像に分け,
	/// 切り替えなどを行えるようにする.
	/// </summary>
	class SliceTexture
	{
	private:

		// 画像の名前
		String mTextureName;

		// 画像を切り分ける大きさ
		Size mSliceSize;

		// true のとき左右反転して描画
		bool mMirror;

		// 画像を遷移する時間
		Linearly<double> mChangeSpan;

		// 現在のAnimationの名前
		String mAnimationName;

		// Animationを管理するマップ
		std::unordered_map<String, Animation> mAnimationMap;

	public:

		/// <summary>
		/// 画像の切り分け
		/// </summary>
		/// <param name="textureName"> 画像の名前             </param>
		/// <param name="sliceSize">   画像を切り分ける大きさ </param>
		/// <param name="pos">         画像の初期番号         </param>
		SliceTexture(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// 画像の名前の設定
		/// </summary>
		/// <param name="textureName"> 画像の名前             </param>
		/// <param name="sliceSize">   画像を切り分ける大きさ </param>
		void setTextureName(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// アニメーションの設定
		/// </summary>
		/// <param name="anim"> アニメーション </param>
		void setAnimation(const String& name, const Animation& anim)
		{
			mAnimationMap.try_emplace(name, anim);
		}

		/// <summary>
		/// 画像の変更
		/// </summary>
		/// <returns>
		/// 画像の切り替えが終了したとき true , そうでないとき false
		/// ループしているときは true を常に返すので注意
		/// </returns>
		bool update();

		/// <summary>
		/// 画像の反転
		/// </summary>
		void mirror()
		{
			mMirror = !mMirror;
		}

		/// <summary>
		/// アニメーションの開始
		/// </summary>
		/// <param name="name"> アニメーションの名前 </param>
		void start(const String name);

		/// <summary>
		/// 別アニメーションの開始
		/// </summary>
		/// <param name="name"> アニメーション名 </param>
		void startAnotherAnimation(const String name);

		/// <summary>
		/// 画像の変更
		/// </summary>
		TextureRegion getTexture() const;

	};
	
}