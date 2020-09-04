/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "cGame.h"
#include "cGameMain.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "BaseObject/GameObject/Player/cPlayer.h"
#include "BaseObject/GameObject/Stage/cStageManager.h"
#include "Utility/Timer/cTimer.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
// �萔
//==========================================================================================
const float cGameMain::TIME_OVER_LIMIT = 90.0f;
const float cGameMain::GOAL_TIME = 2.0f;
const float cGameMain::DEAD_TIME = 2.0f;
const float cGameMain::START_TIME = 2.0f;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_eState( STATE::START )
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cGameMain::~cGameMain(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cGameMain::Initialize(void)
{
	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "GameMainBack", "data\\graphic\\GameMainBack.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth()/2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	CreateObject<cPlayer>(this);
	CreateObject<cStageManager>(this);

	// �Q�[���^�C�}�[�̐ݒ�
	cTimer* timer = CreateObject<cTimer>(this, "GameOverTimer");
	timer->Setup(TIME_OVER_LIMIT);

	// UI�Ǘ��̐���
	cUIManager* um = CreateObject<cUIManager>(this);

	IBaseObject::Initialize();

	cGame* game = (cGame*)GetRoot();

	um->Create(UIID::OVER_TIMER, { game->GetWindowCenter().x,28 });
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{
	switch (m_eState)
	{
	case STATE::START: Start(); break;
	case STATE::MAIN: Main(); break;
	case STATE::CLEAR: Clear(); break;
	case STATE::OVER: Over(); break;
	}
	IBaseObject::Update();
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  �Q�[���I�[�o�[�܂ł̕����擾
//==========================================================================================
int cGameMain::GetOverTimeMinute(void)
{
	int ret = 0;
	cTimer* timer = (cTimer*)FindChild("GameOverTimer");
	if (timer)
	{
		if (!timer->Finished())
		{
			ret = (int)(timer->GetLimit() - timer->GetTime()) / 60;
		}
	}
	return ret;
}
//==========================================================================================
//  �Q�[���I�[�o�[�܂ł̕b���擾
//==========================================================================================
int cGameMain::GetOverTimeSecond(void)
{
	int ret = 0;
	cTimer* timer = (cTimer*)FindChild("GameOverTimer");
	if (timer)
	{
		if (!timer->Finished())
		{
			ret = (int)(timer->GetLimit() - timer->GetTime()) % 60;
		}
	}
	return ret;
}
//==========================================================================================
//  �J�n
//==========================================================================================
void cGameMain::Start(void)
{
	cTimer* timer = (cTimer*)FindChild("GameStartTimer");
	cTimer* gameOverTimer = (cTimer*)FindChild("GameOverTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "GameStartTimer");
		timer->Setup(START_TIME);

		// �X�^�[�g�����̐���
		cUIManager* ui = (cUIManager*)FindChild("UIManager");
		ui->Create(UIID::START_FONT);

		// �I�u�W�F�N�g�̏�Ԃ��X�V���~�߂Ă���
		gameOverTimer->SetObjetState(OBJECT_STATE::WAIT);
	}

	// �Q�[���J�n��Ԃ��I�������^�C�}�[��߂�
	if (timer->Finished())
	{
		if( gameOverTimer)
		// �I�u�W�F�N�g�̏�Ԃ��X�V���J�n����
		gameOverTimer->SetObjetState(OBJECT_STATE::ACTIVE);

		// �v���C���[���Q�[�����s��Ԃɂ���
		cPlayer* player = (cPlayer*)FindChild("Player");
		if (player) player->ChangeState(cPlayer::STATE::NORMAL);

		m_eState = STATE::MAIN;
	}
}
//==========================================================================================
//  ���C��
//==========================================================================================
void cGameMain::Main(void)
{
	cPlayer* player = (cPlayer*)FindChild("Player");

	if (player)
	{
		// �v���C���[�̏�Ԃɉ����ăQ�[�����C���̏�Ԃ�ύX����
		if (player->GetState() == cPlayer::STATE::GOAL)
		{
			m_eState = STATE::CLEAR;
		}
		if (player->GetState() == cPlayer::STATE::DEAD)
		{
			m_eState = STATE::OVER;
		}
	}
}
//==========================================================================================
//  �N���A
//==========================================================================================
void cGameMain::Clear(void)
{
	cTimer* timer = (cTimer*)FindChild("GoalTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "GoalTimer");
		timer->Setup(GOAL_TIME);
		
		cUIManager* ui = (cUIManager*)FindChild("UIManager");
		if (ui)
		{
			ui->Create(UIID::CLEAR_FONT);
		}
	}

	// ���Ԃ��o�߂�����V�[���ڍs
	if (timer->Finished())
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		if (sm) sm->ChangeSceneUniTrans(SCENE_ID::TITLE, "data\\graphic\\rule_00.png");
	}
	cTimer* coinTimer = (cTimer*)FindChild("CoinTimer");
	if (!coinTimer)
	{
		coinTimer = CreateObject<cTimer>(this,"CoinTimer");
		coinTimer->Setup(0.02f);
	}
	if (coinTimer->Finished())
	{
		coinTimer->Reset();
		cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		cGame* game = (cGame*)GetRoot();
		em->Create(EFFECT_ID::COIN, { (float)cGame::Random(0,game->GetWindowWidth()),0.0f - 32.0f });
		em->Create(EFFECT_ID::COIN, { (float)cGame::Random(0,game->GetWindowWidth()),0.0f - 32.0f });
	}
}
//==========================================================================================
//  �I�[�o�[
//==========================================================================================
void cGameMain::Over(void)
{
	cTimer* timer = (cTimer*)FindChild("MainDeadTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "MainDeadTimer");
		timer->Setup(DEAD_TIME);

		cUIManager* ui = (cUIManager*)FindChild("UIManager");
		if (ui)
		{
			ui->Create(UIID::MISS_FONT);
		}
	}

	// ���S��Ԃ̎��Ԃ��o�߂�����V�[���ڍs
	if (timer->Finished())
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		if (sm) sm->ChangeSceneUniTrans(SCENE_ID::TITLE, "data\\graphic\\rule_00.png");
	}
}
