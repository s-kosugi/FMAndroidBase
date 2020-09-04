#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IBullet.h													*/
/*  @brief		:	弾ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// 弾ベースクラス
class IBullet : public cSpriteObject
{
public:
	IBullet(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IBullet(void);

	// 初期化
	void Initialize(void);
	void Initialize(const cVector2& pos);
	//------------------------------------------------------------------
	// 初期化
	// pos   : 発生位置
	// angle : 発射角度(DEGREE)
	// speed : 弾速
	void Initialize(const cVector2& pos,float angle,float speed);

	void Update(void);
	IBaseObject* Finalize(void);

	// 無敵フラグの設定
	inline void SetInvincible(bool flag) { m_bInvincible = flag; };

	// 当たり判定の半径の取得
	inline const float GetDist(void) { return m_fDist; };
	// 無敵フラグの取得
	inline const bool  IsInvincivble(void) { return m_bInvincible; };

protected:
	cVector2	m_vPosUp;		// 移動ベクトル
	float		m_fDist;		// 当たり判定の半径
	bool		m_bInvincible;	// 無敵フラグ

	// 当たり判定処理
	void CheckHitEnemy(void);

	// エリアアウト処理
	void AreaOutLeftProc(void);
	void AreaOutUpProc(void);
	void AreaOutRightProc(void);
	void AreaOutBottomProc(void);
	void AreaOutAllProc(void);

	static const int	AREAOUT_ADJUST;	// エリアアウト距離
};
//================================================================================================