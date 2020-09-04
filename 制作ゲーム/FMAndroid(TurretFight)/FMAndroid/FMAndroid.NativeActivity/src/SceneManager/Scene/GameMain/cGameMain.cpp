/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "cGameMain.h"
#include "cGame.h"
#include "..\..\cSceneManager.h"
#include "BaseObject\cSpriteObject.h"

#include "BaseObject\GameObject\Player\cPlayer.h"
#include "BaseObject/GameObject/Bullet/cBulletManager.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "DataManager/cDataManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "ScoreManager/cScoreManager.h"


#include "BaseObject/GameObject/GameStartObject/cReadyFont.h"
#include "BaseObject/GameObject/GameStartObject/cGoFont.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif



//==========================================================================================
// �萔
//==========================================================================================
const short cGameMain::MAX_DIFFICULT = 10;		// �ő��Փx
const float cGameMain::LEVELUP_TIME = 10.0f;	// ��Փx���オ��܂ł̎���(�b)

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_nDifficult( 0 )
	, m_eState( STATE::START )
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
	// �Q�[���N���X�̎擾
	cGame* game = (cGame*)GetRoot();

	// �w�i�X�v���C�g�̐���
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "BackGround", "data\\graphic\\background.png");
	obj->SetPriority(-100);
	obj->SetPos((float)game->GetWindowWidth()/2, (float)game->GetWindowHeight() / 2);

	// �v���C���[�L�����N�^�[�̐���
	CreateObject<cPlayer>(this);

	// �e�Ǘ��N���X�̐���
	CreateObject<cBulletManager>(this);

	// �X�R�A�Ǘ��N���X�̎擾
	cScoreManager* score = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	// �X�R�A���Z�b�g
	score->ResetScore();

	// UI�Ǘ��N���X�̐���
	cUIManager* um = CreateObject<cUIManager>(this);
	// �X�R�A�{�[�h�̐���
	um->Create(UIID::SCORE_BOARD,{ 100,50 });

	// �Q�[���J�n���o�p�����X�v���C�g����
	CreateObject<cReadyFont>(this);

	IBaseObject::Initialize();
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGameMain::Update(void)
{
	switch (m_eState) {
	case START: Start(); break;
	case PLAY:  Play();  break;
	case OVER:  Over();  break;
	default: break;
	}

	IBaseObject::Update();

}
//==========================================================================================
//  �j��
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{
	ControlGameLevel();

	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// �Q�[�����x������֐�
//==========================================================================================
void cGameMain::ControlGameLevel(void)
{
	// �i�K�I�ɃQ�[���������邽�߂̏���
	cTimer* lvTimer = (cTimer*)FindChild("LevelUpTimer");
	if (lvTimer)
	{
		if (lvTimer->Finished())
		{
			// ���x���A�b�v�^�C�}�[�����������ē�Փx��1�i�K�グ��
			lvTimer->Reset();
			m_nDifficult++;
			if (m_nDifficult >= MAX_DIFFICULT) m_nDifficult = MAX_DIFFICULT;
		}
	}
	else
	{
		// ���x���A�b�v�^�C�}�[�̐���
		lvTimer = CreateObject<cTimer>(this, "LevelUpTimer");
		lvTimer->Setup(LEVELUP_TIME);
	}
}

//==========================================================================================
// �Q�[���J�n��
//==========================================================================================
void cGameMain::Start(void)
{
	cReadyFont* ready = (cReadyFont*)FindChild("ReadyFont");
	cGoFont* go = (cGoFont*)FindChild("GoFont");

	// ���o�I��������Q�[���v���C��Ԃɂ���
	if (ready == nullptr && go == nullptr)
	{
		m_eState = STATE::PLAY;


		// �G�Ǘ��N���X�̐���
		CreateObject<cEnemyManager>(this);
	}
}

//==========================================================================================
// �v���C��
//==========================================================================================
void cGameMain::Play(void)
{
	// �Q�[�����x���̐���
	ControlGameLevel();
}

//==========================================================================================
// �Q�[���I�[�o�[
//==========================================================================================
void cGameMain::Over(void)
{
}
