#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cReadyFont.h												*/
/*  @brief		:	Ready�����N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// Ready�����N���X
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

	// �o�����
	void Appear(void);
	// ��������
	void Disappear(void);


	STATE m_eState;


	// �\���D��x
	static const int	PRIORITY;
};
