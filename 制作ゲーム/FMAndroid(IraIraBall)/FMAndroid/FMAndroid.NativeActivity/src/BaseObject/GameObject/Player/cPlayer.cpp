/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/18													*/
/*																				*/
/*==============================================================================*/
#include "cPlayer.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/Effect/DeadEffect/cDeadEffect.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==================================================================================
// �萔
//==================================================================================
const float cPlayer::REFLECTION = 0.7f;				// ���ˌ�����
const float cPlayer::FRICTION = 0.96f;				// ���C��
const float cPlayer::SLOPE_MIN_ROUNDDOWN = 0.45f;	// �ŏ��X���l
const float cPlayer::SENSOR_RATE = 0.05f;			// �Z���T�[������
const float cPlayer::DIST = 20.0f;					// �����蔻��̔��a
const float cPlayer::DEAD_TIME = 2.0f;				// ���S��Ԃ̎���
const float cPlayer::GOAL_TIME = 2.0f;				// �S�[����Ԃ̎���
const int   cPlayer::DEAD_EFFECT_NUM = 12;			// ���S�G�t�F�N�g�̐�
const float cPlayer::DEAD_EFFECT_SPEED = 5.0f;		// ���S�G�t�F�N�g�̈ړ��X�s�[�h
const int   cPlayer::PRIORITY = 400;				// �\���D��x
//==================================================================================
// �R���X�g���N�^
//==================================================================================
cPlayer::cPlayer(IBaseObject * parent):
	cSpriteObject(parent,"Player","data\\graphic\\val_01.png")
	, m_vVelocity(0.0f,0.0f)
	, m_eState( STATE::START)
{
}

//==================================================================================
// �f�X�g���N�^
//==================================================================================
cPlayer::~cPlayer(void)
{
}

//==================================================================================
// ������
//==================================================================================
void cPlayer::Initialize(void)
{
	SetPriority(PRIORITY);
	m_vVelocity = {0.0f,0.0f};
}

//==================================================================================
// �X�V
//==================================================================================
void cPlayer::Update(void)
{
	switch (m_eState)
	{
	case STATE::START:  Start();  break;
	case STATE::NORMAL: Normal(); break;
	case STATE::DEAD:   Dead();   break;
	case STATE::GOAL:   Goal();   break;
	default:					  break;
	}
#ifdef DEBUG
	// �����蔻��̕\��
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, DIST, 0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==================================================================================
// �j��
//==================================================================================
IBaseObject * cPlayer::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==================================================================================
// �v���C���[��Ԃ̕ύX
//==================================================================================
void cPlayer::ChangeState(STATE state)
{
	m_eState = state;
}
//==================================================================================
// �J�n���
//==================================================================================
void cPlayer::Start()
{

}
//==================================================================================
// �ʏ���
//==================================================================================
void cPlayer::Normal()
{
	// �����x�Z���T�[�̒l���擾
	VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_ACCELEROMETER);

	// �ړ��ʂƂ��Ďg����l�Ɍv�Z����
	cVector2 velocity = CalcSensorVector(v);

	// ����ʂȂ̂�x,y�𔽓]���ē����
	m_vVelocity.x += velocity.y;
	m_vVelocity.y += velocity.x;

	// ���C
	m_vVelocity *= FRICTION;

	// �ړ��l����ꍞ��
	m_vPos += m_vVelocity;

	// ���Ԑ؂ꔻ��
	CheckTimeOver();

	// �ǔ���
	CheckHitWall();

	// �L�����N�^�[�̃A�j���[�V��������
	Animation();
}
//==================================================================================
// ���S���
//==================================================================================
void cPlayer::Dead()
{
	cTimer* timer = (cTimer*)FindChild("DeadTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this,"DeadTimer");
		timer->Setup(DEAD_TIME);

		// �^�C�}�[�𐶐������u�ԂɐU����������
		Vibrator_vibrate(DEAD_TIME * 1000,128);

		// ���S��Ԃł̓L�����N�^�[���\���ɂ���
		m_bVisible = false;

		// �G�t�F�N�g����
		cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		if (em)
		{
			for (int i = 0; i < DEAD_EFFECT_NUM; i++)
			{
				cDeadEffect* ef = (cDeadEffect*)em->Create(EFFECT_ID::DEAD, m_vPos);
				ef->SetMove(360 / DEAD_EFFECT_NUM * i, DEAD_EFFECT_SPEED);
			}
		}
	}
}
//==================================================================================
// �S�[�����
//==================================================================================
void cPlayer::Goal()
{
	
}
//==================================================================================
// AndroidSensorVector�̖߂�l��cPlayer���g����l�ɂ���
//==================================================================================
cVector2 cPlayer::CalcSensorVector(VECTOR dxvector)
{
	cVector2 ret;
	// �������l��؂肷�āA�X���������Ȏ��͓����Ȃ��悤�ɂ���
	if (fabs(dxvector.x) <= SLOPE_MIN_ROUNDDOWN)
	{
		dxvector.x = 0.0f;
	}
	if (fabs(dxvector.y) <= SLOPE_MIN_ROUNDDOWN)
	{
		dxvector.y = 0.0f;
	}
	// �͂���������̂�1/10�ɂ���
	dxvector.x *= SENSOR_RATE;
	dxvector.y *= SENSOR_RATE;

	ret.x = dxvector.x;
	ret.y = dxvector.y;

	return ret;
}

