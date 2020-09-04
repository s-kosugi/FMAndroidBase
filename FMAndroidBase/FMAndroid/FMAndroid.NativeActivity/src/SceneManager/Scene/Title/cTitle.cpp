/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.cpp													*/
/*  @brief		:	�^�C�g���V�[��												*/
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
//  �R���X�g���N�^
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTitle::~cTitle(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cTitle::Initialize(void)
{
	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	// �e�X�g�X�R�A�̃��[�h
	cDataManager::GetInstance().LoadFile("testSave.bin");
#ifdef DEBUG
	cDebugFunc::GetInstance().PushDebugLog("LoadData = ",cDataManager::GetInstance().GetSaveData().Score);
#endif
	IBaseObject::Initialize();

	// UI�N���X�̐���
	cUIManager* ui = CreateObject<cUIManager>(this);
	ui->Create(UIID::START_BUTTON);
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// �Q�[�����C���V�[����
	// �Q�[�����C���V�[���֍s���̂̓{�^���Ŏ���
	/*if (1 <= GetTouchInputNum())
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN,"data\\graphic\\rule_00.png");
	}*/
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}
