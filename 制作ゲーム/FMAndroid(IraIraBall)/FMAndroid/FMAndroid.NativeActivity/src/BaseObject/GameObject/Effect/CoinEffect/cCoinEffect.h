#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cCoinEffect.h												*/
/*  @brief		:	�R�C���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IEffect.h"

//================================================================================================
// �R�C���G�t�F�N�g�N���X
class cCoinEffect : public IEffect
{
public:
	cCoinEffect(IBaseObject* parent);

	// ������
	void Initialize(const cVector2& pos) override;
	// �X�V
	void Update(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// �ő呬�x
	static const float  MAX_SPEED;

	//--------------------------------------------------------------------------------------------
	cVector2 m_vVelocity;		// �ړ���
	float    m_fScaleCurve;		// �X�P�[�����O�psin�J�[�u�l

};
//================================================================================================