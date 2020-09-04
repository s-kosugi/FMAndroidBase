/*==============================================================================*/
/*																				*/
/*	@file title	:	cOverTimer.cpp												*/
/*  @brief		:	�Q�[�����C���^�C�}�[UI�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/26													*/
/*																				*/
/*==============================================================================*/

#include "cOverTimer.h"
#include "Utility/Number/cNumber.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cOverTimer::PRIORITY = 500;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cOverTimer::cOverTimer(IBaseObject* parent)
	: cSpriteObject(parent, "OverTimer", "data\\graphic\\timerFrame.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cOverTimer::~cOverTimer(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cOverTimer::Initialize(void)
{
	// ���̃N���X���g�̓^�C�}�[�̃t���[����\������
	SetPriority(PRIORITY);

	// ���̕����̐���
	cNumber* num = CreateDrawObject<cNumber>(this, "MinuteNumber", "data\\graphic\\Number.png");
	num->CreateNumber(2, 0);
	num->SetPriority(PRIORITY + 10);
	// �b�̕����̐���
	num = CreateDrawObject<cNumber>(this, "SecondNumber", "data\\graphic\\Number.png");
	num->CreateNumber(2, 0);
	num->SetPriority(PRIORITY + 10);

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cOverTimer::Update(void)
{
	cNumber* num = (cNumber*)FindChild("MinuteNumber");
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();
	if (num && gm)
	{
		num->SetValue(gm->GetOverTimeMinute());
		cVector2 vec = m_vPos;
		vec.x -= 25.0f;
		vec.y += 0.0f;
		num->SetPos(vec);
	}
	num = (cNumber*)FindChild("SecondNumber");
	if( num)
	{
		num->SetValue(gm->GetOverTimeSecond());
		cVector2 vec = m_vPos;
		vec.x += 50.0f;
		vec.y += 0.0f;
		num->SetPos(vec);
	}

	cSpriteObject::Update();
}