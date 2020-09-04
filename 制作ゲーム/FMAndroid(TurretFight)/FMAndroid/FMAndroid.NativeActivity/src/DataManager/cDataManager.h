#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDataManager.h												*/
/*  @brief		:	�f�[�^�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/01/27													*/
/*																				*/
/*==============================================================================*/

/*  �f�[�^�Ǘ��N���X�̎g����
	�Z���ʎ���
	�P�D�f�[�^�Ǘ��N���X�̃Z�[�u�f�[�^�\���̂̃����o�Ɏ��O�ɕۑ����������e��ǉ����Ă����B

	�Z��������
	�P�D�f�[�^�Ǘ��N���X�̃Z�[�u�f�[�^�ϐ��̒l����������ł���(SetSaveData)
	�Q�D�f�[�^�Ǘ��N���X��ʂ��ăZ�[�u�t�@�C���ɏ�������(SaveFile)

	�Z�ǂݍ���
	�P�D�f�[�^�Ǘ��N���X�ɃZ�[�u�t�@�C����ǂݍ���(LoadFile)
	�Q�D�f�[�^�Ǘ��N���X����Z�[�u�f�[�^�ϐ���ǂݍ���(GetSaveData)
*/

#include "..\BaseObject\IBaseObject.h"

class cDataManager : public IBaseObject
{
public:
	// �j��
	IBaseObject* Finalize(void);

	// �Z�[�u�f�[�^�\����
	// �ۑ��Ώۂ̕��������o�ɒǉ����Ă�������
	struct SaveData
	{
		int Score;

	};

	// �Z�[�u�f�[�^�̎擾
	inline SaveData GetSaveData(void) { return m_SaveData; };
	// �Z�[�u�f�[�^�̐ݒ�
	inline void		SetSaveData(SaveData data) { m_SaveData = data; };

	// �t�@�C���ւ̕ۑ�
	// ���O��SetSaveData�Œ��g��ۑ����Am_SaveData�̒��g���t�@�C���ւƕۑ�����
	// filename : �������݃t�@�C����
	void SaveFile(std::string filename);

	// �t�@�C���̓ǂݍ���
	// �t�@�C������m_SaveData�ւƓǂݍ���
	// �ǂݍ��݌�GetSaveData�Œl���擾����
	// filename : �ǂݍ��݃t�@�C����
	void LoadFile(std::string filename);
private:
	SaveData m_SaveData;		// �Z�[�u�f�[�^�\����


	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cDataManager(void) { };     //  ������̐������֎~
	cDataManager(IBaseObject* parent) {  };
	cDataManager(IBaseObject* parent, const std::string& name) { };
	~cDataManager(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cDataManager(const cDataManager& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cDataManager& operator = (const cDataManager& t) { return *this; };  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cDataManager& GetInstance(void) {
		static cDataManager instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};