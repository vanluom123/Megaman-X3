#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "KieuDuLieu.h"

class HinhAnh
{
public:
	HinhAnh(const char* in_DuongDan, const D3DCOLOR &in_Color = NULL);
	~HinhAnh();

// FUNCTION
	void Ve(const D3DCOLOR &in_SubColor = D3DCOLOR_ARGB(255, 255, 255, 255));

// INFORMATION
protected:

	D3DXIMAGE_INFO          mThongTinHinhAnh;
	LPDIRECT3DTEXTURE9      mKetCauHinhAnh;		// tải hình ảnh vào đây
	D3DXMATRIX              mMaTran;			// ma trận hỗ trợ cho các phép hình học

	Vec2					mToaDo;
	int						mChieuRong; 
	int						mChieuCao;			// kích thước của Kết Cấu Hình Ảnh
	HCN						mHCN;				// hình chữ nhật cắt từ Kết Cấu Hình Ảnh
	Vec2					mTiLe;
	bool					mLatTheoChieuNgang;
	bool                    mLatTheoChieuDoc;
	float					mGocXoayHinh;
	Vec2					mDoDoi;				// Dời hình ảnh theo vị trí hình ảnh + độ dời






// SUB-FUNCTION
public:
	void set_ToaDo(const Vec2& in_ToaDo);
	void set_ChieuRong(int in_ChieuRong);
	void set_ChieuCao(int in_ChieuCao);
	void set_HCN(const HCN& in_HCN);
	void set_TiLe(const Vec2& in_TiLe);
	void set_LatTheoChieuNgang(bool in_Co);
	void set_LatTheoChieuDoc(bool in_Co);
	void set_GocXoayHinh(float in_GocXoay);
	void set_DoDoi(const Vec2& in_DoDoi);

	Vec2 get_ToaDo() const;
	int get_ChieuRong() const;
	int get_ChieuCao() const;
	Vec2 get_TiLe() const;
	bool get_LatTheoChieuNgang() const;
	bool get_LatTheoChieuDoc() const;
	float get_GocXoayHinh() const;
	Vec2 get_DoDoi() const;
};

