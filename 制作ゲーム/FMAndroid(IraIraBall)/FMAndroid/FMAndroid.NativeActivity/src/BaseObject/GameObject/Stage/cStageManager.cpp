/*==============================================================================*/
/*																				*/
/*	@file title	:	cStageManager.cpp											*/
/*  @brief		:	ステージ管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/08/19													*/
/*																				*/
/*==============================================================================*/

#include "cStageManager.h"
#include "Utility/CsvReader/cCsvReader.h"
#include "IStage.h"
#include "Needle/cNeedle.h"
#include "StageStart/cStageStart.h"
#include "StageGoal/cStageGoal.h"
#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
// 定数
//==========================================================================================
const int cStageManager::STAGE_PIXEL_SIZE = 64;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cStageManager::cStageManager(IBaseObject* pObj)
	:IBaseObject(pObj, "StageManager")
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cStageManager::~cStageManager(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cStageManager::Initialize(void)
{
	IBaseObject::Initialize();

	// ステージ生成
	cCsvReader* csv = CreateObject<cCsvReader>(this);
	csv->LoadFile("data\\csv\\maingame_1.csv");
	for (int i = 0; i < csv->GetRowNum(); i++)
	{
		for (int j = 0; j < csv->GetColNum(); j++)
		{
			Create((STAGE_ID)csv->GetInt(i, j), 
				{ j * STAGE_PIXEL_SIZE + STAGE_PIXEL_SIZE / 2.0f,
				  i * STAGE_PIXEL_SIZE + STAGE_PIXEL_SIZE / 2.0f });
		}
	}
}

//==========================================================================================
// 更新
//==========================================================================================
void cStageManager::Update(void)
{

	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cStageManager::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
// ステージオブジェクト生成
// return : 生成した敵のポインタ 生成されなかった場合はnullptr
//==========================================================================================
IStage* cStageManager::Create(STAGE_ID id, const cVector2& pos)
{
	IStage* pObj = nullptr;
	switch (id)
	{
	case STAGE_ID::EMPTY: break;
	case STAGE_ID::NEEDLE: pObj = CreateObject<cNeedle>(this); break;
	case STAGE_ID::START: pObj = CreateObject<cStageStart>(this); break;
	case STAGE_ID::GOAL: pObj = CreateObject<cStageGoal>(this); break;
	default: break;
	}

	if (pObj)
	{
		pObj->Initialize(pos);
	}

	return pObj;
}