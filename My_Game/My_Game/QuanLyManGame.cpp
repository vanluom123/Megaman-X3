#include "QuanLyManGame.h"

ManGame* QuanLyManGame::mManGame = nullptr;

void QuanLyManGame::set_ManGame(ManGame * in_BanDo)
{
	delete mManGame;
	mManGame = in_BanDo;
}


ManGame * QuanLyManGame::get_ManGame()
{
	return mManGame;
}