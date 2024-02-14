﻿#pragma once

#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:

private:

	int background_image;
	int kuruma_image;
	int state_image;
	int help_image;
	int ranking_image;
	int end_image;
	int cursor_image;
	int menu_cursor;
	int Title_Bgm;
	int cursor_down_se;
	int cursor_up_se;
	int mae2_image;
	

public:

	int Mae_se;

	TitleScene();
	virtual ~TitleScene();

	int Title_SE();

	virtual void  Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

