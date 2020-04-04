#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"


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

	public:

		/// <summary>
		/// オブジェクト
		/// </summary>
		/// <param name="pos" > 生成座標 </param>
		/// <param name="size"> サイズ   </param>
		/// <param name="type"> 種類     </param>
		GameObject(const Vec3& pos, const Vec3 size, const ObjectType& type);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}