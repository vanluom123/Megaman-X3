#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Pet1 :
	public DoiTuong
{
public:
	Pet1()
		:
		DoiTuong(Vec2(), Vec2(), 0, 0)
	{

		// hoat hinh
		std::vector<ThongTinFrame> lDSTTFrame;
		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(12, 6, HCN(3, 3 + 12, 2, 2 + 6), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(20, 6, HCN(18, 18 + 20, 2, 8),   0.08f));
		lDSTTFrame.push_back(ThongTinFrame(32, 6, HCN(41, 41 + 32, 2, 8),   0.08f));
		lDSTTFrame.push_back(ThongTinFrame(20, 6, HCN(75, 75 + 20, 2, 8),   0.08f));
		lDSTTFrame.push_back(ThongTinFrame(12, 6, HCN(99, 99 + 12, 2, 8),   0.08f));
		HH_1 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2, 2 + 36, 13, 13 + 54), 0.2f));
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(41, 41 + 36, 13, 13 + 54), 0.2f));
		HH_2 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2,     2 + 36, 13, 13 + 54),     0.25f));
		lDSTTFrame.push_back(ThongTinFrame(44, 58, HCN(120, 120 + 44, 13, 13 + 54), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2,     2 + 36, 13, 13 + 54),     99.9f));
		HH_3 = new HoatHinh(lDSTTFrame);

		HH_HienTai = HH_2;
	}

	void CapNhat(float in_tg) {}
// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong) 
	{
		if (KichHoat)
		{
			DEM += in_tg;
			HH_1->CapNhat(in_tg);
			HH_HienTai->CapNhat(in_tg);
			mToaDo.x += mVanToc.x * in_tg;
			mToaDo.y += mVanToc.y * in_tg;

			if (DEM > TG_DiXuong + 0.009f && 
				DEM <= TG_DiXuong + 0.29f)
			{
				mVanToc.x = 0.0f;
				mVanToc.y = 0.0f;
			}
			else if (DEM > TG_DiXuong + 0.29f)
			{
				mVanToc.x = 0.0f;
				mVanToc.y = -80.0f;
			}
			if (DEM > TG_DiXuong &&
				DEM <= TG_DiXuong + 0.77f)
			{
				HH_HienTai = HH_3;
			}
			else
			{
				HH_HienTai = HH_2;
			}
			if (DEM > TG_DiXuong * 2.0f)
			{
				KichHoat = false;
			}
		}
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}

	void Ve(const Vec2& in_DoDoi)
	{
		if (KichHoat)
		{
			HH_HienTai->Ve(DS_HinhAnh::get_TH()->Pet1_png, false, mToaDo, in_DoDoi);
			HH_1->Ve(DS_HinhAnh::get_TH()->Pet1_png, false, mToaDo + Vec2(0.0f, -29.0f), in_DoDoi);
		}
	}
	void DiChuyen(const Vec2& in_ToaDo, const Vec2& in_VanToc, float in_TG)
	{
		HH_HienTai = HH_2;
		mToaDo = in_ToaDo;
		mVanToc = in_VanToc;
		DEM = 0.0f;
		TG_DiXuong = in_TG;
		KichHoat = true;
		HH_1->Remake();
		HH_2->Remake();
		HH_3->Remake();
	}
// INFORMATION
private:
	HoatHinh *HH_1,
		*HH_2,
		*HH_3;
	HoatHinh *HH_HienTai;
	float TG_DiXuong = 2.29f;
	float DEM = 0.0f;
	bool KichHoat = false;

// DESTRUCTURE
public:
	~Pet1(){}
};

