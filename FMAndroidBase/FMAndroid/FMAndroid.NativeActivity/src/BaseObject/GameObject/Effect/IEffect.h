#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEffect.h													*/
/*  @brief		:	エフェクト基底クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// エフェクト基底クラス
class IEffect : public cSpriteObject
{
public:
	IEffect(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);

	// 初期化
	virtual void Initialize(void);
	virtual void Initialize(const cVector2& pos);

	virtual void Update(void);
	virtual IBaseObject* Finalize(void);

	inline POINT GetAnimeSize(void) { return m_ptSize; };
	inline short GetColumnNum(void) { return m_nColNum; };
	inline short GetRowNum(void) { return m_nMaxAnimNum / m_nColNum; };
	inline short GetMaxAnimNum(void) { return m_nMaxAnimNum; };
	inline short GetAnimNo(void) { return m_nAnimNo; };
	inline float GetFrameTime(void) { return m_fFrameTime; };

	void SetAnimNo(short animeNo);
	void SetFrameTime(float time);


	// アニメーションの設定
	void SetupAnime(const POINT& size, short col, short maxNum, float frameTime);

protected:
	POINT		m_ptSize;		// １アニメーション当たりの大きさ
	short		m_nColNum;		// 横列の枚数
	short		m_nMaxAnimNum;	// 最大アニメーション枚数
	short		m_nAnimNo;		// 現在のアニメーション番号
	float		m_fFrameTime;	// １フレーム当たりの時間

	// 現在のアニメーション番号にスプライトをあわせる
	void UpdateAnime(void);
};
//================================================================================================