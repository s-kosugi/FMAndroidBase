/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.cpp											*/
/*  @brief		:	敵管理クラス												*/
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
// 定数
//==========================================================================================
const int cEnemyManager::DEFAULT_POP_INTERVAL = 120;  // 初期出現間隔
const int cEnemyManager::DIFFICULT_POP_RATE = 10;	  // 難易度による敵の出現頻度の倍率


//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnemyManager::cEnemyManager(IBaseObject* pObj)
	:IBaseObject(pObj, "EnemyManager")
	, m_nPopCounter(0)
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cEnemyManager::~cEnemyManager(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnemyManager::Initialize(void)
{
	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnemyManager::Update(void)
{
	// 敵の出現制御
	ControlPop();

	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cEnemyManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// 敵生成
// return : 生成した敵のポインタ 生成されなかった場合はnullptr
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
// 当たり判定チェック
// pos : 判定をするオブジェクトの位置
// dist : 判定をするオブジェクトの半径
// ret : true 当たった  false 当たってない
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
// 敵の出現制御
//==========================================================================================
void cEnemyManager::ControlPop(void)
{
	m_nPopCounter++;

	// 難易度によって敵の出現頻度を変更する
	cGameMain* gm = (cGameMain*)GetParent();
	if (m_nPopCounter % (DEFAULT_POP_INTERVAL - gm->GetDifficult() * DIFFICULT_POP_RATE) == 0)
	{
		cGame* game = (cGame*)GetRoot();

		// 敵の位置をランダムに決定する
		cVector2 pos;
		pos.x = cGame::Random(0, game->GetWindowWidth());
		pos.y = cGame::Random(0, game->GetWindowHeight());
			
		// 敵の生成
		Create((ENEMY_ID)(cGame::Random(0, (int)ENEMY_ID::MAX-1)), pos);
	}
}
