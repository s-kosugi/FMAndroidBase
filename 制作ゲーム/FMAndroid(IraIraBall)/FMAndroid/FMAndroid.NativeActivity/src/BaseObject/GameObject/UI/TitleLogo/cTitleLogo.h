#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleLogo.h												*/
/*  @brief		:	�^�C�g�����S�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// �^�C�g�����S�N���X
class cTitleLogo : public cSpriteObject
{
public:
	cTitleLogo(IBaseObject* parent);
	~cTitleLogo(void);

	void Initialize(void) override;
	void Update(void) override;

private:

	enum STATE
	{
		SCALE,
		WAIT,
	};

	// ��ԕʏ���
	// �g�厞����
	void Scale(void);
	// �ҋ@����
	void Wait(void);


	// ���
	STATE m_eState;

	// �X�P�[�����O�psin�J�[�u
	float m_fScaleCurve;


	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;
	static const float  SCALE_INCREMENT;
	static const float  WAIT_TIME;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================