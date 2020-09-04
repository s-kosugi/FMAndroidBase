/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "Input\Touch\cTouch.h"
#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "BaseObject/GameObject/Bullet/cBulletManager.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/Effect/IEffect.h"
#include "SceneManager/cSceneManager.h"
#include "Utility/Timer/cTimer.h"
#ifdef DEBUG
#include "..\..\..\DebugFunc\cDebugFunc.h"
#include <sstream>
#endif // DEBUG

//==========================================================================================
// 定数
//==========================================================================================
const float cPlayer::NORMAL_BUL_SPD = 10.0f;
const float cPlayer::NORMAL_BUL_INTERVAL = 0.2f;
const float cPlayer::BUL_FIRE_POS = 80.0f;
const int cPlayer::PRIORITY = 200;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cPlayer::cPlayer(IBaseObject * parent)
	: cSpriteObject(parent, "Player", "data\\graphic\\Turret.png")
	, m_fDist( 1.0f )
	, m_eState(STATE::NORMAL)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cPlayer::~cPlayer(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cPlayer::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();

	m_vPos = { game->GetWindowCenter().x,game->GetWindowCenter().y };
	SetPriority(PRIORITY);
	// 当たり判定の設定
	m_fDist = GetSpriteSize().x / 3.0f;

	// 弾発射間隔タイマーの生成
	cTimer* timer = CreateObject<cTimer>(this,"BulletTimer");
	timer->Setup(NORMAL_BUL_INTERVAL);

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cPlayer::Update(void)
{
	switch (m_eState)
	{
	case STATE::NORMAL: Normal(); break;
	case STATE::LASER: Laser(); break;
	case STATE::DEAD: Dead(); break;
	default: break;
	}

	cSpriteObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cPlayer::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// 通常状態
//==========================================================================================
void cPlayer::Normal(void)
{
	cTouch* touch = (cTouch*)GetRoot()->FindChild("Touch");
	cTimer* bulTimer = (cTimer*)FindChild("BulletTimer");
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	POINT pt;

	// タッチ座標を取得
	if (touch->GetTouchPos(0, pt))
	{
		// 自機の回転
		cVector2 vec(pt);
		m_fAngle = m_vPos.CalcTwoPointAngle(vec);

		// 弾の発射間隔を過ぎていたら発射する
		if (bulTimer && bulTimer->Finished())
		{
			bulTimer->Reset();

			cBulletManager* bm = (cBulletManager*)FindSibling("BulletManager");
			// 発射位置の調整
			cVector2 firePos;
			firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
			firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;

			bm->Create(BULLET_ID::NORMAL, firePos, m_fAngle, NORMAL_BUL_SPD);

			// エフェクトの生成
			cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			IEffect* effect = em->Create(EFFECT_ID::MUZZLE, firePos);
			effect->SetAngle(m_fAngle - 90.0f);

			// 音声の再生
			if (sc) sc->Play(SOUND_ID::SHOT);
		}
	}
	// ２点タッチが押されたらレーザー状態にする
	if (touch->GetTouchPos(1, pt))
	{
		StartLaser();
	}

	// 敵との当たり判定処理
	CheckHitEnemy();
#ifdef DEBUG
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif
}

//==========================================================================================
// レーザー発射状態
//==========================================================================================
void cPlayer::Laser(void)
{
	cTimer* timer = (cTimer*)FindChild("LaserTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "LaserTimer");
		timer->Setup(3.0f);
	}
	// タイマーが終わったので通常状態に戻す
	if (timer->Finished())
	{
		m_eState = STATE::NORMAL;
		timer->DeleteObject();

		// レーザーエフェクトを削除する
		cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		if (em) em->DeleteLaserEffect();
	}

	// 敵との当たり判定処理
	CheckHitEnemy();
#ifdef DEBUG
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif
}

//==========================================================================================
// 死亡状態
//==========================================================================================
void cPlayer::Dead(void)
{
	cTimer* timer = (cTimer*)FindChild("DeadTimer");

	// レーザーエフェクトを削除する
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (em) em->DeleteLaserEffect();

	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "DeadTimer");
		timer->Setup(2.0f);
	}

	// 死亡タイマーが経過したらシーンチェンジ
	if (timer->Finished())
	{
		cSceneManager* sm = (cSceneManager*)GetRoot()->FindChild("SceneManager");
		sm->ChangeSceneUniTrans(SCENE_ID::RESULT, "data\\graphic\\rule_00.png");
	}

}

//==========================================================================================
// レーザー開始処理
//==========================================================================================
void cPlayer::StartLaser(void)
{
	cGame* game = (cGame*)GetRoot();
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");

	// 自機をレーザー発射状態にする
	m_eState = STATE::LASER;

	// 音声の再生
	if (sc) sc->Play(SOUND_ID::LASER);

	// 発射位置の調整
	cVector2 firePos;

	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
	firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS;
	// レーザー始点エフェクトの作成
	IEffect* effect = em->Create(EFFECT_ID::LASER_START, firePos);
	effect->SetAngle(m_fAngle);
	effect->SetLoop(true);
	// レーザー本体エフェクトの作成
	for (int i = 1;; i++)
	{
		firePos.x = m_vPos.x + cos(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS + cos(DEG_TO_RAD(m_fAngle)) * i * 128;
		firePos.y = m_vPos.y + sin(DEG_TO_RAD(m_fAngle)) * BUL_FIRE_POS + sin(DEG_TO_RAD(m_fAngle)) * i * 128;

		// レーザーの弾の発生
		cBulletManager* bm = (cBulletManager*)FindSibling("BulletManager");
		bm->Create(BULLET_ID::LASER,firePos,m_fAngle,0.0f);

		effect = em->Create(EFFECT_ID::LASER, firePos);
		effect->SetAngle(m_fAngle);
		// レーザーはループエフェクト
		effect->SetLoop(true);

		if (firePos.x + 128 < 0.0f ||
			firePos.x - 128 > game->GetWindowWidth() ||
			firePos.y + 128 < 0.0f ||
			firePos.y - 128 > game->GetWindowHeight())
		{
			// 範囲外に出たら生成をやめる
			break;
		}
	}
}

//==========================================================================================
// 当たり判定処理
//==========================================================================================
void cPlayer::CheckHitEnemy(void)
{
	cEnemyManager* em = (cEnemyManager*)GetParent()->FindSibling("EnemyManager");

	if (em)
	{
		// 当たったら死亡処理
		if (em->CheckHit(m_vPos, m_fDist))
		{
			m_eState = STATE::DEAD;

			m_bVisible = false;
			// エフェクト再生
			cEffectManager* ef = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			ef->Create(EFFECT_ID::BOM, m_vPos);
		}
	}
}