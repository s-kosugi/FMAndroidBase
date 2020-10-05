#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartFont.h												*/
/*  @brief		:	�X�^�[�g�̕����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// �X�^�[�g�̕����N���X
class cStartFont : public cSpriteObject
{
public:
	cStartFont(IBaseObject* parent);
	~cStartFont(void);

	void Initialize(void) override;
	void Update(void) override;

private:

	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;
	static const float  MOVE_TIME;
	static const float  FADE_TIME;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================