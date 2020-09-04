#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cLaserStartEffect.h											*/
/*  @brief		:	レーザー始点エフェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEffect.h"

//================================================================================================
// レーザー始点エフェクトクラス
class cLaserStartEffect : public IEffect
{
public:
	cLaserStartEffect(IBaseObject* parent);

	// 初期化
	void Initialize(const cVector2& pos);

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================