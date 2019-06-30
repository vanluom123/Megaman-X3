#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "VaChamGame.h"
#include "XMan.h"

class OngCon :
	public DoiTuong
{
// CONSTRUCTURE
public:
	OngCon()
		:
		DoiTuong(Vec2(), Vec2(), 20, 22)
	{
		mLoaiDoiTuong = eLDT_OngCon;
		LoadThongTinHoatHinh();
		mToaDo = Vec2(7800.0f, 1900.0f);
		mTrangThai = eTT_OngCon_BienMat;
		HH_HienTai = HH_ConOng;
	}
	void CapNhat(float in_tg) {} // NOT USE
// FUNTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{
		if (mTrangThai == eTT_OngCon_BienMat)
		{
			return;
		}
		DEM += in_tg;
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
		HH_HienTai->CapNhat(in_tg);
		if (mTrangThai != eTT_OngCon_PhatNo && HP <= 0)
		{
			PhatNo();
		}
		if (mTrangThai == eTT_OngCon_BanRa)
		{
			if (BamXMAN)
			{
				mVanToc = 0.0f;
				mToaDo = in_DoiTuong->get_ToaDo() + Vec2(DX, DY);
			}
			if (DEM > TG_BanRa)
			{
				PhatNo();
			}
			DEM_KoTheGaySatThuong += in_tg;
		}
		if (mTrangThai == eTT_OngCon_PhatNo)
		{
			if (DEM > TG_PhatNo)
			{
				BienMat();
			}
		}
		if (mTrangThai == eTT_OngCon_ChoDoiHongTam)
		{
			if (DEM > 6.0f)
			{
				PhatNo();
			}
		}
		if (mTrangThai == eTT_OngCon_TanCongMucTieu)
		{
			if (DEM > 6.0f)
			{
				PhatNo();
			}
			DEM_KoTheGaySatThuong += in_tg * 3;
			float DX = in_DoiTuong->get_ToaDo().x - mToaDo.x;
			float DY = in_DoiTuong->get_ToaDo().y - mToaDo.y;
			if (DX > 0.0f)
			{
				if (mVanToc.x < 0.0f)
				{
					mVanToc.x += 1200.0f * in_tg;
				}
				mVanToc.x += 290.0f * in_tg;
				if (mVanToc.x > 90.0f)
				{
					mVanToc.x = 90.0f;
				}
			}
			else
			{
				if (mVanToc.x > 0.0f)
				{
					mVanToc.x -= 1200.0f * in_tg;
				}
				mVanToc.x -= 290.0f * in_tg;
				if (mVanToc.x < -90.0f)
				{
					mVanToc.x = -90.0f;
				}
			}
			if (DY > 0.0f)
			{
				if (mVanToc.y < 0.0f)
				{
					mVanToc.y += 1200.0f * in_tg;
				}
				mVanToc.y += 290.0f * in_tg;
				if (mVanToc.y > 90.0f)
				{
					mVanToc.y = 90.0f;
				}
			}
			else
			{
				if (mVanToc.y < 0.0f)
				{
					mVanToc.y -= 1200.0f * in_tg;
				}
				mVanToc.y -= 290.0f * in_tg;
				if (mVanToc.y < -90.0f)
				{
					mVanToc.y = -90.0f;
				}
			}
		}
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
		if (mTrangThai == eTT_OngCon_BienMat ||
			mTrangThai == eTT_Box_PhatNo)
		{
			return;
		}
		if (BamXMAN)
		{
			return;
		}
		
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_CuaDanhBoss ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh4)
		{
			if (mTrangThai == eTT_OngCon_TanCongMucTieu)
			{
				return;
			}

			if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				return;
			}
			mVanToc = Vec2();
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_XMan)
		{
			if (mTrangThai != eTT_OngCon_BanRa)
			{
				return;
			}

			if (mVanToc.x == 0.0f && mVanToc.y == 0.0f)
			{
				return;
			}
			if (!((XMan*)in_DoiTuong)->get_CoTheNhanSatThuong())
			{
				return;
			}

			if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				return;
			}
			BamXMAN = true;
			DX = mToaDo.x - in_DoiTuong->get_ToaDo().x;
			DY = mToaDo.y - in_DoiTuong->get_ToaDo().y;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv1 ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv2 ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv3)
		{

			if (((DanLv*)in_DoiTuong)->get_TrangThai() == eTT_Dan_BienMat ||
				((DanLv*)in_DoiTuong)->get_TrangThai() == eTT_Dan_DangTanBien)
			{
				return;
			}

			if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				return;
			}

			HP -= ((DanLv*)in_DoiTuong)->get_Damage();
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mTrangThai == eTT_OngCon_BienMat)
		{
			return;
		}
		HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi);
	}

	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc)
	{
		mTrangThai = eTT_OngCon_BanRa;
		mToaDo = in_ToaDo;
		mVanToc = in_VanToc;
		LatHinh = (mVanToc.x > 0);
		BamXMAN = false;
		DEM = 0.0f;
		HH_HienTai = HH_ConOng;
		HP = MAXHP;
		DEM_KoTheGaySatThuong = TG_KoTheGaySatThuong + 0.1f;
	}
	void ChoDoiHongTam(const Vec2& in_ToaDo)
	{
		mTrangThai = eTT_OngCon_ChoDoiHongTam;
		HH_HienTai = HH_ConOng;
		mToaDo = in_ToaDo;
		DEM = 0.0f;
		HP = MAXHP;
	}
	void TanCongMucTieu()
	{
		if (mTrangThai == eTT_OngCon_ChoDoiHongTam)
		{
			mTrangThai = eTT_OngCon_TanCongMucTieu;
		}
	}

	bool get_KoTheGaySatThuong() { return (DEM_KoTheGaySatThuong <= TG_KoTheGaySatThuong); }
	float DEM_KoTheGaySatThuong = 99.9f;
	void PhatNo()
	{
		mTrangThai = eTT_OngCon_PhatNo;
		HH_HienTai = HH_PhatNo;
		HH_HienTai->Remake();
		DEM = 0.0f;
	}

	void BienMat()
	{
		mTrangThai = eTT_OngCon_BienMat;
		DEM = 0.0f;
	}

