/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlue.cpp												*/
/*  @brief		:	青い敵クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cEnmBlue.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cEnmBlue::PRIORITY = 300;
const float cEnmBlue::ROTATE_SPEED = 6.0f;
const int   cEnmBlue::BASE_DIST = 100;
const int   cEnmBlue::MIN_TIME = 8;
const int   cEnmBlue::MAX_TIME = 15;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmBlue::cEnmBlue(IBaseObject * parent)
	: IEnemy(parent, "EnmBlue", "data\\graphic\\enemy_02.png")
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmBlue::~cEnmBlue(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmBlue::Initialize(const cVector2 & pos)
{
	SetPriority(PRIORITY);
	// 当たり判定を設定
	m_fDist = GetSpriteSize().x / 2.0f;

	// 位置を設定する
	m_vPos = pos;

	SetAngle((float)cGame::Random(0,359));

	IEnemy::Initialize(m_vPos);
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnmBlue::Update(void)
{
	// 自転処理
	SetAngle(GetAngle() + ROTATE_SPEED);

	IEnemy::Update();
}
//==========================================================================================
// 通常状態
//==========================================================================================
void cEnmBlue::Normal(void)
{
	// 自機接近タイマー
	cTimer* timer = (cTimer*)FindChild("DistTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "DistTimer");
		timer->Setup((float)cGame::Random(MIN_TIME, MAX_TIME));
	}
	// プレイヤーに向かって移動
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		m_vPos.x = cos(DEG_TO_RAD(GetAngle()*0.1f)) * BASE_DIST * (timer->GetLimit() - timer->GetTime()) + pc->GetPos().x;
		m_vPos.y = sin(DEG_TO_RAD(GetAngle()*0.1f)) * BASE_DIST * (timer->GetLimit() - timer->GetTime()) + pc->GetPos().y;
	}
}
//==========================================================================================
// 範囲外処理
//==========================================================================================
void cEnmBlue::AreaOutAllProc(void)
{
	// オーバーライドして何も処理しない
}
