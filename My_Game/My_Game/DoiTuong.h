#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "KieuDuLieu.h"

// là 1 lớp giao diện, dùng để trỏ đến Đối Tượng thực sự (ngoại trừ các Đối Tượng tĩnh)
class DoiTuong
{
public:
	DoiTuong(const Vec2& in_ToaDo, const Vec2& in_VanToc,
		int in_ChieuRong, int in_ChieuCao);
	virtual void CapNhat(float in_tg) = 0;
	virtual void Ve(const Vec2& in_DoDoi) = 0; // Độ dời phụ thuộc Camera hiện tại
	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong) = 0;
	virtual void CapNhat(float in_tg, const DoiTuong *in_DoiTuong){}

protected:
	eLoaiDoiTuong mLoaiDoiTuong;
	eTrangThai mTrangThai;
	Vec2 mToaDo;
	Vec2 mVanToc;
	int mChieuRong;
	int mChieuCao;










/////////////////////////////
/*  Các thủ tục SET - GET  */
public:
	void set_ToaDo(Vec2 in_ToaDo);
	void set_VanToc(Vec2 in_VanToc);
	void set_ChieuRong(int in_ChieuRong);
	void set_ChieuCao(int in_ChieuCao);

	eLoaiDoiTuong get_LoaiDoiTuong() const;
	Vec2 get_ToaDo() const;
	Vec2 get_VanToc() const;
	int get_ChieuRong() const;
	int get_ChieuCao() const;
	HCN get_HCNGioiHan() const; // chiều cao, chiều rộng của các thực thể nên chia hết cho 2
	RECT get_RECT() const;
	eTrangThai get_TrangThai() const { return mTrangThai; }
};

