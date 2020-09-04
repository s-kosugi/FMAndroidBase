#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleLogo.h												*/
/*  @brief		:	タイトルロゴクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// タイトルロゴクラス
class cTitleLogo : public cSpriteObject
{
public:
	cTitleLogo(IBaseObject* parent);
	~cTitleLogo(void);

	void Initialize(void) override;
	void Update(void) override;

private:

	enum STATE
	{
		SCALE,
		WAIT,
	};

	// 状態別処理
	// 拡大時処理
	void Scale(void);
	// 待機処理
	void Wait(void);


	// 状態
	STATE m_eState;

	// スケーリング用sinカーブ
	float m_fScaleCurve;


	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;
	static const float  SCALE_INCREMENT;
	static const float  WAIT_TIME;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================