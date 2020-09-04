/*==============================================================================*/
/*																				*/
/*	@file title	:	cCsvReader.cpp												*/
/*  @brief		:	CSV読み込みクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/08													*/
/*																				*/
/*==============================================================================*/

#include "cCsvReader.h"
#include <DxLib.h>
#include <sstream>

// 定数
const int cCsvReader::LINE_CHAR_MAX = 256;		// １行当たりの最大文字数

//==========================================================================================
// 初期化
//==========================================================================================
void cCsvReader::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "CsvReader";

	IBaseObject::Initialize();
}
//==========================================================================================
// ファイル読み込み
// fiepath : 読み込むファイルのパス
// buf : 読み込んだファイルが文字列配列として入る
// return : 読み込んだ行数を返す
//==========================================================================================
int cCsvReader::LoadFile(const std::string filepath, std::vector<std::string>& buf)
{
	int handle = FileRead_open(filepath.c_str());

	// エラー
	if (handle == 0)
	{
		ErrorLogAdd("FileLoadError! FileHandle is None\n");
		return 0;
	}
	// １行ごとのデータを格納しておく
	char line[LINE_CHAR_MAX];
	int linecount = 0;
	// ファイル終端まで１行ずつ読み込む
	while (FileRead_gets(line, LINE_CHAR_MAX, handle) != -1)
	{
		if (SplitCsv(line, buf)) {
			// 読み込み行の中に項目があればカウントする
			linecount++;
		}
	}

	FileRead_close(handle);

	return linecount;
}
//==========================================================================================
// １行単位の文字列を項目毎に分割する
// str : 行単位での文字列
// buf : 読み込んだ文字を格納するバッファ
// ret : 読み込み項目数を返す
//==========================================================================================
int cCsvReader::SplitCsv(const std::string & str, std::vector<std::string>& buf)
{
	// 文字列ストリーム
	std::istringstream iss(str);

	std::string readStr;

	// 項目数カウント
	int itemcount = 0;

	// ,毎にgetlineで文字列を読み込み
	while (std::getline(iss, readStr, ',')) {
		buf.push_back(readStr);
		itemcount++;
	}

	return itemcount;
}
