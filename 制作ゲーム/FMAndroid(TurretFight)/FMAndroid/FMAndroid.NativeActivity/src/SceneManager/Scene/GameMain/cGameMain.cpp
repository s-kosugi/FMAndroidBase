/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "cGameMain.h"
#include "cGame.h"
#include "..\..\cSceneManager.h"
#include "BaseObject\cSpriteObject.h"

#include "BaseObject\GameObject\Player\cPlayer.h"
#include "BaseObject/GameObject/Bullet/cBulletManager.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "DataManager/cDataManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "ScoreManager/cScoreManager.h"


#include "BaseObject/GameObject/GameStartObject/cReadyFont.h"
#include "BaseObject/GameObject/GameStartObject/cGoFont.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif



//==========================================================================================
// 定数
//==========================================================================================
const short cGameMain::MAX_DIFFICULT = 10;		// 最大難易度
const float cGameMain::LEVELUP_TIME = 10.0f;	// 難易度が上がるまでの時間(秒)

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_nDifficult( 0 )
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
	// ゲームクラスの取得
	cGame* game = (cGame*)GetRoot();

	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-100);
	obj->SetPos((float)game->GetWindowWidth()/2, (float)game->GetWindowHeight() / 2);

	// プレイヤーキャラクターの生成
	CreateObject<cPlayer>(this);

	// 弾管理クラスの生成
	CreateObject<cBulletManager>(this);

	// スコア管理クラスの取得
	cScoreManager* score = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	// スコアリセット
	score->ResetScore();

	// UI管理クラスの生成
	cUIManager* um = CreateObject<cUIManager>(this);
	// スコアボードの生成
	um->Create(UIID::SCORE_BOARD,{ 100,50 });

	// ゲーム開始演出用文字スプライト生成
	CreateObject<cReadyFont>(this);

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cGameMain::Update(void)
{
	switch (m_eState) {
	case START: Start(); break;
	case PLAY:  Play();  break;
	case OVER:  Over();  break;
	default: break;
	}

	IBaseObject::Update();

}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{
	ControlGameLevel();

	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// ゲームレベル制御関数
//==========================================================================================
void cGameMain::ControlGameLevel(void)
{
	// 段階的にゲームを難しくするための処理
	cTimer* lvTimer = (cTimer*)FindChild("LevelUpTimer");
	if (lvTimer)
	{
		if (lvTimer->Finished())
		{
			// レベルアップタイマーを初期化して難易度を1段階上げる
			lvTimer->Reset();
			m_nDifficult++;
			if (m_nDifficult >= MAX_DIFFICULT) m_nDifficult = MAX_DIFFICULT;
		}
	}
	else
	{
		// レベルアップタイマーの生成
		lvTimer = CreateObject<cTimer>(this, "LevelUpTimer");
		lvTimer->Setup(LEVELUP_TIME);
	}
}

//==========================================================================================
// ゲーム開始時
//==========================================================================================
void cGameMain::Start(void)
{
	cReadyFont* ready = (cReadyFont*)FindChild("ReadyFont");
	cGoFont* go = (cGoFont*)FindChild("GoFont");

	// 演出終了したらゲームプレイ状態にする
	if (ready == nullptr && go == nullptr)
	{
		m_eState = STATE::PLAY;


		// 敵管理クラスの生成
		CreateObject<cEnemyManager>(this);
	}
}

//==========================================================================================
// プレイ中
//==========================================================================================
void cGameMain::Play(void)
{
	// ゲームレベルの制御
	ControlGameLevel();
}

//==========================================================================================
// ゲームオーバー
//==========================================================================================
void cGameMain::Over(void)
{
}
