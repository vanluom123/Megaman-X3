#pragma once

#include "MapReader/Tmx.h.in"
#include "HinhAnh.h"

// Là 1 lớp giao diện, sử dụng để gọi đến Màn Game thực sự
class ManGame
{
public:
	virtual void TaiDuLieu() = 0;
	virtual void CapNhat(float in_tg) = 0;
	virtual void Ve() = 0;
	virtual void OnKeyDown(int in_KeyCode) = 0;
	virtual void OnKeyUp(int in_KeyCode) = 0;
	virtual void OnMouseDown(float in_x, float in_y) = 0;

	D3DCOLOR get_MauNen()
	{
		return mMauNen;
	}

protected:
	D3DCOLOR mMauNen;
	
	Tmx::Map *mBanDo;
	int mChieuRong;
	int mChieuCao;
	int mChieuRongTile;
	int mChieuCaoTile;
	//std::map<int, HinhAnh*> mDanhSachTileset;
};


