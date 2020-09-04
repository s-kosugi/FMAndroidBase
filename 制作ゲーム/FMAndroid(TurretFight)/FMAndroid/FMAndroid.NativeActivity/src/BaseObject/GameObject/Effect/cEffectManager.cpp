/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.cpp											*/
/*  @brief		:	�G�t�F�N�g�Ǘ��N���X										*/
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
// �萔
//==========================================================================================

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEffectManager::cEffectManager(IBaseObject* pObj)
	:IBaseObject(pObj, "EffectManager")
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEffectManager::~cEffectManager(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEffectManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEffectManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEffectManager::Finalize(void)
{
	return IBaseObject::Finalize();
}

//==========================================================================================
// ����
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
// ���[�U�[�G�t�F�N�g�̍폜
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
