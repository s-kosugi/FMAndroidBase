#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStageManager.h												*/
/*  @brief		:	ステージ管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "StageID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class IStage;

// ステージ管理クラス
class cStageManager : public IBaseObject
{
public:
	// コンストラクタ
	cStageManager(IBaseObject* pObj);
	~cStageManager(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// ステージ生成
	IStage* Create(STAGE_ID id, const cVector2& pos);

private:
	// ステージオブジェクトのピクセルサイズ
	static const int STAGE_PIXEL_SIZE;
};