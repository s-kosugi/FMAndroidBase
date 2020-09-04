#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleCursol.h												*/
/*  @brief		:	�^�C�g���J�[�\���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// �^�C�g���J�[�\���N���X
class cTitleCursol : public cSpriteObject
{
public:
	cTitleCursol(IBaseObject* parent);

	void Initialize(void);
	void Update(void);

	// �����ݒ�
	void Setup(const cVector2& pos, float angle);

private:

	cVector2 m_vOriginPos;

	// �\���D��x
	static const int	PRIORITY;
};
