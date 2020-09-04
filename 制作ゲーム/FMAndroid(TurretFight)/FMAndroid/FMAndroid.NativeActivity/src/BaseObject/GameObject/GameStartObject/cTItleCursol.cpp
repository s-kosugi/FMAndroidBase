/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleCursol.cpp											*/
/*  @brief		:	�^�C�g���J�[�\���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cTitleCursol.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cTitleCursol::PRIORITY = 1000;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cTitleCursol::cTitleCursol(IBaseObject * parent)
	: cSpriteObject(parent, "TitleCursol", "data\\graphic\\cursol.png")
{
}
//==========================================================================================
// ������
//==========================================================================================
void cTitleCursol::Initialize(void)
{
	cSpriteObject::Initialize();

	cTimer* timer = CreateObject<cTimer>(this, "CursolTimer");
	timer->Setup(1.5f);

	SetPriority(PRIORITY);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cTitleCursol::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("CursolTimer");
	if (timer)
	{
		if (timer->Finished()) timer->Reset();

		float addPos;
		addPos = fabs(sin(DEG_TO_RAD(Easing::Linear(timer->GetTime(), timer->GetLimit(), 360.0f, 0.0f))) * 30.0f);
		if (m_fAngle > 0) addPos = -addPos;

		m_vPos.x = m_vOriginPos.x + addPos;
	}

	cSpriteObject::Update();
}

//==========================================================================================
// �����ݒ�
//==========================================================================================
void cTitleCursol::Setup(const cVector2 & pos, float angle)
{
	m_vOriginPos = m_vPos = pos;
	m_fAngle = angle;
}
