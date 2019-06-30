#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"

class HieuUngMap :
	public DoiTuong
{
public:
	HieuUngMap(const Vec2& in_ToaDo, int in_Rong, int in_Cao, HoatHinh *in_HieuUng, int in_PhanLoai);
	~HieuUngMap();

	void CapNhat(float in_tg) {}
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}

private:
	HoatHinh *HH_HieuUng;
	int PhanLoai;
};

