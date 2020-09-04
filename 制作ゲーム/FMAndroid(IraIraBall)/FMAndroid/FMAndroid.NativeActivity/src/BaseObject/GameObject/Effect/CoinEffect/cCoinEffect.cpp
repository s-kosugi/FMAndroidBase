/*==============================================================================*/
/*																				*/
/*	@file title	:	cCoinEffect.cpp												*/
/*  @brief		:	�R�C���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/09/02													*/
/*																				*/
/*==============================================================================*/

#include "cCoinEffect.h"
#include "cGame.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cCoinEffect::PRIORITY = 400;
const float cCoinEffect::MAX_SPEED = 20.0f;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cCoinEffect::cCoinEffect(IBaseObject * parent)
	: IEffect(parent, "CoinEffect", "data\\graphic\\coin.png")
	, m_vVelocity()
	, m_fScaleCurve( 0.0f )
{
	SetPriority(PRIORITY);
}

//==========================================================================================
// ������
//==========================================================================================
void cCoinEffect::Initialize(const cVector2 & pos)
{
	// �A�j���[�V�����������g��Ȃ����߃Z�b�g���Ȃ�
	// �A�j���[�V���������ݒ�
	//SetupAnime({ 128,128 }, 4, 23, 0.02f);

	IEffect::Initialize(pos);
}
//==========================================================================================
// �X�V
//==========================================================================================
void cCoinEffect::Update(void)
{
	cGame* game = (cGame*)GetRoot();

	// �d�͉����x������
	m_vVelocity.y += 0.45f;

	//�ő呬�x
	if (m_vVelocity.y >= MAX_SPEED)
	{
		m_vVelocity.y = MAX_SPEED;
	}

	//
	m_fScaleCurve += 5.0f;
	m_vScale.x = sin(DEG_TO_RAD(m_fScaleCurve));

	m_vPos += m_vVelocity;

	// ��ʊO����
	if (game->GetWindowHeight() < m_vPos.y + GetSpriteSize().y / 2.0f)
	{
		DeleteObject();
	}

	IEffect::Update();
}