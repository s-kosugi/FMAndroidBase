/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.cpp											*/
/*  @brief		:	�G�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyManager.h"
#include "cGame.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"
#include "EnmWhite/cEnmWhite.h"
#include "EnmBlue/cEnmBlue.h"
#include "EnmYellow/cEnmYellow.h"
#include "EnmRed/cEnmRed.h"
#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
// �萔
//==========================================================================================
const int cEnemyManager::DEFAULT_POP_INTERVAL = 120;  // �����o���Ԋu
const int cEnemyManager::DIFFICULT_POP_RATE = 10;	  // ��Փx�ɂ��G�̏o���p�x�̔{��


//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnemyManager::cEnemyManager(IBaseObject* pObj)
	:IBaseObject(pObj, "EnemyManager")
	, m_nPopCounter(0)
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnemyManager::~cEnemyManager(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnemyManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnemyManager::Update(void)
{
	// �G�̏o������
	ControlPop();

	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cEnemyManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// �G����
// return : ���������G�̃|�C���^ ��������Ȃ������ꍇ��nullptr
//==========================================================================================
IEnemy* cEnemyManager::Create(ENEMY_ID id, const cVector2& pos)
{
	IEnemy* pObj = nullptr;
	switch (id)
	{
	case ENEMY_ID::WHITE:
		pObj = CreateObject<cEnmWhite>(this);
		break;
	case ENEMY_ID::BLUE:
		pObj = CreateObject <cEnmBlue> (this);
		break;
	case ENEMY_ID::YELLOW:
		pObj = CreateObject <cEnmYellow>(this);
		break;
	case ENEMY_ID::RED:
		pObj = CreateObject <cEnmRed>(this);
		break;
	default:
		break;
	}

	if (pObj)
	{
		pObj->Initialize(pos);
	}

	return pObj;
}

//==========================================================================================
// �����蔻��`�F�b�N
// pos : ���������I�u�W�F�N�g�̈ʒu
// dist : ���������I�u�W�F�N�g�̔��a
// ret : true ��������  false �������ĂȂ�
//==========================================================================================
bool cEnemyManager::CheckHit(const cVector2 & pos, float dist)
{
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end();it++)
	{
		IEnemy* enm = (IEnemy*)(*it);
		if ( enm->GetState() != IEnemy::STATE::DEAD && dist + enm->GetDist() > enm->GetPos().CalcTwoPointDist(pos))
		{
			enm->Damage();
			return true;
		}
	}
	return false;
}

//==========================================================================================
// �G�̏o������
//==========================================================================================
void cEnemyManager::ControlPop(void)
{
	m_nPopCounter++;

	// ��Փx�ɂ���ēG�̏o���p�x��ύX����
	cGameMain* gm = (cGameMain*)GetParent();
	if (m_nPopCounter % (DEFAULT_POP_INTERVAL - gm->GetDifficult() * DIFFICULT_POP_RATE) == 0)
	{
		cGame* game = (cGame*)GetRoot();

		// �G�̈ʒu�������_���Ɍ��肷��
		cVector2 pos;
		pos.x = cGame::Random(0, game->GetWindowWidth());
		pos.y = cGame::Random(0, game->GetWindowHeight());
			
		// �G�̐���
		Create((ENEMY_ID)(cGame::Random(0, (int)ENEMY_ID::MAX-1)), pos);
	}
}