// INFORMATION
private:
	static constexpr float TG_KoTheGaySatThuong = 1.3f;
	int MAXHP = 2;
	int HP = MAXHP;
	static constexpr float TG_BanRa = 3.5f;
	static constexpr float TG_PhatNo = 0.05f * 7;
	float DEM = 0.0f;
	HoatHinh *HH_ConOng,
		*HH_PhatNo;
	HoatHinh *HH_HienTai;
	bool LatHinh;
	bool BamXMAN;
	float DX, DY;
// SUB-FUNCTION
private:



	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(20, 22, HCN(17, 17 + 20, 172, 194), 0.03f));
		lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(64, 64 + 22, 172, 194), 0.03f));
		lDSTTFrame.push_back(ThongTinFrame(20, 22, HCN(41, 41 + 20, 172, 194), 0.03f));
		lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(64, 64 + 22, 172, 194), 0.03f));
		HH_ConOng = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(186, 186 + 16, 185, 185 + 16), 0.05f)); // 1
		lDSTTFrame.push_back(ThongTinFrame(20, 20, HCN(205, 205 + 20, 183, 183 + 20), 0.05f)); // 2
 		lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(228, 228 + 24, 181, 181 + 24), 0.05f)); // 3
		lDSTTFrame.push_back(ThongTinFrame(26, 26, HCN(254, 254 + 26, 180, 180 + 26), 0.05f)); // 4
		lDSTTFrame.push_back(ThongTinFrame(32, 30, HCN(283, 283 + 32, 178, 178 + 30), 0.05f)); // 5
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(319, 319 + 32, 177, 177 + 32), 0.05f)); // 6
		lDSTTFrame.push_back(ThongTinFrame(34, 34, HCN(354, 354 + 34, 176, 176 + 34), 99.9f)); // 7
		HH_PhatNo = new HoatHinh(lDSTTFrame);
	}
// DESTRUCTURE
public:
	~OngCon()
	{

	}
};

