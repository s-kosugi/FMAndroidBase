#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/18													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

// プレイヤークラス
class cPlayer : public cSpriteObject
{
public:
	// プレイヤー状態
	enum class STATE {
		START,
		NORMAL,
		DEAD,
		GOAL,
	};

	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// プレイヤー状態の変更
	void ChangeState(STATE state);

	// 状態の取得
	const inline STATE GetState(void) { return m_eState; };

	// 当たり判定の半径の取得
	const inline float GetDist(void) { return DIST; };

private:
	// 壁当たりの速度減衰率
	static const float REFLECTION;
	// 摩擦率
	static const float FRICTION;
	// 小さい傾き値の切り捨て
	static const float SLOPE_MIN_ROUNDDOWN;
	// センサーの値の大きさを使う大きさにあわせる
	static const float SENSOR_RATE;
	// 当たり判定の半径
	static const float DIST;
	// 死亡状態の時間
	static const float DEAD_TIME;
	// 死亡エフェクトの玉の数
	static const int DEAD_EFFECT_NUM;
	// 死亡エフェクトの移動スピード
	static const float DEAD_EFFECT_SPEED;
	// ゴール状態の時間
	static const float GOAL_TIME;

	// 速度
	cVector2 m_vVelocity;

	// プレイヤー状態
	STATE m_eState;


	// 開始状態の処理
	void Start();
	// 通常状態処理
	void Normal();
	// 死亡状態
	void Dead();
	// ゴール状態
	void Goal();


	// AndroidSensorVectorの戻り値をcPlayerが使える値にする
	cVector2 CalcSensorVector(VECTOR dxvector);

	// 壁判定
	void CheckHitWall(void);

	// 時間切れチェック
	void CheckTimeOver(void);

	// アニメーション処理
	void Animation(void);
};