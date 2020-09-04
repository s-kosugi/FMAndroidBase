/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cGameMain.h"
#include "..\..\cSceneManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>

#include "..\..\..\BaseObject\GameObject\Player\cPlayer.h"
#include "DataManager/cDataManager.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"

#include "Input/Touch/cTouch.h"
#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cGameMain::~cGameMain(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cGameMain::Initialize(void)
{
	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth()/2, (float)cGame::GetInstance().GetWindowHeight() / 2);


	// �v���C���[�L�����N�^�[�̐���
	CreateObject<cPlayer>(this);

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{

	IBaseObject::Update();

	//----------------------------------------------------
	// �G�t�F�N�g�Đ�
	cTouch* touch = (cTouch*)GetRoot()->FindChild("Touch");
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (touch && em)
	{
		POINT pt;
		cTouch::TOUCH_STATE state;
		if (touch->GetTouchPos(0, pt, state))
		{
			if (state == cTouch::TOUCH_STATE::TRIGGER) em->Create(EFFECT_ID::BOM, pt);
		}
		if (touch->GetTouchPos(1, pt, state))
		{
			if (state == cTouch::TOUCH_STATE::TRIGGER) em->Create(EFFECT_ID::MUZZLE, pt);
		}

	}
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
