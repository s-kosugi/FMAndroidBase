#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCoinEffect.h												*/
/*  @brief		:	コインエフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IEffect.h"

//================================================================================================
// コインエフェクトクラス
class cCoinEffect : public IEffect
{
public:
	cCoinEffect(IBaseObject* parent);

	// 初期化
	void Initialize(const cVector2& pos) override;
	// 更新
	void Update(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 最大速度
	static const float  MAX_SPEED;

	//--------------------------------------------------------------------------------------------
	cVector2 m_vVelocity;		// 移動量
	float    m_fScaleCurve;		// スケーリング用sinカーブ値

};
//================================================================================================