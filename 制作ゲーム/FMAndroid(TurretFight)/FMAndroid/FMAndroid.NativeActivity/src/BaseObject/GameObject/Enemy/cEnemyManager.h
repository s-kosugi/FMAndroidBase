#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.h												*/
/*  @brief		:	敵管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EnemyID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class IEnemy;

// 敵管理クラス
class cEnemyManager : public IBaseObject
{
public:
	// コンストラクタ
	cEnemyManager(IBaseObject* pObj);
	~cEnemyManager(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 弾生成
	IEnemy* Create(ENEMY_ID id, const cVector2& pos);

	// 当たり判定チェック
	// pos : 判定をするオブジェクトの位置
	// dist : 判定をするオブジェクトの半径
	// ret : true 当たった  false 当たってない
	bool CheckHit(const cVector2& pos, float dist);

private:

	// 初期出現間隔
	static const int DEFAULT_POP_INTERVAL;
	// 難易度による敵の出現頻度の倍率
	static const int DIFFICULT_POP_RATE;


	// 敵の出現制御用フレームカウンター
	int m_nPopCounter;


	// 敵の出現制御
	void ControlPop(void);

};