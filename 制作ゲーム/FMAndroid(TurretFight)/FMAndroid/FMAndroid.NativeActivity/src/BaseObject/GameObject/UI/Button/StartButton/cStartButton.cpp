/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartButton.cpp											*/
/*  @brief		:	�X�^�[�g�{�^���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cStartButton.h"
#include "cGame.h"
#include "SceneManager/cSceneManager.h"
#include "SoundCtrl/cSoundCtrl.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cStartButton::PRIORITY = 200;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cStartButton::cStartButton(IBaseObject * parent)
	: IButton(parent, "StartButton", "data\\graphic\\start_button.png")
	, m_bPressed(false)
{
}
//==========================================================================================
// ������
//==========================================================================================
void cStartButton::Initialize(void)
{
	IButton::Initialize();

	cGame* game = (cGame*)GetRoot();
	SetPos(game->GetWindowWidth() / 2.0f,game->GetWindowHeight() / 4 * 3);
	// �X�v���C�g��Rect���������ɂ���
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	// Rect�̑傫����ς����̂Œ��S�ʒu��ύX
	m_vCenter.x = GetSpriteSize().x / 2.0f;


	SetPriority(PRIORITY);
}
//==========================================================================================
// ������Ă��Ȃ���
//==========================================================================================
void cStartButton::Neutral(void)
{
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	m_bPressed = false;
}
//==========================================================================================
// �����ꂽ�u��
//==========================================================================================
void cStartButton::Trigger(void)
{
	SetSrcRect(this->GetGraphichSize().x / 2.0f,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	m_bPressed = true;

	// �X�C�b�`��
	cSoundCtrl* sound = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	sound->Play(SOUND_ID::KACHI);
}
//==========================================================================================
// ������Ă����
//==========================================================================================
void cStartButton::Pressed(void)
{
	if( m_bPressed ) SetSrcRect(this->GetGraphichSize().x / 2.0f,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	else SetSrcRect(0, 0, this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
}
//==========================================================================================
// �����ꂽ�u��
//==========================================================================================
void cStartButton::Release(void)
{
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);

	// �{�^����������Ă��痣���ꂽ�̂ŃV�[���J�ڂ�����
	if (m_bPressed)
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		if (sm)
		{
			sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN, "data\\graphic\\rule_00.png");
		}
	}
}
