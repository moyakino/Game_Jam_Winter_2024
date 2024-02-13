#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
private:
	int image;          //画像データ
	int aura[4];        //画像データ
	int nowAura;        //今のオーラ
	int nowCombo[3];
	int combo1;
	int combo10;
	int combo100;
	int FontHandle;
	Vector2D location;  //位置座標
	Vector2D box_size;  //当たり判定の大きさ
	float angle;        //角度
	float speed;        //速さ
	int keyCount;       //入力クールタイム

public:
	Player();
	~Player();

	void Initialize();   //初期化処理
	void Update();       //更新処理
	void Draw();         //描画処理
	void Finalize();     //終了時処理

public:
	Vector2D GetLocation()const;     //位置座標取得
	Vector2D GetBoxSize()const;      //当たり判定の大きさ取得
	float GetSpeed()const;           //速さ取得処理
private:
	void Movement();                 //移動処理
};

