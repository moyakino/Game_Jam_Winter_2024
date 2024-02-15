#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define WIDTH 640.0f    //画面サイズ
#define HEIGHT 600.0f   // 画面サイズ
#define KEYTIME 8       //横移動の入力CT　小さい程速めに入力できる

#define MAXHP 5000      //最大HP
#define MAXTYOKIN 20000 //最大貯金額
#define MAETUTIME 8     //前津ニキのアニメーション変更　小さい程すぐ終わる

Player::Player() :is_car(false), is_bike(false), image(NULL), nowMaetu(0),
location(0.0f), box_size(0.0f), angle(0.0f),
speed(0.0f), hp(0.0f), tyokin(0.0f), HitFrame(0), keyCount(0)
{

}


Player::~Player()
{

}


//初期化処理
void Player::Initialize()
{
	is_car = true;
	is_bike = true;
	location = Vector2D(190.0f, HEIGHT - 100.0f);
	box_size = Vector2D(31.0f, 77.7f);
	speed = 3.0f;
	hp = MAXHP;
	tyokin = MAXTYOKIN;

	nowMaetu = 0;
	maetuCount = 0;
	keyCount = 0;
	HitFrame = 0;

	//画像の読み込み
	//image = LoadGraph("Resource/images/Player/maetu_125_166/透過/maetu_touka_tyokuritu_125_166.png");
	LoadDivGraph("Resource/images/Player.png", 3, 3, 1, 125, 166, maetu);

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	////操作不可状態であれば、自身を回転させる
	//if (!is_active)
	//{
	//	angle += DX_PI_F / 24.0f;
	//	//speed = 1.0f;
	//	if (angle >= DX_PI_F * 4.0f)
	//	{
	//		is_active = true;
	//	}
	//	return;
	//}

	//車であれば、自身をガッカリさせる
	if (!is_car)
	{
		maetuCount++;
		nowMaetu = 2;
		if (MAETUTIME <= maetuCount)
		{
			nowMaetu = 0;
			is_car = true;
			maetuCount = 0;
		}
		return;

		//nowMaetu = 2;
		//is_car = TRUE;
		//HitFrame = 60;
		//return;
	}

	//HitFrame--;
	//if (HitFrame < 0) {
	//	HitFrame = 0;
	//	nowMaetu = 0;
	//}

	//バイクであれば、自身を喜ばせる
	if (!is_bike)
	{
		maetuCount++;
		nowMaetu = 1;
		if (MAETUTIME <= maetuCount)
		{
			nowMaetu = 0;
			is_bike = true;
			maetuCount = 0;
		}
		return;
	}

	//移動処理
	Movement();
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;
	keyCount++;

	//十字移動処理
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT)
		&& KEYTIME <= keyCount)
	{
		move += Vector2D(-130.0f, 0.0f);
		keyCount = 0;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT)
		&& KEYTIME <= keyCount)
	{
		move += Vector2D(130.0f, 0.0f);
		keyCount = 0;
	}
	location += move;

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= WIDTH - 180.0f) ||
		(location.y < box_size.y) || (location.y >= HEIGHT - box_size.y))
	{
		location -= move;
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	//DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	switch (nowMaetu)
	{
	case 0:
		DrawGraph(location.x - 60.0f, location.y - 85.0f, maetu[0], TRUE);
		break;

	case 1:
		DrawGraph(location.x - 60.0f, location.y - 85.0f, maetu[1], TRUE);
		break;

	case 2:
		//if ((HitFrame / 10) % 2 == 0)
		//{
			DrawGraph(location.x - 60.0f, location.y - 85.0f, maetu[2], TRUE);
		//}
		break;

	default:
		break;
	}

	//当たり判定用
	/*DrawBox(location.x - box_size.x, location.y - box_size.y, 
		location.x + box_size.x, location.y + box_size.y, 0xffffff, FALSE);*/
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);
}

//状態設定処理
void Player::SetIsCar(bool flg)
{
	this->is_car = flg;
}

//状態設定処理
void Player::SetIsBike(bool flg)
{
	this->is_bike = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//貯金減少処理
void Player::DecreaseTyokin(float value)
{
	this->tyokin += value;
}

//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}

//体力(心)取得処理
float Player::GetHp()const
{
	return this->hp;
}

//貯金取得処理
float Player::GetTyokin()const
{
	return this->tyokin;
}