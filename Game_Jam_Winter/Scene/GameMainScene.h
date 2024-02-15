#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Scene/TitleScene.h"

#define PI    3.1415926535897932384626433832795f

class GameMainScene :public SceneBase
{
private:

	int high_score;      //ハイスコア
	int back_ground;     //背景画像
	int barrier_image;   //バリア映像
	int mileage;         //走行距離
	int score;			 //スコア
	int enemy_image[4];  //敵画像
	int enemy_count[4];  //通り過ぎた敵カウント
	int enemy_create_span;	//敵の生成スパンの計測
	int main_song_handle;//ゲームメインで流れるメインの曲用変数

	bool ScoreString;	//加算スコアを描画
	int DrawPlusScoreCount;	//加算したスコアの時間を測るタイマー
	int Biku_Get_SE = 0;
	int Car_Get_SE = 0;
	
	int GameMain_UI_ArrayImg[3];

	int fps = 0;
	int Count = 0;

	int Mae_HappySE;	 //前津ニキが喜ぶ時のSE
	int Mae_BadSE;		 //前津ニキが落ち込む時のSE

	Player* player;      //プレイヤー
	Enemy** enemy;       //敵 ダブルポインタなので配列の先頭のアドレス(場所)を指す
	TitleScene* title;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);
};