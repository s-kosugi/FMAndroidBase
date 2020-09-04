/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/18													*/
/*																				*/
/*==============================================================================*/
#include "cPlayer.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "BaseObject/GameObject/Effect/DeadEffect/cDeadEffect.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==================================================================================
// 定数
//==================================================================================
const float cPlayer::REFLECTION = 0.7f;				// 反射減衰率
const float cPlayer::FRICTION = 0.96f;				// 摩擦率
const float cPlayer::SLOPE_MIN_ROUNDDOWN = 0.45f;	// 最小傾き値
const float cPlayer::SENSOR_RATE = 0.05f;			// センサー減衰率
const float cPlayer::DIST = 20.0f;					// 当たり判定の半径
const float cPlayer::DEAD_TIME = 2.0f;				// 死亡状態の時間
const float cPlayer::GOAL_TIME = 2.0f;				// ゴール状態の時間
const int   cPlayer::DEAD_EFFECT_NUM = 12;			// 死亡エフェクトの数
const float cPlayer::DEAD_EFFECT_SPEED = 5.0f;		// 死亡エフェクトの移動スピード
//==================================================================================
// コンストラクタ
//==================================================================================
cPlayer::cPlayer(IBaseObject * parent):
	cSpriteObject(parent,"Player","data\\graphic\\uri_64_64.png")
	, m_vVelocity(0.0f,0.0f)
	, m_eState( STATE::START)
{
}

//==================================================================================
// デストラクタ
//==================================================================================
cPlayer::~cPlayer(void)
{
}

//==================================================================================
// 初期化
//==================================================================================
void cPlayer::Initialize(void)
{
	SetPriority(100);
	m_vVelocity = {0.0f,0.0f};
}

//==================================================================================
// 更新
//==================================================================================
void cPlayer::Update(void)
{
	switch (m_eState)
	{
	case STATE::START:  Start();  break;
	case STATE::NORMAL: Normal(); break;
	case STATE::DEAD:   Dead();   break;
	case STATE::GOAL:   Goal();   break;
	default:					  break;
	}
#ifdef DEBUG
	// 当たり判定の表示
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, DIST, 0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==================================================================================
// 破棄
//==================================================================================
IBaseObject * cPlayer::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==================================================================================
// プレイヤー状態の変更
//==================================================================================
void cPlayer::ChangeState(STATE state)
{
	m_eState = state;
}
//==================================================================================
// 開始状態
//==================================================================================
void cPlayer::Start()
{

}
//==================================================================================
// 通常状態
//==================================================================================
void cPlayer::Normal()
{
	// 加速度センサーの値を取得
	VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_ACCELEROMETER);

	// 移動量として使える値に計算する
	cVector2 velocity = CalcSensorVector(v);

	// 横画面なのでx,yを反転して入れる
	m_vVelocity.x += velocity.y;
	m_vVelocity.y += velocity.x;

	// 摩擦
	m_vVelocity *= FRICTION;

	// 移動値を入れ込む
	m_vPos += m_vVelocity;

	// 時間切れ判定
	CheckTimeOver();

	// 壁判定
	CheckHitWall();

	// キャラクターのアニメーション処理
	Animation();
}
//==================================================================================
// 死亡状態
//==================================================================================
void cPlayer::Dead()
{
	cTimer* timer = (cTimer*)FindChild("DeadTimer");
	if (!timer)
	{
		timer = CreateObject<cTimer>(this,"DeadTimer");
		timer->Setup(DEAD_TIME);

		// タイマーを生成した瞬間に振動をさせる
		Vibrator_vibrate(DEAD_TIME * 1000,128);

		// 死亡状態ではキャラクターを非表示にする
		m_bVisible = false;

		// エフェクト生成
		cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		if (em)
		{
			for (int i = 0; i < DEAD_EFFECT_NUM; i++)
			{
				cDeadEffect* ef = (cDeadEffect*)em->Create(EFFECT_ID::DEAD, m_vPos);
				ef->SetMove(360 / DEAD_EFFECT_NUM * i, DEAD_EFFECT_SPEED);
			}
		}
	}
}
//==================================================================================
// ゴール状態
//==================================================================================
void cPlayer::Goal()
{
	
}
//==================================================================================
// AndroidSensorVectorの戻り値をcPlayerが使える値にする
//==================================================================================
cVector2 cPlayer::CalcSensorVector(VECTOR dxvector)
{
	cVector2 ret;
	// 小さい値を切りすて、傾きが微小な時は動かないようにする
	if (fabs(dxvector.x) <= SLOPE_MIN_ROUNDDOWN)
	{
		dxvector.x = 0.0f;
	}
	if (fabs(dxvector.y) <= SLOPE_MIN_ROUNDDOWN)
	{
		dxvector.y = 0.0f;
	}
	// 力が強すぎるので1/10にする
	dxvector.x *= SENSOR_RATE;
	dxvector.y *= SENSOR_RATE;

	ret.x = dxvector.x;
	ret.y = dxvector.y;

	return ret;
}

//==================================================================================
// 壁判定
//==================================================================================
void cPlayer::CheckHitWall(void)
{
	cGame* gm = (cGame*)GetRoot();
	if (m_vPos.x - GetSpriteSize().x / 2.0f < 0.0f)
	{
		// 壁の内側へ戻す
		m_vPos.x = GetSpriteSize().x / 2.0f;
		// 反射する毎に加速を減衰させる
		m_vVelocity.x = -m_vVelocity.x * REFLECTION;
	}
	if (m_vPos.x + GetSpriteSize().x / 2.0f > gm->GetWindowWidth())
	{
		// 壁の内側へ戻す
		m_vPos.x = gm->GetWindowWidth() - GetSpriteSize().x / 2.0f;
		// 反射する毎に加速を減衰させる
		m_vVelocity.x = -m_vVelocity.x * REFLECTION;
	}
	if (m_vPos.y - GetSpriteSize().y / 2.0f < 0.0f)
	{
		// 壁の内側へ戻す
		m_vPos.y = GetSpriteSize().y / 2.0f;
		// 反射する毎に加速を減衰させる
		m_vVelocity.y = -m_vVelocity.y * REFLECTION;
	}
	if (m_vPos.y + GetSpriteSize().y / 2.0f > gm->GetWindowHeight())
	{
		// 壁の内側へ戻す
		m_vPos.y = gm->GetWindowHeight() - GetSpriteSize().y / 2.0f;
		// 反射する毎に加速を減衰させる
		m_vVelocity.y = -m_vVelocity.y * REFLECTION;
	}
}
//==================================================================================
// 時間切れチェック
//==================================================================================
void cPlayer::CheckTimeOver(void)
{
	cGameMain* gm = (cGameMain*)GetParent();
	if (gm->GetObjectName() == "GameMain")
	{
		// 時間切れだったら死亡にする
		if (gm->GetOverTimeSecond() <= 0 && gm->GetOverTimeMinute() <= 0)
		{
			m_eState = STATE::DEAD;
		}
	}
}
//==================================================================================
// アニメーション処理
//==================================================================================
void cPlayer::Animation(void)
{
	if (m_vVelocity.x < 0)
	{
		m_vScale.x = -1.0f;
	}
	else if (m_vVelocity.x > 0)
	{
		m_vScale.x = 1.0f;
	}
}
