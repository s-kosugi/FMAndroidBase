/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.cpp													*/
/*  @brief		:	ゲームクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "DrawCtrl\cDrawCtrl.h"
#include "MovieManager/cMovieManager.h"
#include "Input\cControllerManager.h"
#include "Input/Touch/cTouch.h"
#include "SceneManager\cSceneManager.h"
#include "Utility\CsvReader\cCsvReader.h"
#include "DrawCtrl/Camera/cCamera.h"
#include "ScoreManager/cScoreManager.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"

#include "Utility\memory.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif // DEBUG

//==========================================================================================
// 定数
//==========================================================================================
const float             cGame::MAX_DELTA_TIME = 0.16f;		// 最大デルタタイム
const float				cGame::ONE_MILL_SECOND = 1000.0f;	// １秒
const int				cGame::CALC_FRAME_COUNT = 60;		// 平均を計算するフレームの数
const int				cGame::WINDOW_SIZE_X = 1280;		// ウィンドウ幅
const int				cGame::WINDOW_SIZE_Y = 720;			// ウィンドウ高さ

//==========================================================================================
//  初期化
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Game";

	// FPS
	m_nFPS = DEFAULT_FPS;

	// 1フレーム内の更新回数
	m_nOneFrameUpdate = 1;

	// デルタタイム設定
	m_fDeltaTime = 0.0f;
	m_fDeltaTimeScale = 1.0f;

	// 更新フレーム設定
	m_nFrameCount = 0;
	m_nStartTime = 0;
	m_nPrevTime = 0;

	// プレイエリアの設定(UI表示領域があることを想定)
	m_PlayArea = { 0,0,GetWindowWidth(),GetWindowHeight() };

	// 描画操作クラス
	AddChild(&cDrawCtrl::GetInstance());

	// エフェクト管理
	CreateObject<cEffectManager>(this);

	// 動画管理クラス
	AddChild(&cMovieManager::GetInstance());

	// サウンド操作クラス
	AddChild(&cSoundCtrl::GetInstance());
	// 全サウンドの読み込み
	cSoundCtrl::GetInstance().LoadAll();

	// 入力管理クラス
	AddChild(&cTouch::GetInstance());
	//AddChild(&cControllerManager::GetInstance());

	// シーンマネージャークラス
	AddChild(&cSceneManager::GetInstance());

	// Csv読込クラス
	AddChild(&cCsvReader::GetInstance());

	// カメラクラス
	AddChild(&cCamera::GetInstance());

	// スコア管理
	CreateObject<cScoreManager>(this);


#ifdef DEBUG
	// デバッグ機能クラス
	AddChild(&cDebugFunc::GetInstance());
#endif // DEBUG


	IBaseObject::Initialize();

}
//==========================================================================================
//  更新
//==========================================================================================
void cGame::Update(void)
{
	// フレームカウント算出
	CalcFrameCount();

	for (int i = 0; i < m_nOneFrameUpdate; i++)
	{
		// 通常の更新
		IBaseObject::Update();
	}
}
//==========================================================================================
//  描画
//==========================================================================================
void cGame::Draw(void)
{
	cDrawCtrl::GetInstance().Draw();
#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif // DEBUG
}

//==========================================================================================
// 乱数の発生
//==========================================================================================
int cGame::Random(int min, int max)
{
	int range;

	range = max - min;
	return GetRand(range) + min;
}

//==========================================================================================
// 更新するフレームカウントの計算
//==========================================================================================
void cGame::CalcFrameCount(void)
{
	// 現在の時間を取得
	int now_time = GetNowCount();

	// 計算開始時
	if (m_nFrameCount == 0)
	{
		m_nStartTime = now_time;
	}
	// 指定されたフレームカウント時
	else if (m_nFrameCount == CALC_FRAME_COUNT)
	{
		m_nFrameCount = 0;

		m_nStartTime = now_time;
	}

	// フレームカウントを更新
	++m_nFrameCount;

	// 前の処理との時間の差
	int sub_time = now_time - m_nPrevTime;

	// デルタタイムを算出
	m_fDeltaTime = (float)sub_time / ONE_MILL_SECOND;

	// 最大デルタタイムで制限する
	if (m_fDeltaTime > MAX_DELTA_TIME) m_fDeltaTime = MAX_DELTA_TIME;

	// 今の時間を保存
	m_nPrevTime = now_time;
}