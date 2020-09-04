/*==============================================================================*/
/*																				*/
/*	@file title	:	cDataManager.cpp											*/
/*  @brief		:	データ管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/01/27													*/
/*																				*/
/*==============================================================================*/

#include "cDataManager.h"
#include <DxLib.h>


//==========================================================================================
// 定数

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cDataManager::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}
//==========================================================================================
// データの保存
//==========================================================================================
void cDataManager::SaveFile(std::string filename)
{
	FILE* fp;
	char FilePath[256];

	// GetExternalDataPathでデータセーブ用のフォルダーパスを取得
	GetExternalDataPath(FilePath, sizeof(FilePath));
	strcat(FilePath,"/");

	// セーブファイルパスを文字の後ろに付ける
	strcat(FilePath,filename.c_str());

	// ファイルを書き込み新規作成で開く
	fp = fopen(FilePath,"wb");

	if (fp != NULL)
	{
		// データを書き込み
		fwrite(&m_SaveData, sizeof(m_SaveData), 1, fp);

		fclose(fp);
	}
}
//==========================================================================================
// データの読み込み
//==========================================================================================
void cDataManager::LoadFile(std::string filename)
{
	FILE* fp;
	char FilePath[256];

	// GetExternalDataPathでデータセーブ用のフォルダーパスを取得
	GetExternalDataPath(FilePath, sizeof(FilePath));
	strcat(FilePath, "/");

	// セーブファイルパスを文字の後ろに付ける
	strcat(FilePath, filename.c_str());

	// ファイルを読み込み新規作成で開く
	fp = fopen(FilePath, "rb");

	if (fp != NULL)
	{
		// データを読み込み
		fread(&m_SaveData, sizeof(m_SaveData), 1, fp);

		fclose(fp);
	}
}
