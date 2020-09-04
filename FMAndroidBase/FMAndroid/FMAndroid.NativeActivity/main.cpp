#include "DxLib.h"
#include "cGame.h"
#include "DrawCtrl\cDrawCtrl.h"

void MainLoop(void);

// プログラムは android_main から始まります
int android_main(void)
{

	// ウィンドウタイトル
	//SetWindowText("FMGameBase");

	// 画面サイズとカラービット数の指定
	SetGraphMode(cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight(), 32);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
		return -1;			// エラーが起きたら直ちに終了

	//描画先を裏画面に設定(ダブルバッファ)
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;

	// ウィンドウが非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);

	// 描画リストの生成、初期化
	cDrawCtrl::GetInstance().ClearDrawList();

	// ゲームクラスの作成
	cGame& game = cGame::GetInstance();

	// 初期化
	game.Initialize();
#ifdef DEBUG
	//cDebugFunc::GetInstance().PushDebugLog("ShaderVersion = " + std::to_string(GetValidShaderVersion()));
	//cDebugFunc::GetInstance().PushDebugLog("MultiDrawScreenNum = " + std::to_string(GetMultiDrawScreenNum()));
#endif
	// メインループ
	MainLoop();

	// 破棄
	game.Finalize();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
//==========================================================================================
// メインループ
//==========================================================================================
void MainLoop(void)
{
	cGame& game = cGame::GetInstance();

	for (;;) {
		int StartTime;

		// 計測開始時刻を保存
		StartTime = GetNowCount();

		// 画面のクリア
		ClearDrawScreen();
		// ゲームの更新
		game.Update();
		// 描画
		game.Draw();

		// 画面を更新(垂直同期+裏画面の内容を表画面にコピー)
		ScreenFlip();

		// メッセージ処理
		if (ProcessMessage() != 0)
			return;

		// 1/60秒を越えるまで待機させる
		while (GetNowCount() < StartTime + 1000 / (int)game.GetFPS());
	}
}