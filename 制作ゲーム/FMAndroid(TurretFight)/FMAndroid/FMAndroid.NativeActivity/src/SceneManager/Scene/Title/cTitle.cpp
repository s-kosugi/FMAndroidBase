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
#include "BaseObject/GameObject/GameStartObject/cTitleCursol.h"
#include "SoundCtrl/cSoundCtrl.h"

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
	// ゲームクラスの取得
	cGame* game = (cGame*)GetRoot();

	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-101);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// タイトルロゴの生成
	obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// UI管理の生成
	cUIManager* ui = CreateObject<cUIManager>(this);
	cSpriteObject* button = ui->Create(UIID::START_BUTTON);

	// BGMの再生
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	if (sc) sc->BGMPlay(SOUND_ID::BGM);

	IBaseObject::Initialize();

	//------------------------------------------------------------------
	// ボタンの位置を基準にカーソルを配置
	cTitleCursol* cursol = CreateObject<cTitleCursol>(this);
	cursol->Initialize();
	cVector2 buttonPos = button->GetPos();
	buttonPos.x -= 250.0f;
	cursol->Setup(buttonPos, 90.0f);

	buttonPos = button->GetPos();
	cursol = CreateObject<cTitleCursol>(this);
	cursol->Initialize();
	buttonPos.x += 250.0f;
	cursol->Setup(buttonPos,-90.0f);
	//------------------------------------------------------------------

}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
