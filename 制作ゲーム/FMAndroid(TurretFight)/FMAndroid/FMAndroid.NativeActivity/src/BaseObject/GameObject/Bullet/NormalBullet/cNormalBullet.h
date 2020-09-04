#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cNormalBullet.h												*/
/*  @brief		:	通常弾クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\IBullet.h"

//================================================================================================
// 通常弾クラス
class cNormalBullet : public IBullet
{
public:
	cNormalBullet(IBaseObject* parent);
	~cNormalBullet(void);

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================