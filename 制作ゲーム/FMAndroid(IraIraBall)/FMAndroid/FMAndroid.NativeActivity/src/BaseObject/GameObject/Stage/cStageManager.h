#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStageManager.h												*/
/*  @brief		:	�X�e�[�W�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "StageID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class IStage;

// �X�e�[�W�Ǘ��N���X
class cStageManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cStageManager(IBaseObject* pObj);
	~cStageManager(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �X�e�[�W����
	IStage* Create(STAGE_ID id, const cVector2& pos);

private:
	// �X�e�[�W�I�u�W�F�N�g�̃s�N�Z���T�C�Y
	static const int STAGE_PIXEL_SIZE;
};