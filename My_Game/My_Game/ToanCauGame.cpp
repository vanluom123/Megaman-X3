#include "ToanCauGame.h"

HINSTANCE ToanCauGame::mTruongHopXuLy = NULL;
HWND ToanCauGame::mCuaSoXuLy = NULL;
LPD3DXSPRITE ToanCauGame::mXuLyHinhAnh = NULL;
LPDIRECT3DDEVICE9 ToanCauGame::mThietBi = NULL;
int ToanCauGame::mChieuRong = 254;
int ToanCauGame::mChieuCao = 220;
IDirect3DSurface9* ToanCauGame::mMatSau = nullptr;
bool ToanCauGame::mGameDangChay = true;

//void ToanCauGame::set_TruongHopXuLy(HINSTANCE in_TruongHopXuLy)
//{
//	mTruongHopXuLy = in_TruongHopXuLy;
//}
//
//HINSTANCE ToanCauGame::get_TruongHopXuLy()
//{
//	return mTruongHopXuLy;
//}
//
//void ToanCauGame::set_CuaSoXuLy(HWND in_CuaSoXuLy)
//{
//	mCuaSoXuLy = in_CuaSoXuLy;
//}
//
//HWND ToanCauGame::get_CuaSoXuLy()
//{
//	return mCuaSoXuLy;
//}
//
//void ToanCauGame::set_XuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh)
//{
//	mXuLyHinhAnh = in_XuLyHinhAnh;
//}
//
//LPD3DXSPRITE ToanCauGame::get_XuLyHinhAnh()
//{
//	return mXuLyHinhAnh;
//}
//
//void ToanCauGame::set_ThietBi(LPDIRECT3DDEVICE9 in_ThietBi)
//{
//	mThietBi = in_ThietBi;
//}
//
//LPDIRECT3DDEVICE9 ToanCauGame::get_ThietBi()
//{
//	return mThietBi;
//}
//
//void ToanCauGame::set_ChieuRong(int in_ChieuRong)
//{
//	mChieuRong = in_ChieuRong;
//}
//
//int ToanCauGame::get_ChieuRong()
//{
//	return mChieuRong;
//}
//
//void ToanCauGame::set_ChieuCao(int in_ChieuCao)
//{
//	mChieuCao = in_ChieuCao;
//}
//
//int ToanCauGame::get_ChieuCao()
//{
//	return mChieuCao;
//}
