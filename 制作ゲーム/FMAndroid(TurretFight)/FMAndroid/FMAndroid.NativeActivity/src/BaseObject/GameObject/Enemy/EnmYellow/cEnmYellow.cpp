/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmYellow.cpp												*/
/*  @brief		:	���F���G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cEnmYellow.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cEnmYellow::PRIORITY = 300;
const float cEnmYellow::BASE_SPEED = 1.0f;
const float cEnmYellow::ROTATE_SPEED = 4.0f;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnmYellow::cEnmYellow(IBaseObject * parent)
	: IEnemy(parent, "EnmYellow", "data\\graphic\\enemy_03.png")
	, m_ePopDirection( DIRECTION::LEFT)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnmYellow::~cEnmYellow(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnmYellow::Initialize(const cVector2 & pos)
{
	SetPriority(PRIORITY);
	// �����蔻���ݒ�
	m_fDist = GetSpriteSize().x / 2.0f;

	// �ʒu��ݒ肷��
	m_vPos = pos;

	// ��ʊO�z�u����
	m_ePopDirection = ArrangeOffScreen();

	SetAngle((float)cGame::Random(0, 359));

	IEnemy::Initialize(m_vPos);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnmYellow::Update(void)
{
	// ���]����
	SetAngle(GetAngle() + ROTATE_SPEED);

	if (m_eState == STATE::NORMAL)
	{
		cGame* game = (cGame*)GetRoot();

		switch (m_ePopDirection)
		{
		case DIRECTION::LEFT:
			m_vPosUp.x = BASE_SPEED;
			m_vPos.y = cos(DEG_TO_RAD(GetAngle()*0.5f)) * game->GetWindowCenter().y + game->GetWindowCenter().y;
			break;
		case DIRECTION::RIGHT:
			m_vPosUp.x = -BASE_SPEED;
			m_vPos.y = cos(DEG_TO_RAD(GetAngle()*0.5f)) * game->GetWindowCenter().y + game->GetWindowCenter().y;
			break;
		case DIRECTION::TOP:
			m_vPosUp.y = BASE_SPEED;
			m_vPos.x = cos(DEG_TO_RAD(GetAngle()*0.5f)) * game->GetWindowCenter().x + game->GetWindowCenter().x;
			break;
		case DIRECTION::BOTTOM:
			m_vPosUp.y = -BASE_SPEED;
			m_vPos.x = cos(DEG_TO_RAD(GetAngle()*0.5f)) * game->GetWindowCenter().x + game->GetWindowCenter().x;
			break;
		}
	}

	IEnemy::Update();
}