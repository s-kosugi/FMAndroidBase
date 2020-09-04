#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemy.h													*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// 敵ベースクラス
class IEnemy : public cSpriteObject
{
public:
	enum class STATE
	{
		NORMAL,		// 通常状態
		DEAD,		// 死亡状態
	};
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
	};
public:
	IEnemy(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IEnemy(void);

	// 初期化
	void Initialize(void);
	// 初期化
	// pos   : 生成位置
	void Initialize(const cVector2& pos);
	void Update(void);
	IBaseObject* Finalize(void);

	// ダメージ
	void Damage(void);

	// 当たり判定距離の取得
	inline const float GetDist(void) { return m_fDist; };

	// 状態の取得
	inline const STATE GetState(void) { return m_eState; };


protected:
	cVector2	m_vPosUp;		// 移動ベクトル
	float		m_fDist;		// 当たり判定の半径

	STATE		m_eState;		// 状態
	short		m_nHp;			// 耐久力

	short		m_nScore;		// 獲得スコア

	// エリアアウト処理
	virtual void AreaOutLeftProc(void);
	virtual void AreaOutUpProc(void);
	virtual void AreaOutRightProc(void);
	virtual void AreaOutBottomProc(void);
	virtual void AreaOutAllProc(void);

	// 状態別処理
	virtual void Normal(void);
	virtual void Dead(void);

	// 画面外配置処理
	// 戻り値 : 配置方向
	DIRECTION ArrangeOffScreen(void);

	// プレイヤーへ向かう移動量を設定する
	// speed : 基本移動力
	void GotoPlayer(float speed);

	static const int	AREAOUT_ADJUST;	// エリアアウト距離
};
//================================================================================================