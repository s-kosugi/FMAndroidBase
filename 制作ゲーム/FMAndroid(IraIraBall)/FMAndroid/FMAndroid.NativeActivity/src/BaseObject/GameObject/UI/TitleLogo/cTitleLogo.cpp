/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleLogo.cpp												*/
/*  @brief		:	�^�C�g�����S�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "cTitleLogo.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cTitleLogo::PRIORITY = 1000;
const float cTitleLogo::SCALE_INCREMENT = 7.5f;
const float cTitleLogo::WAIT_TIME = 1.0f;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cTitleLogo::cTitleLogo(IBaseObject* parent)
	: cSpriteObject(parent, "TitleLogo", "data\\graphic\\TitleLogo.png")
	, m_eState( STATE::SCALE)
	, m_fScaleCurve( 0.0f )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cTitleLogo::~cTitleLogo(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cTitleLogo::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();

	// �����ɔz�u
	SetPos(game->GetWindowCenter());

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cTitleLogo::Update(void)
{
	switch (m_eState)
	{
	case STATE::SCALE: Scale(); break;
	case STATE::WAIT: Wait(); break;
	default: break;
	}

	cSpriteObject::Update();
}

//==========================================================================================
// �g�厞����
//==========================================================================================
void cTitleLogo::Scale(void)
{
	m_fScaleCurve += SCALE_INCREMENT;

	float scale = sin(DEG_TO_RAD(m_fScaleCurve)) * 0.5f + 1.0f;
	if (scale <= 1.0f)
	{
		scale = 1.0f;
		m_eState = STATE::WAIT;

		// sin�J�[�u�Ɏg���l�����Z�b�g
		m_fScaleCurve = 0.0f;
	}
	SetScale(scale);
}
//==========================================================================================
// �ҋ@����
//==========================================================================================
void cTitleLogo::Wait(void)
{
	cTimer* timer = (cTimer*)FindChild("TitleWaitTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this,"TitleWaitTimer");
		timer->Setup(WAIT_TIME);
	}
	if (timer->Finished())
	{
		timer->DeleteObject();
		m_eState = STATE::SCALE;
	}
}
