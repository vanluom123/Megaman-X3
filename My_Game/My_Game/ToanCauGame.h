#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class ToanCauGame
{
public:
	static HINSTANCE			mTruongHopXuLy;
	static HWND					mCuaSoXuLy;
	static LPDIRECT3DDEVICE9	mThietBi;
	static LPD3DXSPRITE			mXuLyHinhAnh;
	static int					mChieuRong;
	static int					mChieuCao;
public:
	static LPDIRECT3DSURFACE9	mMatSau;
	static bool					mGameDangChay;












/////////////////////////////
/*  Các thủ tục SET - GET  */
//public:
//	static void set_TruongHopXuLy(HINSTANCE in_TruongHopXuLy);
//	static void set_CuaSoXuLy(HWND in_CuaSoXuLy);
//	static void set_ThietBi(LPDIRECT3DDEVICE9 in_ThietBi);
//	static void set_XuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh);
//	static void set_ChieuRong(int in_ChieuRong);
//	static void set_ChieuCao(int in_ChieuCao);
//
//	static HINSTANCE get_TruongHopXuLy();
//	static HWND get_CuaSoXuLy();
//	static LPD3DXSPRITE get_XuLyHinhAnh();
//	static LPDIRECT3DDEVICE9 get_ThietBi();
//	static int get_ChieuRong();
//	static int get_ChieuCao();
};
