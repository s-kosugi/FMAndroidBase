/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRed.cpp													*/
/*  @brief		:	赤い敵クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "cEnmRed.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cEnmRed::PRIORITY = 300;
const float cEnmRed::BASE_SPEED = 2.5f;
const float cEnmRed::ROTATE_SPEED = 8.0f;
const float cEnmRed::STOP_DIST = 400.0f;
const float cEnmRed::STOP_TIME = 3.0f;
const float cEnmRed::RESTART_TIME = 2.0f;
const float cEnmRed::RESTART_MAX_SPEED = 10.0f;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmRed::cEnmRed(IBaseObject * parent)
	: IEnemy(parent, "EnmRed", "data\\graphic\\enemy_04.png")
	, m_eActionState( ACTION_STATE::START )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmRed::~cEnmRed(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmRed::Initialize(const cVector2 & pos)
{

	SetPriority(PRIORITY);
	// 当たり判定を設定
	m_fDist = GetSpriteSize().x / 2.0f;

	// 位置を設定する
	m_vPos = pos;

	// 画面外配置処理
	ArrangeOffScreen();

	// 現在位置からプレイヤーに向かって移動させる
	GotoPlayer(BASE_SPEED);

	IEnemy::Initialize(m_vPos);
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnmRed::Update(void)
{
	// 自転処理
	SetAngle(GetAngle() + ROTATE_SPEED);

	switch (m_eActionState)
	{
	case ACTION_STATE::START: Start(); break;
	case ACTION_STATE::STOP: Stop(); break;
	case ACTION_STATE::RESTART: Restart(); break;
	}


	IEnemy::Update();
}

//==========================================================================================
// 開始状態
//==========================================================================================
void cEnmRed::Start(void)
{
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		// 停止距離になったら状態を変更する
		if (pc->GetPos().CalcTwoPointDist(m_vPos) < STOP_DIST)
		{
			m_eActionState = ACTION_STATE::STOP;
		}
	}
}

//==========================================================================================
// 停止状態
//==========================================================================================
void cEnmRed::Stop(void)
{
	cTimer* timer = (cTimer*)FindChild("StopTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "StopTimer");
		timer->Setup(STOP_TIME);
	}
	GotoPlayer(Easing::OutSine(timer->GetTime(), timer->GetLimit(), 0.0f, BASE_SPEED));

	if (timer->Finished())
	{
		m_eActionState = ACTION_STATE::RESTART;
		timer->DeleteObject();
	}
}

//==========================================================================================
// 再始動状態
//==========================================================================================
void cEnmRed::Restart(void)
{
	cTimer* timer = (cTimer*)FindChild("RestartTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "RestartTimer");
		timer->Setup(RESTART_TIME);
	}
	
	// 時間で加速する
	if (!timer->Finished())
	{
		GotoPlayer(Easing::InSine(timer->GetTime(),timer->GetLimit(), RESTART_MAX_SPEED,0.0f));
	}

}
