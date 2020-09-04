#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.h											*/
/*  @brief		:	弾管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "BulletID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class IBullet;

// 弾管理クラス
class cBulletManager : public IBaseObject
{
public:
	// コンストラクタ
	cBulletManager(IBaseObject* pObj);
	~cBulletManager(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 弾生成
	// id : 弾の種類
	// pos : 弾の生成位置
	// angle : 弾の発射角度
	// speed : 弾の移動速度
	IBullet* Create(BULLET_ID id,const cVector2& pos,float angle,float speed);

private:

};