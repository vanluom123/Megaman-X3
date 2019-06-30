#pragma once

#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class HieuUngLuot :
	public DoiTuong
{
public:
	HieuUngLuot();

	~HieuUngLuot();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
	}

	void Remake();

	bool get_BienMat()
	{
		return mBienMat;
	}

	void BienMat()
	{
		mBienMat = true;
	}

	void LatHinh(bool a)
	{
		mLatHinh = a;
	}

private:
	HoatHinh *mHoatHinh;

	float mTG_TonTai;
	float mTG_DemTonTai = 0.0f;
	bool mBienMat = true;
	bool mLatHinh = false;
};

