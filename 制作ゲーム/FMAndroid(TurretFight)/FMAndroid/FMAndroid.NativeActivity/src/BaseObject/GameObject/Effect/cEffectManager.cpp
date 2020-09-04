/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.cpp											*/
/*  @brief		:	エフェクト管理クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "cEffectManager.h"
#include "BomEffect/cBomEffect.h"
#include "MuzzleFlashEffect/cMuzzleFlashEffect.h"
#include "LaserEffect/cLaserEffect.h"
#include "LaserStartEffect/cLaserStartEffect.h"

//==========================================================================================
// 定数
//==========================================================================================

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEffectManager::cEffectManager(IBaseObject* pObj)
	:IBaseObject(pObj, "EffectManager")
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cEffectManager::~cEffectManager(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEffectManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEffectManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cEffectManager::Finalize(void)
{
	return IBaseObject::Finalize();
}

//==========================================================================================
// 生成
//==========================================================================================
IEffect* cEffectManager::Create(EFFECT_ID id,const cVector2& pos)
{
	IEffect* obj = nullptr;
	switch (id)
	{
	case EFFECT_ID::BOM: obj = CreateObject<cBomEffect>(this); break;
	case EFFECT_ID::MUZZLE: obj = CreateObject<cMuzzleFlashEffect>(this); break;
	case EFFECT_ID::LASER: obj = CreateObject<cLaserEffect>(this); break;
	case EFFECT_ID::LASER_START: obj = CreateObject<cLaserStartEffect>(this); break;
	default: break;
	}

	if (obj != nullptr)
	{
		obj->Initialize(pos);
	}
	return obj;
}

//==========================================================================================
// レーザーエフェクトの削除
//==========================================================================================
void cEffectManager::DeleteLaserEffect(void)
{
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); it++)
	{
		if ((*it)->GetObjectName() == "LaserEffect" || (*it)->GetObjectName() == "LaserStartEffect")
		{
			(*it)->DeleteObject();
		}
	}
}
