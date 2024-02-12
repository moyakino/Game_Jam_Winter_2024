#include "DxLib.h"

#define SCREEN_WIDTH 1280 //横の長さ
#define SCREEN_HEIGHT 720 //縦の長さ

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow)
{
	//タイトル
	SetMainWindowText("Game_Jam_Winter");

	//Log.txtを生成しないようにするjjgjgj
	SetOutApplicationLogValidFlag(FALSE);

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	//描画先を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1) // ＤＸライブラリ初期化処理
	{
		return -1; // エラーが起きたら直ちに終了
	}

	DrawPixel(320, 240, GetColor(255, 255, 255)); // 点を打つ
	WaitKey(); // キー入力待ち
	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}