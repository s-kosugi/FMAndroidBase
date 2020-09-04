/*==============================================================================*/
/*																				*/
/*	@file title	:	IEffect.cpp													*/
/*  @brief		:	�G�t�F�N�g�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "IEffect.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
IEffect::IEffect(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name) :
	cSpriteObject(parent, object_name, graphic_file_name)
	, m_ptSize({ 64,64 })
	, m_nColNum(1)
	, m_nMaxAnimNum(1)
	, m_nAnimNo(0)
	, m_fFrameTime(0.05f)
	, m_bLoop( false )
{

}

//==========================================================================================
//  ������
//==========================================================================================
void
IEffect::
Initialize(void)
{
	cSpriteObject::Initialize();
}

//==========================================================================================
//  ������
//==========================================================================================
void IEffect::Initialize(const cVector2& pos)
{
	m_vPos = pos;

	Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void IEffect::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("AnimeTimer");
	if (timer && timer->Finished())
	{
		m_nAnimNo++;
		// �A�j���[�V�������ő喇���𒴂�����폜
		if (m_nAnimNo >= m_nMaxAnimNum)
		{
			if( !m_bLoop)
			{
				DeleteObject();
				return;
			}
			else
			{
				// ���[�v�ݒ�̏ꍇ�A�j���[�V������߂�
				m_nAnimNo = 0;
			}
		}
		// �A�j���[�V�����X�V
		UpdateAnime();

		timer->Reset();
	}

	cSpriteObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* IEffect::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
// �A�j���[�V�����ԍ��̃Z�b�g
//==========================================================================================
void IEffect::SetAnimNo(short animeNo)
{

	if (m_nMaxAnimNum > animeNo)
	{
		m_nAnimNo = animeNo;
		// �A�j���[�V�����X�V
		UpdateAnime();
		// �A�j���[�V�������؂�ւ������^�C�}�[�����Z�b�g
		cTimer* timer = (cTimer*)FindChild("AnimeTimer");
		if (timer) timer->Reset();
	}
	else
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("error : SetAnime (MaxAnime < animeNo)");
#endif
	}
}
//==========================================================================================
// �P�t���[��������̎��Ԃ̃Z�b�g
//==========================================================================================
void IEffect::SetFrameTime(float time)
{
}
//==========================================================================================
//  �A�j���[�V���������ݒ�
//==========================================================================================
void IEffect::SetupAnime(const POINT & size, short col, short maxNum, float frameTime)
{
	m_ptSize = size;
	m_nColNum = col;
	m_nMaxAnimNum = maxNum;
	m_fFrameTime = frameTime;

	m_SrcRect = { 0,0,size.x,size.y };
	m_vCenter.x = size.x / 2.0f;
	m_vCenter.y = size.y / 2.0f;

	// �A�j���[�V�����^�C�}�[�쐬
	cTimer* timer = (cTimer*)FindChild("AnimeTimer");
	if (!timer)
	{
		timer = (cTimer*)CreateObject<cTimer>(this, "AnimeTimer");
	}
	timer->Setup(m_fFrameTime);
}

//==========================================================================================
// ���݂̃A�j���[�V�����ԍ��ɃX�v���C�g�����킹��
//==========================================================================================
void IEffect::UpdateAnime(void)
{
	m_SrcRect.left = (m_nAnimNo * m_ptSize.x) % (m_ptSize.x * m_nColNum);
	m_SrcRect.right = m_SrcRect.left + m_ptSize.x;
	m_SrcRect.top = ((m_nAnimNo * m_ptSize.x) / (m_ptSize.x * m_nColNum)) * m_ptSize.y;
	m_SrcRect.bottom = m_SrcRect.top + m_ptSize.y;
}
