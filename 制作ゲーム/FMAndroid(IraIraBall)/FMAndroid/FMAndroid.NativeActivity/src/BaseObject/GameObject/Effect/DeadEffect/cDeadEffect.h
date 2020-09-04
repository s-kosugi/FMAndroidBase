#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDeadEffect.h												*/
/*  @brief		:	���S�G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/26													*/
/*																				*/
/*==============================================================================*/

#include "..\IEffect.h"

//================================================================================================
// ���S�G�t�F�N�g�N���X
class cDeadEffect : public IEffect
{
public:
	cDeadEffect(IBaseObject* parent);

	// ������
	void Initialize(const cVector2& pos) override;
	// �X�V
	void Update(void) override;


	// �ړ��ݒ�
	// angle : degree�l�̊p�x  power : �ړ���
	void SetMove(float angle, float power);
private:
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	//--------------------------------------------------------------------------------------------
	cVector2 m_vVelocity;		// �ړ���

};
//================================================================================================