/*==============================================================================*/
/*																				*/
/*	@file title	:	IBullet.cpp													*/
/*  @brief		:	�e�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "IBullet.h"
#include "cGame.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
// �萔
//==========================================================================================
const int  IBullet::AREAOUT_ADJUST = 100; // �G���A�A�E�g����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
IBullet::IBullet(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name)
	,m_vPosUp(0.0f, 0.0f)
	,m_fDist(0.0f)
	,m_bInvincible( false )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
IBullet::~IBullet(void)
{
}
//==========================================================================================
// ������
//==========================================================================================
void IBullet::Initialize(void)
{
	Initialize({ 0.0f,0.0f }, 0.0f, 1.0f);
}
//==========================================================================================
// ������
//==========================================================================================
void IBullet::Initialize(const cVector2 & pos)
{
	Initialize(pos, 0.0f, 1.0f);
}

//==========================================================================================
// ������
//==========================================================================================
void IBullet::Initialize(const cVector2& pos, float angle, float speed)
{
	// �e�̈ړ���
	m_vPosUp.x = cos(DEG_TO_RAD(angle)) * speed;
	m_vPosUp.y = sin(DEG_TO_RAD(angle)) * speed;

	// �e�̉�]
	m_fAngle = angle;

	m_vPos = pos;

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void IBullet::Update(void)
{
	
	// �ړ�����
	m_vPos += m_vPosUp;

	// �G���A�A�E�g������e���폜����
	AreaOutAllProc();

	// �G�Ƃ̓����蔻�菈��������
	CheckHitEnemy();

#ifdef DEBUG
	// �����蔻��̕`��
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos,m_fDist,0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* IBullet::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// �����蔻�菈��
//==========================================================================================
void IBullet::CheckHitEnemy(void)
{
	cEnemyManager* em = (cEnemyManager*)GetParent()->FindSibling("EnemyManager");

	if (em)
	{
		// ����������e������
		if (em->CheckHit(m_vPos, m_fDist))
		{
			// ���G�t���O
			if (!m_bInvincible) DeleteObject();
		}
	}
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IBullet::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ��G���A�A�E�g����
//==========================================================================================
void IBullet::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �E�G���A�A�E�g����
//==========================================================================================
void IBullet::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IBullet::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �S�����G���A�A�E�g����
//==========================================================================================
void IBullet::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}