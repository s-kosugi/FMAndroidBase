/*==============================================================================*/
/*																				*/
/*	@file title	:	cEasingTest.cpp												*/
/*  @brief		:	イージング関数テストオブジェクトクラス						*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/18													*/
/*																				*/
/*==============================================================================*/

#include "cEasingTest.h"
#include "..\..\..\cGame.h"

const float cEasingTest::GOAL_POS = 400.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEasingTest::cEasingTest(IBaseObject * parent)
	: cSpriteObject(parent, "EasingTest", "data\\graphic\\enemy_01.png"),
	m_eEasingType(Easing::Type::INQUAD),
	m_dTotalTimer(5.0),
	m_dStartTimer(0.0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEasingTest::~cEasingTest(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEasingTest::Initialize(void)
{
	SetPriority(PRIORITY);
	m_dStartTimer = GetNowCount() / 1000.0;

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEasingTest::Update(void)
{
	double timer = GetNowCount() / 1000.0;

	// 最大値を超えていたら最大値に固定する
	if( m_dTotalTimer < timer - m_dStartTimer) timer = m_dTotalTimer;
	else timer = timer - m_dStartTimer;

	switch (m_eEasingType)
	{
	case Easing::Type::INQUAD: m_vPos.y = Easing::InQuad( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTQUAD: m_vPos.y = Easing::OutQuad( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTQUAD: m_vPos.y = Easing::InOutQuad( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INCUBIC: m_vPos.y = Easing::InCubic( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTCUBIC: m_vPos.y = Easing::OutCubic( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTCUBIC: m_vPos.y = Easing::InOutCubic( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INQUART: m_vPos.y = Easing::InQuart( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTQUART: m_vPos.y = Easing::OutQuart( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTQUART: m_vPos.y = Easing::InOutQuart( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INQUINT: m_vPos.y = Easing::InQuint( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTQUINT: m_vPos.y = Easing::OutQuint( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTQUINT: m_vPos.y = Easing::InOutQuint( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INSINE: m_vPos.y = Easing::InSine( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTSINE: m_vPos.y = Easing::OutSine( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTSINE: m_vPos.y = Easing::InOutSine( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INEXP: m_vPos.y = Easing::InExp( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTEXP: m_vPos.y = Easing::OutExp( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTEXP: m_vPos.y = Easing::InOutExp( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INCIRC: m_vPos.y = Easing::InCirc( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTCIRC: m_vPos.y = Easing::OutCirc( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTCIRC: m_vPos.y = Easing::InOutCirc( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INBACK: m_vPos.y = Easing::InBack( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTBACK: m_vPos.y = Easing::OutBack( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTBACK: m_vPos.y = Easing::InOutBack( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::OUTBOUNCE: m_vPos.y = Easing::OutBounce( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INBOUNCE: m_vPos.y = Easing::InBounce( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::INOUTBOUNCE: m_vPos.y = Easing::InOutBounce( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	case Easing::Type::LINEAR: m_vPos.y = Easing::Linear( (float)timer, (float)m_dTotalTimer, GOAL_POS, 0.0f); break;
	default: break;
	}
	cSpriteObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEasingTest::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// イージングタイプのセット
//==========================================================================================
void cEasingTest::SetEasingType(Easing::Type type)
{
	m_eEasingType = type;
}
