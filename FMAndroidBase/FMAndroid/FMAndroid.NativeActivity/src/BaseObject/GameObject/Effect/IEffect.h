#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEffect.h													*/
/*  @brief		:	�G�t�F�N�g���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �G�t�F�N�g���N���X
class IEffect : public cSpriteObject
{
public:
	IEffect(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);

	// ������
	void Initialize(void);
	void Initialize(const cVector2& pos);

	void Update(void);
	IBaseObject* Finalize(void);

	inline POINT GetAnimeSize(void) { return m_ptSize; };
	inline short GetColumnNum(void) { return m_nColNum; };
	inline short GetRowNum(void) { return m_nMaxAnimNum / m_nColNum; };
	inline short GetMaxAnimNum(void) { return m_nMaxAnimNum; };
	inline short GetAnimNo(void) { return m_nAnimNo; };
	inline float GetFrameTime(void) { return m_fFrameTime; };

	void SetAnimNo(short animeNo);
	void SetFrameTime(float time);


	// �A�j���[�V�����̐ݒ�
	void SetupAnime(const POINT& size, short col, short maxNum, float frameTime);

protected:
	POINT		m_ptSize;		// �P�A�j���[�V����������̑傫��
	short		m_nColNum;		// ����̖���
	short		m_nMaxAnimNum;	// �ő�A�j���[�V��������
	short		m_nAnimNo;		// ���݂̃A�j���[�V�����ԍ�
	float		m_fFrameTime;	// �P�t���[��������̎���

	// ���݂̃A�j���[�V�����ԍ��ɃX�v���C�g�����킹��
	void UpdateAnime(void);
};
//================================================================================================