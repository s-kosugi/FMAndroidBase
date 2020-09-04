#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlue.h													*/
/*  @brief		:	青い敵クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// 青い敵クラス
class cEnmBlue : public IEnemy
{
public:
	cEnmBlue(IBaseObject* parent);
	~cEnmBlue(void);

	// 初期化
	void Initialize(const cVector2& pos) override;

	// 更新
	void Update(void) override;

	// 通常状態
	void Normal(void) override;

protected:
	void AreaOutAllProc(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 自転速度
	static const float	ROTATE_SPEED;
	
	// 基準距離
	static const int	BASE_DIST;

	// 最小到達時間
	static const int	MIN_TIME;
	
	// 最大到達時間
	static const int	MAX_TIME;
	//--------------------------------------------------------------------------------------------

};
//================================================================================================