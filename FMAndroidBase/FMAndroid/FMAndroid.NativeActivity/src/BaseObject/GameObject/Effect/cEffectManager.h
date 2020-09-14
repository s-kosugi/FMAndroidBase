#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	エフェクト管理クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EffectID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

class IEffect;

// エフェクト管理クラス
class cEffectManager : public IBaseObject
{
public:
	// コンストラクタ
	cEffectManager(IBaseObject* pObj);
	~cEffectManager(void);

	// 初期化
	void Initialize(void) override;

	// 更新
	void Update(void) override;

	// 破棄
	IBaseObject* Finalize(void) override;

	// 生成
	IEffect* Create(EFFECT_ID id,const cVector2& pos);

private:
};