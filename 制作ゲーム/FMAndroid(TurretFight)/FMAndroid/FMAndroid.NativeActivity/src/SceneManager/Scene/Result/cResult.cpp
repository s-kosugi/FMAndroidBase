/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.cpp													*/
/*  @brief		:	���U���g�V�[��												*/
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
//  �萔
//==========================================================================================
const int cResult::RANK_B_BORDER = 10;
const int cResult::RANK_A_BORDER = 40;
const int cResult::RANK_S_BORDER = 80;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cResult::cResult(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cResult::~cResult(void)
{
}
//==========================================================================================
//  ������
//==========================================================================================
void cResult::Initialize(void)
{
	// �Q�[���N���X�̎擾
	cGame* game = (cGame*)GetRoot();

	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-101);
	obj->SetPos((float)game->GetWindowWidth() / 2, (float)game->GetWindowHeight() / 2);

	// UI�Ǘ��̐���
	cUIManager* ui = CreateObject<cUIManager>(this);
	cSpriteObject* button = ui->Create(UIID::TITLE_BUTTON);

	// �X�R�A�̎擾
	cScoreManager* scoreman = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	int score = scoreman->GetScore();

	// �����N�摜�̃p�X����
	std::string file_name;
	if (score < RANK_B_BORDER) file_name = "data\\graphic\\rank_c.png";
	if (score >= RANK_B_BORDER) file_name = "data\\graphic\\rank_b.png";
	if (score >= RANK_A_BORDER) file_name = "data\\graphic\\rank_a.png";
	if (score >= RANK_S_BORDER) file_name = "data\\graphic\\rank_s.png";

	// �����N�摜�̐���
	cSpriteObject* rank = CreateDrawObject<cSpriteObject>(this, "Rank", file_name.c_str());
	rank->SetPos(game->GetWindowCenter().x,game->GetWindowHeight() / 4);

	IBaseObject::Initialize();

	//------------------------------------------------------------------
	// �{�^���̈ʒu����ɃJ�[�\����z�u(�^�C�g���J�[�\���𗬗p)
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
//  �X�V
//==========================================================================================
void cResult::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cResult::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}
