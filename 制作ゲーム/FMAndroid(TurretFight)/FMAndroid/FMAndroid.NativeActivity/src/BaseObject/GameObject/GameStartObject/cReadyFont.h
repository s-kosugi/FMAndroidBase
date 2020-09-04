#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cReadyFont.h												*/
/*  @brief		:	Ready文字クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// Ready文字クラス
class cReadyFont : public cSpriteObject
{
public:
	cReadyFont(IBaseObject* parent);

	void Initialize(void);
	void Update(void);
private:
	enum STATE {
		APPEAR,
		DISAPPEAR,
	};

	// 出現状態
	void Appear(void);
	// 消える状態
	void Disappear(void);


	STATE m_eState;


	// 表示優先度
	static const int	PRIORITY;
};
