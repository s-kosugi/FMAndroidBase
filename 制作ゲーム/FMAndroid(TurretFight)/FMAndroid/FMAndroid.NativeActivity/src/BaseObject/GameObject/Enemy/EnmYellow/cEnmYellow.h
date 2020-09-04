#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmYellow.h												*/
/*  @brief		:	黄色い敵クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// 黄色い敵クラス
class cEnmYellow : public IEnemy
{
public:
	cEnmYellow(IBaseObject* parent);
	~cEnmYellow(void);

	// 初期化
	void Initialize(const cVector2& pos) override;

	// 更新
	void Update(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 基本移動力
	static const float	BASE_SPEED;

	// 自転速度
	static const float	ROTATE_SPEED;

	//--------------------------------------------------------------------------------------------

	// 出現方向
	IEnemy::DIRECTION m_ePopDirection;
};
//================================================================================================