#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// プレイヤークラス
class cPlayer : public cSpriteObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// プレイヤー状態
	enum STATE
	{
		NORMAL,
		LASER,
		DEAD
	};

	// 通常弾速度
	static const float NORMAL_BUL_SPD;
	// 弾発射間隔
	static const float NORMAL_BUL_INTERVAL;
	// 弾発射位置差分
	static const float BUL_FIRE_POS;

	// 表示優先度
	static const int   PRIORITY;


	// 当たり判定の半径
	float m_fDist;

	// プレイヤー状態
	STATE m_eState;

	// 通常状態
	void Normal(void);

	// レーザー発射状態
	void Laser(void);

	// 死亡状態
	void Dead(void);

	// レーザー発射処理
	void StartLaser(void);

	// 敵との当たり判定処理
	void CheckHitEnemy(void);
};
//================================================================================================