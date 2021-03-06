/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartButton.cpp											*/
/*  @brief		:	スタートボタンクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cStartButton.h"
#include "cGame.h"
#include "SceneManager/cSceneManager.h"
#include "SoundCtrl/cSoundCtrl.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cStartButton::PRIORITY = 200;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cStartButton::cStartButton(IBaseObject * parent)
	: IButton(parent, "StartButton", "data\\graphic\\start_button.png")
	, m_bPressed(false)
{
}
//==========================================================================================
// 初期化
//==========================================================================================
void cStartButton::Initialize(void)
{
	IButton::Initialize();

	cGame* game = (cGame*)GetRoot();
	SetPos(game->GetWindowWidth() / 2.0f,game->GetWindowHeight() / 4 * 3);
	// スプライトのRectを左半分にする
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	// Rectの大きさを変えたので中心位置を変更
	m_vCenter.x = GetSpriteSize().x / 2.0f;


	SetPriority(PRIORITY);
}
//==========================================================================================
// 押されていない時
//==========================================================================================
void cStartButton::Neutral(void)
{
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	m_bPressed = false;
}
//==========================================================================================
// 押された瞬間
//==========================================================================================
void cStartButton::Trigger(void)
{
	SetSrcRect(this->GetGraphichSize().x / 2.0f,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	m_bPressed = true;

	// スイッチ音
	cSoundCtrl* sound = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	sound->Play(SOUND_ID::KACHI);
}
//==========================================================================================
// 押されている間
//==========================================================================================
void cStartButton::Pressed(void)
{
	if( m_bPressed ) SetSrcRect(this->GetGraphichSize().x / 2.0f,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
	else SetSrcRect(0, 0, this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);
}
//==========================================================================================
// 離された瞬間
//==========================================================================================
void cStartButton::Release(void)
{
	SetSrcRect(0,0,this->GetGraphichSize().x / 2.0f, this->GetSpriteSize().y);

	// ボタンが押されてから離されたのでシーン遷移をする
	if (m_bPressed)
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		if (sm)
		{
			sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN, "data\\graphic\\rule_00.png");
		}
	}
}
