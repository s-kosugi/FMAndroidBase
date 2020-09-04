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
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	// テストスコアのロード
	cDataManager::GetInstance().LoadFile("testSave.bin");
#ifdef DEBUG
	cDebugFunc::GetInstance().PushDebugLog("LoadData = ",cDataManager::GetInstance().GetSaveData().Score);
#endif
	IBaseObject::Initialize();

	// UIクラスの生成
	cUIManager* ui = CreateObject<cUIManager>(this);
	ui->Create(UIID::START_BUTTON);
}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// ゲームメインシーンへ
	// ゲームメインシーンへ行くのはボタンで実装
	/*if (1 <= GetTouchInputNum())
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN,"data\\graphic\\rule_00.png");
	}*/
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
