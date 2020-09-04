/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "Input\Touch\cTouch.h"
#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "BaseObject/GameObject/Bullet/cBulletManager.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/Effect/IEffect.h"
#include "SceneManager/cSceneManager.h"
#include "Utility/Timer/cTimer.h"
#ifdef DEBUG
#include "..\..\..\DebugFunc\cDebugFunc.h"
#include <sstream>
#endif // DEBUG

//==========================================================================================
// �萔
//==========================================================================================
const float cPlayer::NORMAL_BUL_SPD = 10.0f;
const float cPlayer::NORMAL_BUL_INTERVAL = 0.2f;
const float cPlayer::BUL_FIRE_POS = 80.0f;
const int cPlayer::PRIORITY = 200;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cPlayer::cPlayer(IBaseObject * parent)
	: cSpriteObject(parent, "Player", "data\\graphic\\Turret.png")
	, m_fDist( 1.0f )
	, m_eState(STATE::NORMAL)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cPlayer::~cPlayer(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cPlayer::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();

	m_vPos = { game->GetWindowCenter().x,game->GetWindowCenter().y };
	SetPriority(PRIORITY);
	// �����蔻��̐ݒ�
	m_fDist = GetSpriteSize().x / 3.0f;

	// �e���ˊԊu�^�C�}�[�̐���
	cTimer* timer = CreateObject<cTimer>(this,"BulletTimer");
	timer->Setup(NORMAL_BUL_INTERVAL);

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cPlayer::Update(void)
{
	switch (m_eState)
	{
	case STATE::NORMAL: Normal(); break;
	case STATE::LASER: Laser(); break;
	case STATE::DEAD: Dead(); break;
	default: break;
	}

	cSpriteObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cPlayer::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// �ʏ���
//==========================================================================================
void cPlayer::Normal(void)
{
	cTouch* touch = (cTouch*)GetRoot()->FindChild("Touch");
	cTimer* bulTimer = (cTimer*)FindChild("BulletTimer");
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	POINT pt;

	// �^�b�`���W���擾
	if (touch->GetTouchPos(0, pt))
	{
		// ���@�̉�]
		cVector2 vec(pt);
		m_fAngle = m_vPos.CalcTwoPointAngle(vec);

		// �e�̔��ˊԊu���߂��Ă����甭�˂���
		if (bulTimer && bulTimer->Finished())
		{
			bulTimer->Reset();

			cBulletManager* bm = (cBulletManager*)FindSibling("BulletManager");
			// ���ˈʒu�̒���
			cVector2 firePos;
			firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
			firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;

			bm->Create(BULLET_ID::NORMAL, firePos, m_fAngle, NORMAL_BUL_SPD);

			// �G�t�F�N�g�̐���
			cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			IEffect* effect = em->Create(EFFECT_ID::MUZZLE, firePos);
			effect->SetAngle(m_fAngle - 90.0f);

			// �����̍Đ�
			if (sc) sc->Play(SOUND_ID::SHOT);
		}
	}
	// �Q�_�^�b�`�������ꂽ�烌�[�U�[��Ԃɂ���
	if (touch->GetTouchPos(1, pt))
	{
		StartLaser();
	}

	// �G�Ƃ̓����蔻�菈��
	CheckHitEnemy();
#ifdef DEBUG
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif
}

//==========================================================================================
// ���[�U�[���ˏ��
//==========================================================================================
void cPlayer::Laser(void)
{
	cTimer* timer = (cTimer*)FindChild("LaserTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "LaserTimer");
		timer->Setup(3.0f);
	}
	// �^�C�}�[���I������̂Œʏ��Ԃɖ߂�
	if (timer->Finished())
	{
		m_eState = STATE::NORMAL;
		timer->DeleteObject();

		// ���[�U�[�G�t�F�N�g���폜����
		cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		if (em) em->DeleteLaserEffect();
	}

	// �G�Ƃ̓����蔻�菈��
	CheckHitEnemy();
#ifdef DEBUG
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif
}

//==========================================================================================
// ���S���
//==========================================================================================
void cPlayer::Dead(void)
{
	cTimer* timer = (cTimer*)FindChild("DeadTimer");

	// ���[�U�[�G�t�F�N�g���폜����
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (em) em->DeleteLaserEffect();

	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "DeadTimer");
		timer->Setup(2.0f);
	}

	// ���S�^�C�}�[���o�߂�����V�[���`�F���W
	if (timer->Finished())
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		sm->ChangeSceneUniTrans(SCENE_ID::RESULT, "data\\graphic\\rule_00.png");
	}

}

//==========================================================================================
// ���[�U�[�J�n����
//==========================================================================================
void cPlayer::StartLaser(void)
{
	cGame* game = (cGame*)GetRoot();
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");

	// ���@�����[�U�[���ˏ�Ԃɂ���
	m_eState = STATE::LASER;

	// �����̍Đ�
	if (sc) sc->Play(SOUND_ID::LASER);

	// ���ˈʒu�̒���
	cVector2 firePos;

	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
	firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
	// ���[�U�[�n�_�G�t�F�N�g�̍쐬
	IEffect* effect = em->Create(EFFECT_ID::LASER_START, firePos);
	effect->SetAngle(m_fAngle);
	effect->SetLoop(true);
	// ���[�U�[�{�̃G�t�F�N�g�̍쐬
	for (int i = 1;; i++)
	{
		firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS + cos(DEG_TO_RAD(m_fAngle)) * i * 128;
		firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS + sin(DEG_TO_RAD(m_fAngle)) * i * 128;

		// ���[�U�[�̒e�̔���
		cBulletManager* bm = (cBulletManager*)FindSibling("BulletManager");
		bm->Create(BULLET_ID::LASER,firePos,m_fAngle,0.0f);

		effect = em->Create(EFFECT_ID::LASER, firePos);
		effect->SetAngle(m_fAngle);
		// ���[�U�[�̓��[�v�G�t�F�N�g
		effect->SetLoop(true);

		if (firePos.x + 128 < 0.0f ||
			firePos.x - 128 > game->GetWindowWidth() ||
			firePos.y + 128 < 0.0f ||
			firePos.y - 128 > game->GetWindowHeight())
		{
			// �͈͊O�ɏo���琶������߂�
			break;
		}
	}
}

//==========================================================================================
// �����蔻�菈��
//==========================================================================================
void cPlayer::CheckHitEnemy(void)
{
	cEnemyManager* em = (cEnemyManager*)GetParent()->FindSibling("EnemyManager");

	if (em)
	{
		// ���������玀�S����
		if (em->CheckHit(m_vPos, m_fDist))
		{
			m_eState = STATE::DEAD;

			m_bVisible = false;
			// �G�t�F�N�g�Đ�
			cEffectManager* ef = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			ef->Create(EFFECT_ID::BOM, m_vPos);
		}
	}
}