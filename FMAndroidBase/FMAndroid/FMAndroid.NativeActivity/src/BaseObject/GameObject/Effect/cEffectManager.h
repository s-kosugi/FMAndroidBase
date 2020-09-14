#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	�G�t�F�N�g�Ǘ��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EffectID.h"
#include "..\..\..\Utility\Vector\cVector2.h"

class IEffect;

// �G�t�F�N�g�Ǘ��N���X
class cEffectManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cEffectManager(IBaseObject* pObj);
	~cEffectManager(void);

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �j��
	IBaseObject* Finalize(void) override;

	// ����
	IEffect* Create(EFFECT_ID id,const cVector2& pos);

private:
};