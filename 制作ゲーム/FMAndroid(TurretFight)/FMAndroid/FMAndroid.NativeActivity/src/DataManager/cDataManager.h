#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDataManager.h												*/
/*  @brief		:	データ管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/01/27													*/
/*																				*/
/*==============================================================================*/

/*  データ管理クラスの使い方
	〇共通事項
	１．データ管理クラスのセーブデータ構造体のメンバに事前に保存したい内容を追加しておく。

	〇書き込み
	１．データ管理クラスのセーブデータ変数の値を書き込んでおく(SetSaveData)
	２．データ管理クラスを通してセーブファイルに書き込む(SaveFile)

	〇読み込み
	１．データ管理クラスにセーブファイルを読み込む(LoadFile)
	２．データ管理クラスからセーブデータ変数を読み込む(GetSaveData)
*/

#include "..\BaseObject\IBaseObject.h"

class cDataManager : public IBaseObject
{
public:
	// 破棄
	IBaseObject* Finalize(void);

	// セーブデータ構造体
	// 保存対象の物をメンバに追加しておくこと
	struct SaveData
	{
		int Score;

	};

	// セーブデータの取得
	inline SaveData GetSaveData(void) { return m_SaveData; };
	// セーブデータの設定
	inline void		SetSaveData(SaveData data) { m_SaveData = data; };

	// ファイルへの保存
	// 事前にSetSaveDataで中身を保存し、m_SaveDataの中身をファイルへと保存する
	// filename : 書き込みファイル名
	void SaveFile(std::string filename);

	// ファイルの読み込み
	// ファイルからm_SaveDataへと読み込む
	// 読み込み後GetSaveDataで値を取得する
	// filename : 読み込みファイル名
	void LoadFile(std::string filename);
private:
	SaveData m_SaveData;		// セーブデータ構造体


	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cDataManager(void) { };     //  他からの生成を禁止
	cDataManager(IBaseObject* parent) {  };
	cDataManager(IBaseObject* parent, const std::string& name) { };
	~cDataManager(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cDataManager(const cDataManager& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cDataManager& operator = (const cDataManager& t) { return *this; };  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cDataManager& GetInstance(void) {
		static cDataManager instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};