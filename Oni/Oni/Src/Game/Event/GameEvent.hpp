#pragma once


#include "../Board/Text/TextBoard.hpp"


namespace Oni
{

	/// <summary>
	/// イベント管理
	/// </summary>
	class GameEvent
	{
	private:

		// イベント内容
		std::map<String, Array<Array<String>>> mData;

		// イベント名
		String mEventName;

		// 読み込み中の行
		int32 mReadingRow;

		// イベント用の処理
		std::map<String, std::function<void()>> mEventFunc;

		// テキストボックス
		std::unique_ptr<TextBoard> mTextBoard;

		// 待ち時間
		double mWaitSecond;

		// エラーが見つかったとき true にしてイベントを停止
		bool mError;

	public:

		GameEvent();

		/// <summary>
		/// イベントを記述したcsvファイルのロード
		/// </summary>
		/// <param name="dirName"> ディレクトリの名前 </param>
		void load(const FilePath& dirName);

		/// <summary>
		/// 指定したイベントに初期位置に飛ぶ
		/// </summary>
		/// <param name="eventName"> イベント名 </param>
		void jamp(const String& eventName);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// エラーメッセージの出力
		/// </summary>
		/// <param name="funcName"> 処理名 </param>
		void outputErrorMessage(const String& funcName);

	private:

		/// <summary>
		/// 待ち
		/// </summary>
		void wait();

		/// <summary>
		/// オブジェクトの移動
		/// </summary>
		void moveObject();

		/// <summary>
		/// オブジェクトの演出
		/// </summary>
		void actObject();

		/// <summary>
		/// オブジェクトのアニメーション開始
		/// </summary>
		void startAnim();

		/// <summary>
		/// テキストの表示
		/// </summary>
		void setText();

	};

}