#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() :background_image(NULL), Help_song_handle(0)
{

}

HelpScene::~HelpScene()
{

}


//初期化処理
void HelpScene::Initialize()
{

	//画像の読み込み
	/*background_image = LoadGraph("Resource/images/Title.bmp");*/
	SetBackgroundColor(50, 50, 50, 0);
	//タイトルに戻る時のSE読み込み
	Help_song_handle = LoadSoundMem("Resource/music/SE/Title_kettei_se.wav");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images.Title.bmpがありません\n");
	}

	if (Help_song_handle == -1)
	{
		//敵用の車の分割読み込み
		throw("Resource/music/SE/Title_kettei_se.wavがありません\n");
	}
}


//更新処理
eSceneType HelpScene::Update()
{
	/*PlaySoundMem(Main_song_handle, DX_PLAYTYPE_BACK, FALSE);*/

	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(Help_song_handle, DX_PLAYTYPE_BACK, FALSE);
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void HelpScene::Draw()const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(30);
	DrawString(20, 120, "ヘルプ画面", 0xffffff,0);
	SetFontSize(24);-
	DrawString(20, 160, "前津ニキの心とお金をコントロールしよう", 0xffffff, 0);
	SetFontSize(30);
	DrawString(20, 250, "基本操作", 0xffffff, 0);
	SetFontSize(24);
	DrawString(20, 280, "・十字ボタンで操作します（左右）", 0xffffff, 0);
	DrawString(20, 310, "・前津ニキの好きなバイクをとるとスコアが加算され\n  貯金が減ります", 0xffffff, 0);
	DrawString(20, 370, "・前津ニキの好きなバイクを逃してしまうと心のゲージが減少します", 0xffffff, 0);
	DrawString(20, 360, "・前津ニキの好きじゃないバイクを取ると心と貯金のゲージが減少します", 0xffffff, 0);
	/*SetFontSize(30);*/
	/*DrawString(20, 400, "色の変え方", 0xffffff, 0);
	SetFontSize(24);
	DrawString(20, 440, "Aボタンで緑", 0x32cd32, 0);
	DrawString(20, 470, "Bボタンで赤", 0xff0000, 0);
	DrawString(200, 440, "Yボタンで黄色", 0xffd700, 0);
	DrawString(200, 470, "Xボタンで青", 0x0000ff, 0);*/

	
	SetFontSize(30);
	DrawString(50, 550, "Bボタンを押してタイトルへ戻る", 0xffffff, 0);
}


//終了処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene()const
{
	return eSceneType::E_HELP;
}