#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
private:
	bool is_car;        //車か？
	bool is_bike;       //バイクか？
	int image;          //画像データ
	int maetu[3];
	int nowMaetu;
	Vector2D location;  //位置座標
	Vector2D box_size;  //当たり判定の大きさ
	float angle;        //角度
	float speed;        //速さ
	float hp;           //体力(心)
	float tyokin;       //貯金

	int maetuCount;       //ガッカリタイム
	int keyCount;       //入力クールタイム

public:
	Player();
	~Player();

	void Initialize();   //初期化処理
	void Update();       //更新処理
	void Draw();         //描画処理
	void Finalize();     //終了時処理

public:
	void SetIsCar(bool flg);        //車フラグ設定
	void SetIsBike(bool flg);       //バイクフラグ設定
	void DecreaseHp(float value);    //体力(心)減少処理
	void DecreaseTyokin(float value);//貯金減少処理
	Vector2D GetLocation()const;     //位置座標取得
	Vector2D GetBoxSize()const;      //当たり判定の大きさ取得
	float GetSpeed()const;           //速さ取得処理
	float GetTyokin()const;           //貯金取得
	float GetHp()const;              //体力取得
private:
	void Movement();                 //移動処理
};

