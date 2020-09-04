/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	ゲームメインシーン											*/
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
// 定数
//==========================================================================================
const float cGameMain::TIME_OVER_LIMIT = 90.0f;
const float cGameMain::GOAL_TIME = 2.0f;
const float cGameMain::DEAD_TIME = 2.0f;
const float cGameMain::START_TIME = 2.0f;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_eState( STATE::START )
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cGameMain::~cGameMain(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cGameMain::Initialize(void)
{
	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "GameMainBack", "data\\graphic\\GameMainBack.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth()/2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	CreateObject<cPlayer>(this);
	CreateObject<cStageManager>(this);

	// ゲームタイマーの設定
	cTimer* timer = CreateObject<cTimer>(this, "GameOverTimer");
	timer->Setup(TIME_OVER_LIMIT);

	// UI管理の生成
	cUIManager* um = CreateObject<cUIManager>(this);

	IBaseObject::Initialize();

	cGame* game = (cGame*)GetRoot();

	um->Create(UIID::OVER_TIMER, { game->GetWindowCenter().x,28 });
}
//==========================================================================================
//  更新
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
//  破棄
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  ゲームオーバーまでの分を取得
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
//  ゲームオーバーまでの秒を取得
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
//  開始
//==========================================================================================
void cGameMain::Start(void)
{
	cTimer* timer = (cTimer*)FindChild("GameStartTimer");
	cTimer* gameOverTimer = (cTimer*)FindChild("GameOverTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "GameStartTimer");
		timer->Setup(START_TIME);

		// スタート文字の生成
		cUIManager* ui = (cUIManager*)FindChild("UIManager");
		ui->Create(UIID::START_FONT);

		// オブジェクトの状態を更新を止めておく
		gameOverTimer->SetObjetState(OBJECT_STATE::WAIT);
	}

	// ゲーム開始状態が終わったらタイマーを戻す
	if (timer->Finished())
	{
		if( gameOverTimer)
		// オブジェクトの状態を更新を開始する
		gameOverTimer->SetObjetState(OBJECT_STATE::ACTIVE);

		// プレイヤーをゲーム実行状態にする
		cPlayer* player = (cPlayer*)FindChild("Player");
		if (player) player->ChangeState(cPlayer::STATE::NORMAL);

		m_eState = STATE::MAIN;
	}
}
//==========================================================================================
//  メイン
//==========================================================================================
void cGameMain::Main(void)
{
	cPlayer* player = (cPlayer*)FindChild("Player");

	if (player)
	{
		// プレイヤーの状態に応じてゲームメインの状態を変更する
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
//  クリア
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

	// 時間が経過したらシーン移行
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
//  オーバー
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

	// 死亡状態の時間が経過したらシーン移行
	if (timer->Finished())
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		if (sm) sm->ChangeSceneUniTrans(SCENE_ID::TITLE, "data\\graphic\\rule_00.png");
	}
}
