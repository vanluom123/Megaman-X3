#pragma once
#include "DoiTuong.h"
#include "VaChamGame.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class HongTam :
	public DoiTuong
{
public:
	HongTam()
		:
		DoiTuong(Vec2(), Vec2(), 16, 16)
	{
		mLoaiDoiTuong = eLDT_HongTam;
		LoadThongTinHoatHinh();
		BienMat();
	}

	void CapNhat(float in_tg) {} // NOT USE
// FUNCTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{
		if (mTrangThai == eTT_HongTam_BienMat)
		{
			return;
		}

		if (mTrangThai == eTT_HongTam_DiChuyen)
		{
			// Rượt theo Megaman
			float DX = in_DoiTuong->get_ToaDo().x - mToaDo.x;
			float DY = in_DoiTuong->get_ToaDo().y - mToaDo.y;
			if (DX > 0.0f)
			{
				if (mVanToc.x < 0.0f)
				{
					mVanToc.x += 2000.0f * in_tg;
				}
				mVanToc.x += 800.0f * in_tg;
				if (mVanToc.x > 130.0f)
				{
					mVanToc.x = 130.0f;
				}
			}
			else
			{
				if (mVanToc.x > 0.0f)
				{
					mVanToc.x -= 2000.0f * in_tg;
				}
				mVanToc.x -= 800.0f * in_tg;
				if (mVanToc.x < -130.0f)
				{
					mVanToc.x = -130.0f;
				}
			}
			if (DY > 0.0f)
			{
				if (mVanToc.y < 0.0f)
				{
					mVanToc.y += 2000.0f * in_tg;
				}
				mVanToc.y += 800.0f * in_tg;
				if (mVanToc.y > 130.0f)
				{
					mVanToc.y = 130.0f;
				}
			}
			else
			{
				if (mVanToc.y < 0.0f)
				{
					mVanToc.y -= 2000.0f * in_tg;
				}
				mVanToc.y -= 800.0f * in_tg;
				if (mVanToc.y < -130.0f)
				{
					mVanToc.y = -130.0f;
				}
			}
			if (DEM > 5.0f)
			{
				BienMat();
			}
		}
		if (mTrangThai == eTT_HongTam_LockMucTieu)
		{
			mToaDo = in_DoiTuong->get_ToaDo();
			if (DEM > 5.0f)
			{
				BienMat();
			}
		}
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
		DEM += in_tg;
		HH_HienTai->CapNhat(in_tg);
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
		if (mTrangThai == eTT_HongTam_BienMat)
		{
			return;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_XMan)
		{
			if (mTrangThai == eTT_HongTam_DiChuyen)
			{
				// nếu Trung Tâm XMan va chạm với Hồng Tâm thì Lock Mục Tiêu
				if (VaChamGame::get_DiemVaHCN((int)in_DoiTuong->get_ToaDo().x, (int)in_DoiTuong->get_ToaDo().y,
					get_HCNGioiHan()))
				{
					LockMucTieu();
				}
			}
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mTrangThai == eTT_HongTam_BienMat)
		{
			return;
		}
		HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(150, 255, 255, 255));
	}
	void DiChuyen(const Vec2& in_ToaDo)
	{
		mToaDo = in_ToaDo;
		mTrangThai = eTT_HongTam_DiChuyen;
		HH_HienTai = HH_DiChuyen;
		HH_HienTai->Remake();
		DEM = 0.0f;
		mVanToc = Vec2();
	}
	void BienMat()
	{
		mTrangThai = eTT_HongTam_BienMat;
	}
// INFORMATION
private:
	float DEM = 0.0f;
	HoatHinh *HH_DiChuyen,
		*HH_LockMucTieu,
		*HH_HienTai;
// SUB-FUNCTION
private:

	void LockMucTieu()
	{
		mTrangThai = eTT_HongTam_LockMucTieu;
		HH_HienTai = HH_LockMucTieu;
		HH_HienTai->Remake();
	}

	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(96, 96 + 16, 186, 186 + 16),   0.1f));
		lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(113, 113 + 16, 186, 186 + 16), 0.1f));
		HH_DiChuyen = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(131, 131 + 24, 182, 182 + 24), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(158, 158 + 24, 182, 182 + 24), 0.1f));
		HH_LockMucTieu = new HoatHinh(lDSTTFrame);
	}
// DESTRUCTURE
public:
	~HongTam()
	{

	}
};

