#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IStage.h													*/
/*  @brief		:	ステージベースクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// ステージベースクラス
class IStage : public cSpriteObject
{
public:
	IStage(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IStage(void);

	// 初期化
	void Initialize(void);
	// 初期化
	// pos   : 生成位置
	void Initialize(const cVector2& pos);
	void Update(void);
	IBaseObject* Finalize(void);

	// 当たり判定の半径の取得
	const inline float GetDist(void) { return m_fDist; };

protected:
	// プレイヤーと衝突したかどうかのチェック
	void CheckPlayerHit(void);

	// プレイヤー衝突時の処理
	virtual void HitPlayer(void);

	// 当たり判定の半径
	float m_fDist;
};
//================================================================================================