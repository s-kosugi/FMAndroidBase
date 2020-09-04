/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRed.cpp													*/
/*  @brief		:	�Ԃ��G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cEnmRed.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cEnmRed::PRIORITY = 300;
const float cEnmRed::BASE_SPEED = 2.5f;
const float cEnmRed::ROTATE_SPEED = 8.0f;
const float cEnmRed::STOP_DIST = 400.0f;
const float cEnmRed::STOP_TIME = 3.0f;
const float cEnmRed::RESTART_TIME = 2.0f;
const float cEnmRed::RESTART_MAX_SPEED = 10.0f;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnmRed::cEnmRed(IBaseObject * parent)
	: IEnemy(parent, "EnmRed", "data\\graphic\\enemy_04.png")
	, m_eActionState( ACTION_STATE::START )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnmRed::~cEnmRed(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnmRed::Initialize(const cVector2 & pos)
{

	SetPriority(PRIORITY);
	// �����蔻���ݒ�
	m_fDist = GetSpriteSize().x / 2.0f;

	// �ʒu��ݒ肷��
	m_vPos = pos;

	// ��ʊO�z�u����
	ArrangeOffScreen();

	// ���݈ʒu����v���C���[�Ɍ������Ĉړ�������
	GotoPlayer(BASE_SPEED);

	IEnemy::Initialize(m_vPos);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnmRed::Update(void)
{
	// ���]����
	SetAngle(GetAngle() + ROTATE_SPEED);

	switch (m_eActionState)
	{
	case ACTION_STATE::START: Start(); break;
	case ACTION_STATE::STOP: Stop(); break;
	case ACTION_STATE::RESTART: Restart(); break;
	}


	IEnemy::Update();
}

//==========================================================================================
// �J�n���
//==========================================================================================
void cEnmRed::Start(void)
{
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		// ��~�����ɂȂ������Ԃ�ύX����
		if (pc->GetPos().CalcTwoPointDist(m_vPos) < STOP_DIST)
		{
			m_eActionState = ACTION_STATE::STOP;
		}
	}
}

//==========================================================================================
// ��~���
//==========================================================================================
void cEnmRed::Stop(void)
{
	cTimer* timer = (cTimer*)FindChild("StopTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "StopTimer");
		timer->Setup(STOP_TIME);
	}
	GotoPlayer(Easing::OutSine(timer->GetTime(), timer->GetLimit(), 0.0f, BASE_SPEED));

	if (timer->Finished())
	{
		m_eActionState = ACTION_STATE::RESTART;
		timer->DeleteObject();
	}
}

//==========================================================================================
// �Ďn�����
//==========================================================================================
void cEnmRed::Restart(void)
{
	cTimer* timer = (cTimer*)FindChild("RestartTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "RestartTimer");
		timer->Setup(RESTART_TIME);
	}
	
	// ���Ԃŉ�������
	if (!timer->Finished())
	{
		GotoPlayer(Easing::InSine(timer->GetTime(),timer->GetLimit(), RESTART_MAX_SPEED,0.0f));
	}

}
