#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Pet2 :
	public DoiTuong
{
public:
	Pet2()
		:
		DoiTuong(Vec2(), Vec2(), 32 , 24
		)
	{
		mLoaiDoiTuong = eLDT_Pet2;
		ToaDoBanDau = mToaDo = Vec2(4995.0f, 1102.0f);
		LoadThongTinHoatHinh();
	}

	void CapNhat(float in_tg) {}
	// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong) 
	{
		DEM += in_tg;

		mToaDo.y += mVanToc.y * in_tg;

		if (mTrangThai == eTT_Pet2_DiXuong)
		{
			if (DEM > 2.3f)
			{
				mVanToc.y = 0.0f;
			}
		}

	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
	void Ve(const Vec2& in_DoDoi)
	{
		HH->Ve(DS_HinhAnh::get_TH()->Pet2_png, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	void DiXuong()
	{
		mTrangThai = eTT_Pet2_DiXuong;
		mToaDo = ToaDoBanDau;
		mVanToc.y = 10.0f;
		DEM = 0.0f;
	}
	void DiLen()
	{
		mTrangThai = eTT_Pet2_DiLen;
		mVanToc.y = -10.0f;
		DEM = 0.0f;
	}

// SUB-FUNCTION
private:
	float DEM = 0.0f;
	Vec2 ToaDoBanDau;
	HoatHinh *HH;

	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 26, HCN(2, 2 + 32, 5, 5 + 26)));
		HH = new HoatHinh(lDSTTFrame);
	}
// DESTRUTURE
public:
	~Pet2()
	{

	}
};

