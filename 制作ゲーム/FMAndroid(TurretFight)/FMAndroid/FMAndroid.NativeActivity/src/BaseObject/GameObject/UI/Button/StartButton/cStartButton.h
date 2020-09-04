#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartButton.h												*/
/*  @brief		:	�X�^�[�g�{�^���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/
#include "..\IButton.h"

// �X�^�[�g�{�^���N���X
class cStartButton : public IButton
{
public:
	cStartButton(IBaseObject* parent);

	void Initialize(void);

private:
	void Neutral(void);
	void Trigger(void);
	void Pressed(void);
	void Release(void);

	// �\���D��x
	static const int	PRIORITY;

	// ������Ă����Ԃ��痣�ꂽ��ԂɂȂ������̊m�F�t���O
	bool m_bPressed;
};
