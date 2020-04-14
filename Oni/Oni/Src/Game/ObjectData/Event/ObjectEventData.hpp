#pragma once


#include"../../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameObjectがもつEventState用のデータ
	/// </summary>
	class ObjectEventData
	{
	private:

		// イベント用関数
		std::unordered_map<String, std::function<void()>> mActMap;

		// 移動時間
		double mMoveSecond;

	public:

		ObjectEventData(SliceTexture& slide);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 移動時間の設定
		/// </summary>
		/// <param name="moveSecond"> 移動時間 </param>
		void setMoveSecond(double moveSecond)
		{
			mMoveSecond = moveSecond;
		}

		/// <summary>
		/// 移動中かどうか示す
		/// </summary>
		/// <returns> true のとき移動中 </returns>
		bool isMoving() const
		{
			return mMoveSecond > 0;
		}

		/// <summary>
		/// イベント用関数の設定
		/// </summary>
		/// <param name="actName"> 名前           </param>
		/// <param name="actFunc"> イベント用関数 </param>
		void setAct(const String& actName, const std::function<void()>& actFunc)
		{
			mActMap[actName] = actFunc;
		}

		/// <summary>
		/// イベント用関数が存在するか確認
		/// </summary>
		/// <param name="actName"> 名前 </param>
		/// <returns> 存在するとき true , しないとき false </returns>
		bool isExistAct(const String& actName) const
		{
			return mActMap.count(actName);
		}

		/// <summary>
		/// イベント用関数を実行
		/// </summary>
		/// <param name="actName"> 名前 </param>
		void act(const String& actName)
		{
			mActMap[actName]();
		}

	};
}