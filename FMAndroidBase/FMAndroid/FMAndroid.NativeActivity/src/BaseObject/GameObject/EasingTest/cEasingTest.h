#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEasingTest.h												*/
/*  @brief		:	�C�[�W���O�֐��e�X�g�I�u�W�F�N�g�N���X						*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/18													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"
#include "..\..\..\Utility\Easing\Easing.h"

//================================================================================================
// �C�[�W���O�֐��e�X�g�I�u�W�F�N�g�N���X
class cEasingTest : public cSpriteObject
{
public:
	cEasingTest(IBaseObject* parent);
	~cEasingTest(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void SetEasingType(Easing::Type type);

private:
	// �\���D��x
	static const int	PRIORITY = 100;
	static const float	GOAL_POS;

	Easing::Type		m_eEasingType;
	double				m_dTotalTimer;
	double				m_dStartTimer;
};
//================================================================================================