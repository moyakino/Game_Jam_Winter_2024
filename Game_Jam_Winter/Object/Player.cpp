#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define WIDTH 640.0f
#define HEIGHT 600.0f
#define KEYTIME 8

#define MAXHP 1000
#define MAXTYOKIN 20000
#define MAETUTIME 60

Player::Player() :is_active(false), image(NULL), nowMaetu(0), 
location(0.0f),box_size(0.0f), angle(0.0f), 
speed(0.0f), hp(0.0f), tyokin(0.0f), keyCount(0)
{

}


Player::~Player()
{

}


//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(190.0f, HEIGHT - 100.0f);
	box_size = Vector2D(31.0f, 77.7f);
	speed = 3.0f;
	hp = MAXHP;
	tyokin = MAXTYOKIN;

	nowMaetu = 0;
	maetuCount = 0;
	keyCount = 0;

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

	//操作不可状態であれば、自身をガッカリさせる
	if (!is_active)
	{
		maetuCount++;
		nowMaetu = 1;
		if (MAETUTIME <= maetuCount)
		{
			nowMaetu = 0;
			is_active = true;
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
		DrawGraph(location.x - 60.0f, location.y - 85.0f, maetu[2], TRUE);
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
void Player::SetActive(bool flg)
{
	this->is_active = flg;
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