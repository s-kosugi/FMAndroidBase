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

class cEffectManager : public IBaseObject
{
public:
	// コンストラクタ
	cEffectManager(IBaseObject* pObj);
	~cEffectManager(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 生成
	IEffect* Create(EFFECT_ID id,const cVector2& pos);


	// レーザーエフェクトの削除
	void DeleteLaserEffect(void);

private:
};