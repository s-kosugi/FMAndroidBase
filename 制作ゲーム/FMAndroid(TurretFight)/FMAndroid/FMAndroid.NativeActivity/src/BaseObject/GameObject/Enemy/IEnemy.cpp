/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemy.cpp													*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "IEnemy.h"
#include "cGame.h"
#include "ScoreManager/cScoreManager.h"
#include "..\Effect\cEffectManager.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
// �萔
//==========================================================================================
const int  IEnemy::AREAOUT_ADJUST = 100; // �G���A�A�E�g����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
IEnemy::IEnemy(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name)
	, m_vPosUp(0.0f, 0.0f)
	, m_fDist(0.0f)
	, m_eState(STATE::NORMAL)
	, m_nHp(1)
	, m_nScore(1)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
IEnemy::~IEnemy(void)
{
}
//==========================================================================================
// ������
//==========================================================================================
void IEnemy::Initialize(void)
{
	Initialize({ 0.0f,0.0f });
}
//==========================================================================================
// ������
//==========================================================================================
void IEnemy::Initialize(const cVector2 & pos)
{
	m_vPos = pos;

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void IEnemy::Update(void)
{
	// ��ԕʏ���
	switch (m_eState)
	{
	case STATE::NORMAL:
		Normal();
		break;
	case STATE::DEAD:
		Dead();
		break;
	}

	// �ړ�����
	m_vPos += m_vPosUp;

	// �G���A�A�E�g������G���폜����
	AreaOutAllProc();

#ifdef DEBUG
	// �����蔻��̕`��
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* IEnemy::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//=================================================================
// �ʏ���
//=================================================================
void IEnemy::Normal(void)
{
}
//=================================================================
// ���S���
//=================================================================
void IEnemy::Dead(void)
{
	m_vPosUp = {0.0f,0.0f};
	int alpha = GetAlpha();
	alpha -= 8;
	if (alpha <= 0)
	{
		DeleteObject();
	}
	else
	{
		SetAlpha((unsigned int)alpha);
	}

}

//=================================================================
// ��ʊO�z�u����
//=================================================================
IEnemy::DIRECTION IEnemy::ArrangeOffScreen(void)
{
	DIRECTION direction = DIRECTION::LEFT;

	cGame* game = (cGame*)GetRoot();

	// ��ʒ[����o���悤�ɂ���ׂǂ̕�������o�����邩�������_���Ō��肷��
	switch (cGame::Random(0, 3))
	{
	case 0:
		// �����̏ꍇ
		m_vPos.x = -GetSpriteSize().x / 2.0f;
		direction = DIRECTION::LEFT;
		break;
	case 1:
		// �E���̏ꍇ
		m_vPos.x = game->GetWindowWidth() + GetSpriteSize().x;
		direction = DIRECTION::RIGHT;
		break;
	case 2:
		// �㑤�̏ꍇ
		m_vPos.y = -GetSpriteSize().y / 2.0f;
		direction = DIRECTION::TOP;
		break;
	case 3:
		// �����̏ꍇ
		m_vPos.y = game->GetWindowHeight() + GetSpriteSize().y;
		direction = DIRECTION::BOTTOM;
		break;
	}
	return direction;
}

//==========================================================================================
// �v���C���[�֌������ړ��ʂ�ݒ肷��
// speed : ��{�ړ���
//==========================================================================================
void IEnemy::GotoPlayer(float speed)
{
	// �v���C���[�Ɍ������Ĉړ�
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		cVector2 pcPos = pc->GetPos();
		float angle = m_vPos.CalcTwoPointAngle(pcPos);

		// �ړ��ʂ�����
		m_vPosUp.x = cos(DEG_TO_RAD(angle)) * speed;
		m_vPosUp.y = sin(DEG_TO_RAD(angle)) * speed;
	}
}

//==========================================================================================
// �_���[�W����
//==========================================================================================
void IEnemy::Damage(void)
{
	m_nHp--;
	if (m_nHp <= 0)
	{
		m_eState = STATE::DEAD;
		m_vPosUp.x = m_vPosUp.y = 0.0f;

		// ���_����
		cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
		sm->AddScore(m_nScore);

		// �G�t�F�N�g�Đ�
		cEffectManager* ef = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		ef->Create(EFFECT_ID::BOM,m_vPos);
	}
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IEnemy::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ��G���A�A�E�g����
//==========================================================================================
void IEnemy::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �E�G���A�A�E�g����
//==========================================================================================
void IEnemy::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// ���G���A�A�E�g����
//==========================================================================================
void IEnemy::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// �S�����G���A�A�E�g����
//==========================================================================================
void IEnemy::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}