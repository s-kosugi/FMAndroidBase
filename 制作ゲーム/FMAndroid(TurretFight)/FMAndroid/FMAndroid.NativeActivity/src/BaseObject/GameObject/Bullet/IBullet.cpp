/*==============================================================================*/
/*																				*/
/*	@file title	:	IBullet.cpp													*/
/*  @brief		:	弾ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "IBullet.h"
#include "cGame.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
// 定数
//==========================================================================================
const int  IBullet::AREAOUT_ADJUST = 100; // エリアアウト距離

//==========================================================================================
// コンストラクタ
//==========================================================================================
IBullet::IBullet(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name)
	,m_vPosUp(0.0f, 0.0f)
	,m_fDist(0.0f)
	,m_bInvincible( false )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
IBullet::~IBullet(void)
{
}
//==========================================================================================
// 初期化
//==========================================================================================
void IBullet::Initialize(void)
{
	Initialize({ 0.0f,0.0f }, 0.0f, 1.0f);
}
//==========================================================================================
// 初期化
//==========================================================================================
void IBullet::Initialize(const cVector2 & pos)
{
	Initialize(pos, 0.0f, 1.0f);
}

//==========================================================================================
// 初期化
//==========================================================================================
void IBullet::Initialize(const cVector2& pos, float angle, float speed)
{
	// 弾の移動量
	m_vPosUp.x = cos(DEG_TO_RAD(angle)) * speed;
	m_vPosUp.y = sin(DEG_TO_RAD(angle)) * speed;

	// 弾の回転
	m_fAngle = angle;

	m_vPos = pos;

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void IBullet::Update(void)
{
	
	// 移動処理
	m_vPos += m_vPosUp;

	// エリアアウトしたら弾を削除する
	AreaOutAllProc();

	// 敵との当たり判定処理をする
	CheckHitEnemy();

#ifdef DEBUG
	// 当たり判定の描画
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos,m_fDist,0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* IBullet::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// 当たり判定処理
//==========================================================================================
void IBullet::CheckHitEnemy(void)
{
	cEnemyManager* em = (cEnemyManager*)GetParent()->FindSibling("EnemyManager");

	if (em)
	{
		// 当たったら弾を消す
		if (em->CheckHit(m_vPos, m_fDist))
		{
			// 無敵フラグ
			if (!m_bInvincible) DeleteObject();
		}
	}
}

//==========================================================================================
// 左エリアアウト処理
//==========================================================================================
void IBullet::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 上エリアアウト処理
//==========================================================================================
void IBullet::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 右エリアアウト処理
//==========================================================================================
void IBullet::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 下エリアアウト処理
//==========================================================================================
void IBullet::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 全方向エリアアウト処理
//==========================================================================================
void IBullet::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}