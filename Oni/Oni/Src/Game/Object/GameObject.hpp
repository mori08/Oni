#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"
#include "../ObjectData/Battle/ObjectBattleData.hpp"
#include "../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameManagerで使用するオブジェクト
	/// </summary>
	class GameObject
	{
	protected:

		// 交差判定用の直方体
		Collider mCollider;

		// オブジェクトの種類
		ObjectType mType;

		// バトル用のデータ
		Optional<ObjectBattleData> mBattleData;

		// 画像とアニメーション
		SliceTexture mSlide;

	public:

		/// <summary>
		/// オブジェクト
		/// </summary>
		/// <param name="collider"> 当たり判定 </param>
		/// <param name="type"    > 種類       </param>
		/// <param name="slide"   > 画像       </param>
		GameObject(const Collider& collider, const ObjectType& type, const SliceTexture& slide);

		/// <summary>
		/// y座標の比較
		/// </summary>
		bool operator<(const GameObject& another)const
		{
			return mCollider.centerPos().y < another.mCollider.centerPos().y;
		}

	public:

		/// <summary>
		/// バトル時の更新
		/// </summary>
		virtual void updateBattle();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const;

	protected:

		/// <summary>
		/// ColliderとSliceTextureから画像を描画する座標を決定
		/// </summary>
		Point getDrawTexturePoint() const;

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}