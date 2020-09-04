/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.cpp													*/
/*  @brief		:	リザルトシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cResult.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>
#include "DataManager/cDataManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "BaseObject/GameObject/GameStartObject/cTitleCursol.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "ScoreManager/cScoreManager.h"

//==========================================================================================
//  定数
//==========================================================================================
const int cResult::RANK_B_BORDER = 10;
const int cResult::RANK_A_BORDER = 40;
const int cResult::RANK_S_BORDER = 80;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cResult::cResult(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cResult::~cResult(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cResult::Initialize(void)
{
	// ゲームクラスの取得
	cGame* game = (cGame*)GetRoot();

	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-101);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// UI管理の生成
	cUIManager* ui = CreateObject<cUIManager>(this);
	cSpriteObject* button = ui->Create(UIID::TITLE_BUTTON);

	// スコアの取得
	cScoreManager* scoreman = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	int score = scoreman->GetScore();

	// ランク画像のパス決定
	std::string file_name;
	if (score < RANK_B_BORDER) file_name = "data\\graphic\\rank_c.png";
	if (score >= RANK_B_BORDER) file_name = "data\\graphic\\rank_b.png";
	if (score >= RANK_A_BORDER) file_name = "data\\graphic\\rank_a.png";
	if (score >= RANK_S_BORDER) file_name = "data\\graphic\\rank_s.png";

	// ランク画像の生成
	cSpriteObject* rank = CreateDrawObject<cSpriteObject>(this, "Rank", file_name.c_str());
	rank->SetPos(game->GetWindowCenter().x,game->GetWindowHeight() / 4);

	IBaseObject::Initialize();

	//------------------------------------------------------------------
	// ボタンの位置を基準にカーソルを配置(タイトルカーソルを流用)
	cTitleCursol* cursol = CreateObject<cTitleCursol>(this);
	cursol->Initialize();
	cVector2 buttonPos = button->GetPos();
	buttonPos.x -= 250.0f;
	cursol->Setup(buttonPos, 90.0f);

	buttonPos = button->GetPos();
	cursol = CreateObject<cTitleCursol>(this);
	cursol->Initialize();
	buttonPos.x += 250.0f;
	cursol->Setup(buttonPos, -90.0f);
	//------------------------------------------------------------------
}
//==========================================================================================
//  更新
//==========================================================================================
void cResult::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cResult::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
