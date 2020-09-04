/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.cpp												*/
/*  @brief		:	UI�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "cUIManager.h"
#include "ScoreBoard/cScoreBoard.h"
#include "Button/StartButton/cStartButton.h"
#include "Button/TitleButton/cTitleButton.h"

//==========================================================================================
// �萔
//==========================================================================================

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cUIManager::cUIManager( IBaseObject* pObj )
	:IBaseObject( pObj, "UIManager" )
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cUIManager::~cUIManager( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cUIManager::Initialize( void )
{
}

//==========================================================================================
// UI����(�ʒu�w�肠��)
// return : ��������UI�̃|�C���^ ��������Ȃ������ꍇ��nullptr
//==========================================================================================
cSpriteObject* cUIManager::Create( UIID id ,const cVector2& pos)
{
	cSpriteObject* pObj = Create(id);

	// ��������Ă�����ʒu��ݒ�
	if( pObj )
	{
		pObj->SetPos( pos );
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
	case UIID::SCORE_BOARD:	pObj = CreateObject<cScoreBoard>(this); break;
	case UIID::START_BUTTON: pObj = CreateObject<cStartButton>(this); break;
	case UIID::TITLE_BUTTON: pObj = CreateObject<cTitleButton>(this); break;
	default: break;
	}
	if (pObj)
	{
		pObj->Initialize();
	}

	return pObj;
}
