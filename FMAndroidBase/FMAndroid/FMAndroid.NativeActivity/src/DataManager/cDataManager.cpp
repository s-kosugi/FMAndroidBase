/*==============================================================================*/
/*																				*/
/*	@file title	:	cDataManager.cpp											*/
/*  @brief		:	�f�[�^�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/01/27													*/
/*																				*/
/*==============================================================================*/

#include "cDataManager.h"
#include <DxLib.h>


//==========================================================================================
// �萔

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cDataManager::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}
//==========================================================================================
// �f�[�^�̕ۑ�
//==========================================================================================
void cDataManager::SaveFile(std::string filename)
{
	FILE* fp;
	char FilePath[256];

	// GetExternalDataPath�Ńf�[�^�Z�[�u�p�̃t�H���_�[�p�X���擾
	GetExternalDataPath(FilePath, sizeof(FilePath));
	strcat(FilePath,"/");

	// �Z�[�u�t�@�C���p�X�𕶎��̌��ɕt����
	strcat(FilePath,filename.c_str());

	// �t�@�C�����������ݐV�K�쐬�ŊJ��
	fp = fopen(FilePath,"wb");

	if (fp != NULL)
	{
		// �f�[�^����������
		fwrite(&m_SaveData, sizeof(m_SaveData), 1, fp);

		fclose(fp);
	}
}
//==========================================================================================
// �f�[�^�̓ǂݍ���
//==========================================================================================
void cDataManager::LoadFile(std::string filename)
{
	FILE* fp;
	char FilePath[256];

	// GetExternalDataPath�Ńf�[�^�Z�[�u�p�̃t�H���_�[�p�X���擾
	GetExternalDataPath(FilePath, sizeof(FilePath));
	strcat(FilePath, "/");

	// �Z�[�u�t�@�C���p�X�𕶎��̌��ɕt����
	strcat(FilePath, filename.c_str());

	// �t�@�C����ǂݍ��ݐV�K�쐬�ŊJ��
	fp = fopen(FilePath, "rb");

	if (fp != NULL)
	{
		// �f�[�^��ǂݍ���
		fread(&m_SaveData, sizeof(m_SaveData), 1, fp);

		fclose(fp);
	}
}
