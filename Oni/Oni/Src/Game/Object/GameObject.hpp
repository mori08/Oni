#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"
#include "../ObjectData/Battle/ObjectBattleData.hpp"
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

		// バトル用のデータ
		Optional<ObjectBattleData> mBattleData;

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
		/// バトル時の更新
		/// </summary>
		virtual void updateBattle();

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
		/// コライダーの描画
		/// </summary>
		void drawCollider() const;

		/// <summary>
		/// 他のオブジェクトへ判定の譲渡(バトルでの使用)
		/// </summary>
		/// <param name="another"> 他オブジェクト </param>
		virtual void passAnother(GameObject& another) const;

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
		/// 他のオブジェクトの判定を受取(バトルでの使用)
		/// </summary>
		/// <param name="checkInfo">  </param>
		virtual void checkAnother(const ObjectBattleData::CheckInfo& chekcInfo);

		/// <summary>
		/// ColliderとSliceTextureから画像を描画する座標を決定
		/// </summary>
		Point getDrawTexturePoint() const;

		/// <summary>
		/// オブジェクトの種類と衝突の判定
		/// </summary>
		/// <param name="checkInfo"> 判定確認用の情報 </param>
		/// <param name="checkType"> 指定する種類     </param>
		/// <returns>
		/// 指定の種類のオブジェクトかつ衝突しているとき true , そうでないとき false
		/// </returns>
		bool checkTypeAndCollision(const ObjectBattleData::CheckInfo& checkInfo, const ObjectType& checkType) const
		{
			return (checkInfo.type & checkType) && mCollider.intersects(checkInfo.collider);
		}

		/// <summary>
		/// 指定の種類のオブジェクトのとき座標の取得
		/// </summary>
		/// <param name="checkType"> 指定する種類 </param>
		/// <returns>
		/// 座標
		/// </returns>
		Optional<Vec3> checkTypeAndGetPos(const ObjectType& checkType) const;

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}