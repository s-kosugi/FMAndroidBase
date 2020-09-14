#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartButton.h												*/
/*  @brief		:	�X�^�[�g�{�^���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/
#include "..\IButton.h"

// �X�^�[�g�{�^���N���X
class cStartButton : public IButton
{
public:
	cStartButton(IBaseObject* parent);

	void Initialize(void) override;

private:
	void Neutral(void) override;
	void Trigger(void) override;
	void Pressed(void) override;
	void Release(void) override;

	// �\���D��x
	static const int	PRIORITY;

	// ������Ă����Ԃ��痣�ꂽ��ԂɂȂ������̊m�F�t���O
	bool m_bPressed;
};
