#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletManager.h											*/
/*  @brief		:	�e�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "BulletID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class IBullet;

// �e�Ǘ��N���X
class cBulletManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cBulletManager(IBaseObject* pObj);
	~cBulletManager(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �e����
	// id : �e�̎��
	// pos : �e�̐����ʒu
	// angle : �e�̔��ˊp�x
	// speed : �e�̈ړ����x
	IBullet* Create(BULLET_ID id,const cVector2& pos,float angle,float speed);

private:

};