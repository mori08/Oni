#pragma once


#include "Record.hpp"


namespace Oni
{
	/// <summary>
	/// レコード (セーブデータ) のロードやセーブ,
	/// フラグや数値の変更,取得を行えます.
	/// </summary>
	class RecordManager
	{
	public:

		enum class LoadResult
		{
			NEW_GAME, // RECORD.txtが存在しないとき
			CONTINUE, // RECORD.txtを正しく読み込めたとき
			ERROR     // RECORD.txtを正しく読み込めないとき
		};

	private:

		// レコードのマップ
		std::map<String, Record> mRecordMap;

	private:

		RecordManager();

		RecordManager(const RecordManager&) = default;
		RecordManager& operator=(const RecordManager&) = default;
		RecordManager(RecordManager&&) = default;
		RecordManager& operator=(RecordManager&&) = default;

	public:

		/// <summary>
		/// シングルトンとして管理しているRecordManagerのインスタンスの取得
		/// </summary>
		/// <returns>
		/// インスタンス
		/// </summary>
		static RecordManager& instance()
		{
			static RecordManager recordManager;
			return recordManager;
		}

		/// <summary>
		/// RECORD.txtからロード
		/// </summary>
		LoadResult load();

		/// <summary>
		/// 全レコードの初期化
		/// </summary>
		void initAllRecord();

		/// <summary>
		/// RECORD.txtにセーブ
		/// </summary>
		void save();

		/// <summary>
		/// 管理しているレコードの内容の表示
		/// </summary>
		/// <remarks>
		/// デバッグ用
		/// </remarks>
		void printAllRecord();

		/// <summary>
		/// レコードの設定
		/// </summary>
		/// <param name="name" > 名前         </param>
		/// <param name="value"> 変更したい値 </param>
		void setRecord(const String& name, int32 value);

		/// <summary>
		/// レコードの取得
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <returns> レコードの値 </returns>
		int32 getRecord(const String& name) const;

	private:

		/// <summary>
		/// レコードの暗号化
		/// </summary>
		/// <returns>
		/// 暗号化した後の文字列
		/// </returns>
		String encryption() const;

		/// <summary>
		/// 暗号文を復号, フラグのリストに格納
		/// </summary>
		/// <param name="str"> 暗号文 </param>
		/// <returns> 復号に成功したとき true , そうでないとき false </returns>
		bool decryption(const String& str);

	};
}