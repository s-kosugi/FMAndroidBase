#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.h												*/
/*  @brief		:	�G�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "EnemyID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class IEnemy;

// �G�Ǘ��N���X
class cEnemyManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cEnemyManager(IBaseObject* pObj);
	~cEnemyManager(void);

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �e����
	IEnemy* Create(ENEMY_ID id, const cVector2& pos);

	// �����蔻��`�F�b�N
	// pos : ���������I�u�W�F�N�g�̈ʒu
	// dist : ���������I�u�W�F�N�g�̔��a
	// ret : true ��������  false �������ĂȂ�
	bool CheckHit(const cVector2& pos, float dist);

private:

	// �����o���Ԋu
	static const int DEFAULT_POP_INTERVAL;
	// ��Փx�ɂ��G�̏o���p�x�̔{��
	static const int DIFFICULT_POP_RATE;


	// �G�̏o������p�t���[���J�E���^�[
	int m_nPopCounter;


	// �G�̏o������
	void ControlPop(void);

};