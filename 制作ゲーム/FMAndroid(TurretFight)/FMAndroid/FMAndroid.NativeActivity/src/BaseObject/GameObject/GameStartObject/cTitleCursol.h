#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleCursol.h												*/
/*  @brief		:	タイトルカーソルクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// タイトルカーソルクラス
class cTitleCursol : public cSpriteObject
{
public:
	cTitleCursol(IBaseObject* parent);

	void Initialize(void);
	void Update(void);

	// 初期設定
	void Setup(const cVector2& pos, float angle);

private:

	cVector2 m_vOriginPos;

	// 表示優先度
	static const int	PRIORITY;
};
