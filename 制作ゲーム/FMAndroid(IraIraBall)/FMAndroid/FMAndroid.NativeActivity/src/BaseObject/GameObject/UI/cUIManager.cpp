/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.cpp												*/
/*  @brief		:	UI�Ǘ��N���X												*/
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
#include "TouchFont/cTouchFont.h"

//==========================================================================================
// �萔
//==========================================================================================

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cUIManager::cUIManager(IBaseObject* pObj)
	:IBaseObject(pObj, "UIManager")
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cUIManager::~cUIManager(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cUIManager::Initialize(void)
{
}

//==========================================================================================
// UI����(�ʒu�w�肠��)
// return : ��������UI�̃|�C���^ ��������Ȃ������ꍇ��nullptr
//==========================================================================================
cSpriteObject* cUIManager::Create(UIID id, const cVector2& pos)
{
	cSpriteObject* pObj = Create(id);

	// ��������Ă�����ʒu��ݒ�
	if (pObj)
	{
		pObj->SetPos(pos);
	}

	return pObj;
}
//==========================================================================================
// UI����
// return : ��������UI�̃|�C���^ ��������Ȃ������ꍇ��nullptr
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
	case UIID::TOUCH_FONT: pObj = CreateObject<cTouchFont>(this); break;
	default: break;
	}
	if (pObj)
	{
		pObj->Initialize();
	}

	return pObj;
}
