#pragma once

#include "ManGame.h"

class QuanLyManGame
{
public:
	static void set_ManGame(ManGame *in_BanDo);
	static ManGame* get_ManGame();

private:
	static ManGame *mManGame;
};