//==================================================================================
// �ǔ���
//==================================================================================
void cPlayer::CheckHitWall(void)
{
	cGame* gm = (cGame*)GetRoot();
	if (m_vPos.x - GetSpriteSize().x / 2.0f < 0.0f)
	{
		// �ǂ̓����֖߂�
		m_vPos.x = GetSpriteSize().x / 2.0f;
		// ���˂��閈�ɉ���������������
		m_vVelocity.x = -m_vVelocity.x * REFLECTION;
	}
	if (m_vPos.x + GetSpriteSize().x / 2.0f > gm->GetWindowWidth())
	{
		// �ǂ̓����֖߂�
		m_vPos.x = gm->GetWindowWidth() - GetSpriteSize().x / 2.0f;
		// ���˂��閈�ɉ���������������
		m_vVelocity.x = -m_vVelocity.x * REFLECTION;
	}
	if (m_vPos.y - GetSpriteSize().y / 2.0f < 0.0f)
	{
		// �ǂ̓����֖߂�
		m_vPos.y = GetSpriteSize().y / 2.0f;
		// ���˂��閈�ɉ���������������
		m_vVelocity.y = -m_vVelocity.y * REFLECTION;
	}
	if (m_vPos.y + GetSpriteSize().y / 2.0f > gm->GetWindowHeight())
	{
		// �ǂ̓����֖߂�
		m_vPos.y = gm->GetWindowHeight() - GetSpriteSize().y / 2.0f;
		// ���˂��閈�ɉ���������������
		m_vVelocity.y = -m_vVelocity.y * REFLECTION;
	}
}
//==================================================================================
// ���Ԑ؂�`�F�b�N
//==================================================================================
void cPlayer::CheckTimeOver(void)
{
	cGameMain* gm = (cGameMain*)GetParent();
	if (gm->GetObjectName() == "GameMain")
	{
		// ���Ԑ؂ꂾ�����玀�S�ɂ���
		if (gm->GetOverTimeSecond() <= 0 && gm->GetOverTimeMinute() <= 0)
		{
			m_eState = STATE::DEAD;
		}
	}
}
//==================================================================================
// �A�j���[�V��������
//==================================================================================
void cPlayer::Animation(void)
{
	if (m_vVelocity.x < 0)
	{
		m_vScale.x = -1.0f;
	}
	else if (m_vVelocity.x > 0)
	{
		m_vScale.x = 1.0f;
	}
}
