#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �v���C���[�N���X
class cPlayer : public cSpriteObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �v���C���[�̈ړ����x
	static const float MOVE_SPEED;

	// �Q�[���J�n�ʒu
	static const float START_POS_X;		
	static const float START_POS_Y;
	// �\���D��x
	static const int	PRIORITY;

	// �v���C���[�̃T�C�Y
	static const short SIZE_X;
	static const short SIZE_Y;

	// �͈͊O����
	void ProcAreaOut( void );

};
//================================================================================================