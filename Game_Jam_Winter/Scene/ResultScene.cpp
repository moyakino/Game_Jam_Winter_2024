﻿#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

ResultScene::ResultScene() :back_ground(NULL), back_maetu(0), score(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}

}

ResultScene::~ResultScene()
{

}


//初期化処理
void ResultScene::Initialize()
{
	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/リザルト.png");
	back_maetu = LoadGraph("Resource/images/Player/maetu_125_166/透過/maetu_touka_tyokuritu_125_166.png");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/リザルト.pngがありません\n");
	}

	//ファイルオープン
	errno_t rank = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	//対象ファイルから読み込む
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,%2d,%15s \n", &InScore[i], &InRank[i], InName[i], 15);
	}

	//ファイルクローズ
	fclose(fp);

	//ゲーム結果の読み込み
	ReadResultData();
}


//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (InScore[4] < score) {
			return eSceneType::E_RANKING_INPUT;
		}
		else {
			return eSceneType::E_TITLE;
		}
	}

	return GetNowScene();
}


//描画処理
void ResultScene::Draw()const
{
	//背景画像を描画
	DrawRotaGraph(320, 430,0.5f, 0, back_ground, FALSE, FALSE);
	DrawGraph(300, 315, back_maetu, TRUE);

	SetBackgroundColor(255, 255, 255);

	//スコア等表示領域
	//DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);	//緑
	DrawBox(200, 150, 440, 300, GetColor(0, 0, 0), FALSE);//真ん中に出てくる小さい画面の枠線

	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);		//緑

	SetFontSize(30);
	DrawString(125, 550, "Bボタンを押してランキングへ", 0xff0000, 0);

	SetFontSize(20);
	DrawString(270, 170, "ゲーム終了", GetColor(0, 0, 0));
	SetFontSize(16);
	/*DrawString(180, 200, "走行距離         ", GetColor(0, 0, 0));
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);

		DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	}*/
	DrawFormatString(260, 230, 0x000000, "スコア =%6d", score);
}


//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}


//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene()const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%d,\n", &score);

	//避けた数と得点を取得
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%d,\n", &enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);
}
