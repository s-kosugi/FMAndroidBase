#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStageStart.h												*/
/*  @brief		:	ステージ開始オブジェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "..\IStage.h"

//================================================================================================
// ステージ開始オブジェクトクラス
class cStageStart : public IStage
{
public:
	cStageStart(IBaseObject* parent);
	~cStageStart(void);

	// 初期化
	void Initialize(const cVector2& pos) override;

	// 更新
	void Update(void) override;
protected:
	// プレイヤー衝突時の処理
	void HitPlayer(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================