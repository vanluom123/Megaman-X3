#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"


class ThangMay :
	public DoiTuong
{
public:
	ThangMay(const Vec2& in_ToaDo);

	// Ko Dung
	void CapNhat(float in_tg) {}

// FUNCTION
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void CapNhat(float in_tg, const DoiTuong *in_XMan);

// INFORMATION
private:
	HoatHinh* HH_DuyNhat;

	Vec2 ToaDoXuatHien;

	bool DenViTriXuatHien = true;

// SUB-FUNCTION
	void DiChuyen();
	void DungIm();
	void BienMat();

	void CapNhat_DiChuyen(float in_tg, const DoiTuong* in_XMan);
	void CapNhat_DungIm(float in_tg, const DoiTuong* in_XMan);

	void LoadThongTinHoatHinh();

// DESTRUCTURE
	~ThangMay()
	{

	}
};

