#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class DanSang :
	public DoiTuong
{
public:
	DanSang()
		:
		DoiTuong(Vec2(), Vec2(), 14, 14)
	{
		mLoaiDoiTuong = eLDT_DanSang;
		LoadThongTinHoatHinh();
	}
	void CapNhat(float in_tg) { }
	
// FUNCTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{
		DEM += in_tg;
		HH->CapNhat(in_tg);
		if (DEM > 0.2f)
		{
			mToaDo.x += mVanToc.x * in_tg;
			mToaDo.y += mVanToc.y * in_tg;
		}
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong) { }
	void Ve(const Vec2& in_DoDoi)
	{
		HH->Ve(DS_HinhAnh::get_TH()->Pet2_png, false, mToaDo, in_DoDoi);
	}
	void BanDan(const Vec2& in_ToaDo, const DoiTuong *XMAN)
	{
		DEM = 0.0f;
		mToaDo = in_ToaDo;
		float DX = mToaDo.x - XMAN->get_ToaDo().x;
		float DY = mToaDo.y - XMAN->get_ToaDo().y;
		float Cotan = DX / DY;

		if (DY > -25.0f &&
			DY <= 25.0f)
		{
			if (DY < 0)
			{
				mVanToc.y = 70.0f;
			}
			else
			{
				mVanToc.y = -70.0f;
			}
		}
		else if (DY < 0)
		{
			mVanToc.y = 200.0f;
		}
		else
		{
			mVanToc.y = -200.0f;
		}

		mVanToc.x = Cotan * mVanToc.y;
	}
// INFORMATION
private:
	float DEM = 2.0f;
	HoatHinh *HH;
// SUB-FUNCTION
	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(14, 16, HCN(1, 1 + 14, 32, 32 + 16), 0.01f));
		lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(17, 17 + 14, 32, 32 + 14), 0.01f));
		lDSTTFrame.push_back(ThongTinFrame(14, 16, HCN(34, 34 + 14, 32, 32 + 16), 0.01f));
		HH = new HoatHinh(lDSTTFrame);
	}
// DESTRUCTURE
public:
	~DanSang()
	{

	}
};

