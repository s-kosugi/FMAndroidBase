/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\cGame.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"
#ifdef DEBUG
#include "..\..\..\DebugFunc\cDebugFunc.h"
#include <sstream>
#endif // DEBUG

//==========================================================================================
// �萔
//==========================================================================================
const float cPlayer::MOVE_SPEED = 3.0f;
const float cPlayer::START_POS_X = 300.0f;
const float cPlayer::START_POS_Y = 300.0f;
const int cPlayer::PRIORITY = 200;
const short cPlayer::SIZE_X = 64;
const short cPlayer::SIZE_Y = 64;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cPlayer::cPlayer(IBaseObject * parent)
	: cSpriteObject(parent, "Player", "data\\graphic\\player_01.png")
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
	m_vPos = { START_POS_X,START_POS_Y };
	SetPriority(PRIORITY);
	SetSrcRect(0, 0, SIZE_X, SIZE_Y);
	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cPlayer::Update(void)
{
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_RIGHT))
	{
		m_vPos.x += MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_LEFT))
	{
		m_vPos.x -= MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_UP))
	{
		m_vPos.y -= MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_DOWN))
	{
		m_vPos.y += MOVE_SPEED;
	}
	// �͈͊O����
	ProcAreaOut();

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
// �͈͊O����
//==========================================================================================
void cPlayer::ProcAreaOut(void)
{
	if (m_vPos.x - SIZE_X / 2 < 0.0f)
	{
		m_vPos.x = (float)SIZE_X / 2;
	}
	if (m_vPos.y - SIZE_Y / 2 < 0.0f)
	{
		m_vPos.y = (float)SIZE_Y / 2;
	}
	if (m_vPos.x + SIZE_X / 2 >= cGame::GetInstance().GetWindowWidth())
	{
		m_vPos.x = (float)cGame::GetInstance().GetWindowWidth() - SIZE_X /2;
	}
	if (m_vPos.y + SIZE_Y / 2 >= cGame::GetInstance().GetWindowHeight())
	{
		m_vPos.y = (float)cGame::GetInstance().GetWindowHeight() - SIZE_Y / 2;
	}
}
