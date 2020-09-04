/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.cpp													*/
/*  @brief		:	�Q�[���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "DrawCtrl\cDrawCtrl.h"
#include "MovieManager/cMovieManager.h"
#include "Input\cControllerManager.h"
#include "Input/Touch/cTouch.h"
#include "SceneManager\cSceneManager.h"
#include "DrawCtrl/Camera/cCamera.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"

#include "Utility\memory.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif // DEBUG

//==========================================================================================
// �萔
//==========================================================================================
const float             cGame::MAX_DELTA_TIME = 0.16f;		// �ő�f���^�^�C��
const float				cGame::ONE_MILL_SECOND = 1000.0f;	// �P�b
const int				cGame::CALC_FRAME_COUNT = 60;		// ���ς��v�Z����t���[���̐�
const int				cGame::WINDOW_SIZE_X = 1280;		// �E�B���h�E��
const int				cGame::WINDOW_SIZE_Y = 720;			// �E�B���h�E����

//==========================================================================================
//  ������
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Game";

	// FPS
	m_nFPS = DEFAULT_FPS;

	// 1�t���[�����̍X�V��
	m_nOneFrameUpdate = 1;

	// �f���^�^�C���ݒ�
	m_fDeltaTime = 0.0f;
	m_fDeltaTimeScale = 1.0f;

	// �X�V�t���[���ݒ�
	m_nFrameCount = 0;
	m_nStartTime = 0;
	m_nPrevTime = 0;

	// �v���C�G���A�̐ݒ�(UI�\���̈悪���邱�Ƃ�z��)
	m_PlayArea = { 0,0,GetWindowWidth(),GetWindowHeight() };

	// �`�摀��N���X
	AddChild(&cDrawCtrl::GetInstance());

	// �G�t�F�N�g�Ǘ��N���X
	CreateObject<cEffectManager>(this);

	// ����Ǘ��N���X
	AddChild(&cMovieManager::GetInstance());

	// �T�E���h����N���X
	AddChild(&cSoundCtrl::GetInstance());
	// �S�T�E���h�̓ǂݍ���
	cSoundCtrl::GetInstance().LoadAll();

	// ���͊Ǘ��N���X
	AddChild(&cTouch::GetInstance());
	AddChild(&cControllerManager::GetInstance());

	// �V�[���}�l�[�W���[�N���X
	AddChild(&cSceneManager::GetInstance());

	// �J�����N���X
	AddChild(&cCamera::GetInstance());

#ifdef DEBUG
	// �f�o�b�O�@�\�N���X
	AddChild(&cDebugFunc::GetInstance());
#endif // DEBUG


	IBaseObject::Initialize();

}
//==========================================================================================
//  �X�V
//==========================================================================================
void cGame::Update(void)
{
	// �t���[���J�E���g�Z�o
	CalcFrameCount();

	for (int i = 0; i < m_nOneFrameUpdate; i++)
	{
		// �ʏ�̍X�V
		IBaseObject::Update();
	}
}
//==========================================================================================
//  �`��
//==========================================================================================
void cGame::Draw(void)
{
	cDrawCtrl::GetInstance().Draw();
#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif // DEBUG
}

//==========================================================================================
// �����̔���
//==========================================================================================
int cGame::Random(int min, int max)
{
	int range;

	range = max - min;
	return GetRand(range) + min;
}

//==========================================================================================
// �X�V����t���[���J�E���g�̌v�Z
//==========================================================================================
void cGame::CalcFrameCount(void)
{
	// ���݂̎��Ԃ��擾
	int now_time = GetNowCount();

	// �v�Z�J�n��
	if (m_nFrameCount == 0)
	{
		m_nStartTime = now_time;
	}
	// �w�肳�ꂽ�t���[���J�E���g��
	else if (m_nFrameCount == CALC_FRAME_COUNT)
	{
		m_nFrameCount = 0;

		m_nStartTime = now_time;
	}

	// �t���[���J�E���g���X�V
	++m_nFrameCount;

	// �O�̏����Ƃ̎��Ԃ̍�
	int sub_time = now_time - m_nPrevTime;

	// �f���^�^�C�����Z�o
	m_fDeltaTime = (float)sub_time / ONE_MILL_SECOND;

	// �ő�f���^�^�C���Ő�������
	if (m_fDeltaTime > MAX_DELTA_TIME) m_fDeltaTime = MAX_DELTA_TIME;

	// ���̎��Ԃ�ۑ�
	m_nPrevTime = now_time;
}