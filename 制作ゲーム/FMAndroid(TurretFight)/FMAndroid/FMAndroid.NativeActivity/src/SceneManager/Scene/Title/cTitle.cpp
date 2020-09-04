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
#include "BaseObject/GameObject/GameStartObject/cTitleCursol.h"
#include "SoundCtrl/cSoundCtrl.h"

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
	// �Q�[���N���X�̎擾
	cGame* game = (cGame*)GetRoot();

	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-101);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// �^�C�g�����S�̐���
	obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// UI�Ǘ��̐���
	cUIManager* ui = CreateObject<cUIManager>(this);
	cSpriteObject* button = ui->Create(UIID::START_BUTTON);

	// BGM�̍Đ�
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	if (sc) sc->BGMPlay(SOUND_ID::BGM);

	IBaseObject::Initialize();

	//------------------------------------------------------------------
	// �{�^���̈ʒu����ɃJ�[�\����z�u
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
//  �X�V
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
