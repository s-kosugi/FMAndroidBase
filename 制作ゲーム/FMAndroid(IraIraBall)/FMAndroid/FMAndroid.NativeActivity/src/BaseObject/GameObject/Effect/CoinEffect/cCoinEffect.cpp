/*==============================================================================*/
/*																				*/
/*	@file title	:	cCoinEffect.cpp												*/
/*  @brief		:	コインエフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "cCoinEffect.h"
#include "cGame.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cCoinEffect::PRIORITY = 400;
const float cCoinEffect::MAX_SPEED = 20.0f;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cCoinEffect::cCoinEffect(IBaseObject * parent)
	: IEffect(parent, "CoinEffect", "data\\graphic\\coin.png")
	, m_vVelocity()
	, m_fScaleCurve( 0.0f )
{
	SetPriority(PRIORITY);
}

//==========================================================================================
// 初期化
//==========================================================================================
void cCoinEffect::Initialize(const cVector2 & pos)
{
	// アニメーション処理を使わないためセットしない
	// アニメーション初期設定
	//SetupAnime({ 128,128 }, 4, 23, 0.02f);

	IEffect::Initialize(pos);
}
//==========================================================================================
// 更新
//==========================================================================================
void cCoinEffect::Update(void)
{
	cGame* game = (cGame*)GetRoot();

	// 重力加速度をつける
	m_vVelocity.y += 0.45f;

	//最大速度
	if (m_vVelocity.y >= MAX_SPEED)
	{
		m_vVelocity.y = MAX_SPEED;
	}

	//
	m_fScaleCurve += 5.0f;
	m_vScale.x = sin(DEG_TO_RAD(m_fScaleCurve));

	m_vPos += m_vVelocity;

	// 画面外消去
	if (game->GetWindowHeight() < m_vPos.y + GetSpriteSize().y / 2.0f)
	{
		DeleteObject();
	}

	IEffect::Update();
}