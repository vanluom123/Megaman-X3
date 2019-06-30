#pragma once

#include "DoiTuong.h"

class DoiTuongTinh : public DoiTuong
{
public:
	DoiTuongTinh(Vec2 in_ToaDo, int in_Width, int in_Height, int in_K = 0) :
		DoiTuong(in_ToaDo, Vec2(0, 0), in_Width, in_Height)
	{
		K = in_K;
		if (K == 0)
		{
			DoiTuong::mLoaiDoiTuong = eLDT_DoiTuongTinh;
		}
		else if (K == -1)
		{
			mLoaiDoiTuong = eLDT_Gai;
		}
		else if (K == 2)
		{
			mLoaiDoiTuong = eLDT_DoiTuongTinh2;
		}
		else if (K == 3)
		{
			mLoaiDoiTuong = eLDT_DoiTuongTinh3;
		}
		else if (K == 4)
		{
			mLoaiDoiTuong = eLDT_DoiTuongTinh4;
		}
	}

	virtual void CapNhat(float in_tg) {}
	virtual void Ve(const Vec2& in_DoDoi) {}
	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
private:
	int K;
};

