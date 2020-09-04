#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IStage.h													*/
/*  @brief		:	�X�e�[�W�x�[�X�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �X�e�[�W�x�[�X�N���X
class IStage : public cSpriteObject
{
public:
	IStage(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IStage(void);

	// ������
	void Initialize(void);
	// ������
	// pos   : �����ʒu
	void Initialize(const cVector2& pos);
	void Update(void);
	IBaseObject* Finalize(void);

	// �����蔻��̔��a�̎擾
	const inline float GetDist(void) { return m_fDist; };

protected:
	// �v���C���[�ƏՓ˂������ǂ����̃`�F�b�N
	void CheckPlayerHit(void);

	// �v���C���[�Փˎ��̏���
	virtual void HitPlayer(void);

	// �����蔻��̔��a
	float m_fDist;
};
//================================================================================================