#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "VaChamGame.h"
#include <time.h>    

class Item :
	public DoiTuong
{
// CONSTRUCTURE
public:
	Item()
		:
		DoiTuong(Vec2(), Vec2(), 16, 12)
	{
		mLoaiDoiTuong = eLDT_Item;
		srand((int)time(NULL));

		std::vector<ThongTinFrame> lDSTTFrame;
		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(14, 12, HCN(0,   0 + 16, 12, 24), 0.12f));
		lDSTTFrame.push_back(ThongTinFrame(16, 12, HCN(16, 16 + 16, 12, 24), 99.9f));
		HH_Roi = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(16, 12, HCN(34, 34 + 16, 12, 24), 0.15f));
		lDSTTFrame.push_back(ThongTinFrame(16, 12, HCN(52, 52 + 16, 12, 24), 0.15f));
		HH_NamIm = new HoatHinh(lDSTTFrame);

		BienMat();
	}

	// ko xài cái này
	void CapNhat(float in_tg) { }

// FUNCTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_XMan)
	{
		if (mTrangThai == eTT_Item_BienMat)
		{
			return;
		}

		mToaDo.y += mVanToc.y * in_tg;
		DEM += in_tg;
		if (mTrangThai == eTT_Item_Roi)
		{
			HH_Roi->CapNhat(in_tg);
			mVanToc.y += GiaTocTrongTruong * in_tg;
		}
		if (mTrangThai == eTT_Item_NamIm)
		{
			HH_NamIm->CapNhat(in_tg);
			if (DEM > 3.0f)
			{
				DEM2 += in_tg;
				if (DEM2 > 0.2f)
				{
					DEM2 = 0.0f;
				}
			}
			if (DEM > 5.0f)
			{
				BienMat();
			}
		}
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
		if (mTrangThai == eTT_Item_BienMat)
		{
			return;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_ThangMay || 
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh2)
		{
			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

			if (lKQVC.eKQVC_DaVaCham)
			{
				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
				switch (lPVC)
				{
				case ePVC_Duoi:
					mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					NamIm();
					break;

				default:
					break;
				}
			}
		}
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_XMan)
		{
			if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				return;
			}
			BienMat();
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mTrangThai == eTT_Item_BienMat)
		{
			return;
		}
		if (mTrangThai == eTT_Item_Roi)
		{
			HH_Roi->Ve(DS_HinhAnh::get_TH()->Item, false, mToaDo, in_DoDoi);
		}
		if (mTrangThai == eTT_Item_NamIm)
		{
			if (DEM <= 3.0f)
			{
				HH_NamIm->Ve(DS_HinhAnh::get_TH()->Item, false, mToaDo, in_DoDoi);
			}
			else
			{
				if (DEM2 <= 0.1f)
					HH_NamIm->Ve(DS_HinhAnh::get_TH()->Item, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(170, 255, 255, 255));
				else
				{
					HH_NamIm->Ve(DS_HinhAnh::get_TH()->Item, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(120, 255, 255, 255));
				}
			}
		}
	}
	void Roi(const Vec2& in_ToaDo)
	{
		if (mTrangThai == eTT_Item_BienMat)
		{
			int l = rand() % 100;
			if (l < 20)
			{
				mToaDo = in_ToaDo;
				mTrangThai = eTT_Item_Roi;
				mVanToc.y = -200.0f;
				HH_Roi->Remake();
				DEM = 0.0f;
			}
		}
	}
// INFORMATION
private:
	static constexpr float GiaTocTrongTruong = 1000.0f;
	float DEM2 = 0.0f;
	float DEM = 0.0f;
	HoatHinh *HH_Roi,
		*HH_NamIm;
// SUB-FUNCTION
private:

	void NamIm()
	{
		mTrangThai = eTT_Item_NamIm;
		mVanToc.y = 0.0f;
		HH_NamIm->Remake();
		DEM = 0.0f;
		DEM2 = 0.0f;
	}
	void BienMat()
	{
		mTrangThai = eTT_Item_BienMat;
	}

// DESTRUCTURE
public:
	~Item()
	{

	}
};

