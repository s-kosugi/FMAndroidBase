/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.cpp												*/
/*  @brief		:	UI管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "cUIManager.h"
#include "OverTimer/cOverTimer.h"
#include "MissFont/cMissFont.h"
#include "StartFont/cStartFont.h"
#include "ClearFont/cClearFont.h"
#include "TitleLogo/cTitleLogo.h"

//==========================================================================================
// 定数
//==========================================================================================

//==========================================================================================
// コンストラクタ
//==========================================================================================
cUIManager::cUIManager(IBaseObject* pObj)
	:IBaseObject(pObj, "UIManager")
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cUIManager::~cUIManager(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cUIManager::Initialize(void)
{
}

//==========================================================================================
// UI生成(位置指定あり)
// return : 生成したUIのポインタ 生成されなかった場合はnullptr
//==========================================================================================
cSpriteObject* cUIManager::Create(UIID id, const cVector2& pos)
{
	cSpriteObject* pObj = Create(id);

	// 生成されていたら位置を設定
	if (pObj)
	{
		pObj->SetPos(pos);
	}

	return pObj;
}
//==========================================================================================
// UI生成
// return : 生成したUIのポインタ 生成されなかった場合はnullptr
//==========================================================================================
cSpriteObject * cUIManager::Create(UIID id)
{
	cSpriteObject* pObj = nullptr;
	switch (id)
	{
	case UIID::OVER_TIMER:	pObj = CreateObject<cOverTimer>(this); break;
	case UIID::MISS_FONT: pObj = CreateObject<cMissFont>(this); break;
	case UIID::START_FONT: pObj = CreateObject<cStartFont>(this); break;
	case UIID::CLEAR_FONT: pObj = CreateObject<cClearFont>(this); break;
	case UIID::TITLE_LOGO: pObj = CreateObject<cTitleLogo>(this); break;
	default: break;
	}
	if (pObj)
	{
		pObj->Initialize();
	}

	return pObj;
}
