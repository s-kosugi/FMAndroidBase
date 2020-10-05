/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.cpp													*/
/*  @brief		:	タイトルシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cTitle.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>
#include "DataManager/cDataManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cTitle::~cTitle(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cTitle::Initialize(void)
{
	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\GameMainBack.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	// UI管理の生成
	cUIManager* um = CreateObject<cUIManager>(this);

	IBaseObject::Initialize();

	// タイトルロゴの生成
	um->Create(UIID::TITLE_LOGO);

	// タッチしてスタートの文字生成
	um->Create(UIID::TOUCH_FONT);
}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// ゲームメインシーンへ
	if (1 <= GetTouchInputNum())
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN,"data\\graphic\\rule_00.png");
	}
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
