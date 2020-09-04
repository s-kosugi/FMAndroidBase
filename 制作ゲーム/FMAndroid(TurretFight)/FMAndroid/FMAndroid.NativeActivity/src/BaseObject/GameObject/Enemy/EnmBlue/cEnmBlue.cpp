/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlue.cpp												*/
/*  @brief		:	���G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cEnmBlue.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cEnmBlue::PRIORITY = 300;
const float cEnmBlue::ROTATE_SPEED = 6.0f;
const int   cEnmBlue::BASE_DIST = 100;
const int   cEnmBlue::MIN_TIME = 8;
const int   cEnmBlue::MAX_TIME = 15;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnmBlue::cEnmBlue(IBaseObject * parent)
	: IEnemy(parent, "EnmBlue", "data\\graphic\\enemy_02.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnmBlue::~cEnmBlue(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnmBlue::Initialize(const cVector2 & pos)
{
	SetPriority(PRIORITY);
	// �����蔻���ݒ�
	m_fDist = GetSpriteSize().x / 2.0f;

	// �ʒu��ݒ肷��
	m_vPos = pos;

	SetAngle((float)cGame::Random(0,359));

	IEnemy::Initialize(m_vPos);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnmBlue::Update(void)
{
	// ���]����
	SetAngle(GetAngle() + ROTATE_SPEED);

	IEnemy::Update();
}
//==========================================================================================
// �ʏ���
//==========================================================================================
void cEnmBlue::Normal(void)
{
	// ���@�ڋ߃^�C�}�[
	cTimer* timer = (cTimer*)FindChild("DistTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "DistTimer");
		timer->Setup((float)cGame::Random(MIN_TIME, MAX_TIME));
	}
	// �v���C���[�Ɍ������Ĉړ�
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		m_vPos.x = cos(DEG_TO_RAD(GetAngle()*0.1f)) * BASE_DIST * (timer->GetLimit() - timer->GetTime()) + pc->GetPos().x;
		m_vPos.y = sin(DEG_TO_RAD(GetAngle()*0.1f)) * BASE_DIST * (timer->GetLimit() - timer->GetTime()) + pc->GetPos().y;
	}
}
//==========================================================================================
// �͈͊O����
//==========================================================================================
void cEnmBlue::AreaOutAllProc(void)
{
	// �I�[�o�[���C�h���ĉ����������Ȃ�
}
