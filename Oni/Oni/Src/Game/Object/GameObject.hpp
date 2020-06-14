#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"
#include "../ObjectData/Event/ObjectEventData.hpp"
#include "../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameManagerで使用するオブジェクト
	/// </summary>
	class GameObject
	{
	protected:

		// 名前
		const String mName;

		// 交差判定用の直方体
		Collider mCollider;

		// オブジェクトの種類
		ObjectType mType;

		// イベント用のデータ
		Optional<ObjectEventData> mEventData;

		// 画像とアニメーション
		SliceTexture mSlide;

		// true のとき非表示
		bool mIsHiding;

	public:

		/// <summary>
		/// オブジェクト
		/// </summary>
		/// <param name="name"    > 名前       </param>
		/// <param name="collider"> 当たり判定 </param>
		/// <param name="type"    > 種類       </param>
		/// <param name="slide"   > 画像       </param>
		GameObject(const String& name, const Collider& collider, const ObjectType& type, const SliceTexture& slide);

		/// <summary>
		/// y座標の比較
		/// </summary>
		bool operator<(const GameObject& another)const
		{
			return mCollider.centerPos().y < another.mCollider.centerPos().y;
		}

	public:

		/// <summary>
		/// イベント時の更新
		/// </summary>
		virtual void updateEvent();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// コライダーの取得
		/// </summary>
		Collider& getCollider()
		{
			return mCollider;
		}

		/// <summary>
		/// 削除する条件
		/// </summary>
		/// <returns> true のとき削除 </returns>
		virtual bool eraseAble() const;

		/// <summary>
		/// コライダーの描画
		/// </summary>
		void drawCollider() const;

		/// <summary>
		/// 名前の取得
		/// </summary>
		const String& getName() const
		{
			return mName;
		}

		/// <summary>
		/// イベントデータの取得
		/// </summary>
		/// <returns> イベントデータ </returns>
		Optional<ObjectEventData>& getEventData()
		{
			return mEventData;
		}

	protected:

		/// <summary>
		/// ColliderとSliceTextureから画像を描画する座標を決定
		/// </summary>
		Point getDrawTexturePoint() const;

		/// <summary>
		/// アニメーションを設定する
		/// </summary>
		/// <param name="name"> 名前           </param>
		/// <param name="anim"> アニメーション </param>
		void setAnim(const String& name, const Animation& anim);

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}