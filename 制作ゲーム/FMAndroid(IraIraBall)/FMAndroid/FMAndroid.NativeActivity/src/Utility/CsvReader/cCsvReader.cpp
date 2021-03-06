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

//==========================================================================================
// 定数
//==========================================================================================
const int cCsvReader::LINE_CHAR_MAX = 1024;		// １行当たりの最大文字数

//==========================================================================================
// コンストラクタ
//==========================================================================================
cCsvReader::cCsvReader(IBaseObject * parent) 
	: IBaseObject(parent,"CsvReader")
	, m_RowNum( 0 )
{
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cCsvReader::~cCsvReader()
{
}
//==========================================================================================
// ファイル読み込み
// fiepath : 読み込むファイルのパス
//==========================================================================================
void cCsvReader::LoadFile(const std::string filepath)
{
	int handle = FileRead_open(filepath.c_str());

	// エラー
	if (handle == 0)
	{
		ErrorLogAdd("FileLoadError! FileHandle is None\n");
		return;
	}
	// 読み込むのでバッファをクリア
	m_Buffer.clear();
	m_RowNum = 0;

	// １行ごとのデータを格納しておく
	char line[LINE_CHAR_MAX];
	// ファイル終端まで１行ずつ読み込む
	while (FileRead_gets(line, LINE_CHAR_MAX, handle) != -1)
	{
		// 文字列ストリーム
		std::istringstream iss(line);
		std::string readStr;
		bool readFlg = false;
		// ,毎にgetlineで文字列を読み込み
		while (std::getline(iss, readStr, ',')) {
			m_Buffer.push_back(readStr);
			readFlg = true;
		}
		// 読み込み行の中に項目があれば行数カウントする
		if (readFlg) m_RowNum++;
	}

	FileRead_close(handle);
}
//==========================================================================================
// 指定されたデータを文字列で取得
//==========================================================================================
const std::string cCsvReader::GetString(int row, int col)
{
	return m_Buffer[row * GetColNum() + col];
}
//==========================================================================================
// 指定されたデータを整数で取得
//==========================================================================================
const int cCsvReader::GetInt(int row, int col)
{
	// 文字列を整数に変換
	std::istringstream iss(m_Buffer[row * GetColNum() + col]);
	int ret = 0;
	iss >> ret;

	return ret;
}
//==========================================================================================
// 指定されたデータを小数で取得
//==========================================================================================
const float cCsvReader::GetFloat(int row, int col)
{
	// 文字列を整数に変換
	std::istringstream iss(m_Buffer[row * GetColNum() + col]);
	float ret = 0;
	iss >> ret;

	return ret;
}

//==========================================================================================
// 列数の取得
//==========================================================================================
const int cCsvReader::GetRowNum(void)
{
	return m_RowNum;
}

//==========================================================================================
// 行数の取得
//==========================================================================================
const int cCsvReader::GetColNum(void)
{
	return m_Buffer.size() / m_RowNum;
}

//==========================================================================================
// 項目数の取得
//==========================================================================================
const int cCsvReader::GetDataNum(void)
{
	return m_Buffer.size();
}
