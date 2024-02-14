#pragma once

#include "SceneBase.h"

class ResultScene :public SceneBase
{
private:
	int back_ground;      //背景画像
	int score;            //スコア
	int enemy_count[3];   //敵のカウント
	int enemy_image[3];   //敵画像

	//int score[6];       //スコアデータ
	//int rank[6];        //ランクデータ
	//char name[6][15];   //名前データ

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();
};

