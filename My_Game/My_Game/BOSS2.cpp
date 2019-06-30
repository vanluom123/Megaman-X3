#include "BOSS2.h"
#include "Camera.h"


BOSS2::BOSS2(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 0, 0)
{
	mLoaiDoiTuong = eLDT_BOSS2;
	mBox[0] = new Box(Vec2(4950.0f, 1002.0f));
	mBox[1] = new Box(Vec2(4950.0f, 1002.0f));
	mPet1[0] = new Pet1();
	mPet1[1] = new Pet1();
	mPet2 = new Pet2();
	mDanSang = new DanSang();


	LoadThongTinHoatHinh();

	mTrangThai = eTT_BOSS2_BienMat;
}


void BOSS2::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (mTrangThai != eTT_BOSS2_XuatHien)
	{
		if (in_DoiTuong->get_ToaDo().x >= 4800.0f &&
			in_DoiTuong->get_ToaDo().x <= 4830.0f)
		{
			XuatHien();
		}
	}

	if (mTrangThai == eTT_BOSS2_BienMat)
	{
		return;
	}


	mBox[0]->CapNhat(in_tg, this);
	mBox[1]->CapNhat(in_tg, this);
	mPet1[0]->CapNhat(in_tg, this);
	mPet1[1]->CapNhat(in_tg, this);
	mPet2->CapNhat(in_tg, this);
	mDanSang->CapNhat(in_tg, in_DoiTuong);



	if (DEM_Pet2 > TG_Pet2)
	{
		if (mPet2->get_TrangThai() != eTT_Pet2_DiXuong)
		{
			mPet2->DiXuong();
		}
		if (DEM_Pet2 > TG_Pet2 + 2.7f)
		{
			mDanSang->BanDan(Vec2(4995.0f, 1130.0f), in_DoiTuong);
			DEM_Pet2 = TG_Pet2 + 0.01f;
		}
	}
	else
	{
		mPet2->DiLen();
	}


	switch (mTrangThai)
	{
	case eTT_BOSS2_XuatHien:
		DEM += in_tg;
		CapNhat_XuatHien(in_tg);
		break;

	case eTT_BOSS2_BocVac:
		if (SoHop == 0 && 
			mBox[0]->get_TrangThai() == eTT_Box_BienMat && 
			mBox[1]->get_TrangThai() == eTT_Box_BienMat)
		{
			DEM += in_tg;
			if (DEM > 1.0f)
			{
				BoChay();
			}
		}
		if (mBox[0]->get_TrangThai() == eTT_Box_BienMat)
		{

			if (SoHop > 0)
			{
				DEM_HoiChieuBox1 += in_tg;
				if (DEM_HoiChieuBox1 > TG_HoiChieuBox)
				{
					mBox[0]->DiChuyen(Vec2(4950.0f, 1002.0f), Vec2(38.0f, 70.0f), 2.29f);
					mPet1[0]->DiChuyen(Vec2(4950.0f, 952.0f), Vec2(38.0f, 70.0f), 2.29f);
					DEM_HoiChieuBox1 = 0.0f;
					SoHop--;
				}

			}
		}
		if (mBox[1]->get_TrangThai() == eTT_Box_BienMat)
		{
			if (SoHop > 0)
			{
				DEM_HoiChieuBox2 += in_tg;
				if (DEM_HoiChieuBox2 > TG_HoiChieuBox)
				{
					mBox[1]->DiChuyen(Vec2(5035.0f, 1002.0f), Vec2(26.0f, 70.0f), 2.29f);
					mPet1[1]->DiChuyen(Vec2(5035.0f, 952.0f), Vec2(26.0f, 70.0f), 2.29f);
					DEM_HoiChieuBox2 = 0.0f;
					SoHop--;
				}

			}
		}

		if (mBox[0]->get_TrangThai() == eTT_Box_DiChuyen &&
			mBox[1]->get_TrangThai() == eTT_Box_DiChuyen)
		{
			DEM_Pet2 += in_tg;
		}
		else
		{
			DEM_Pet2 = 0.0f;
		}

		break;

	case eTT_BOSS2_BoChay:
		DEM += in_tg;
		CapNhat_BoChay(in_tg);
		break;

	default:
		break;
	}


}

void BOSS2::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void BOSS2::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_BOSS2_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_BOSS2_BocVac)
	{
		mPet2->Ve(in_DoDoi);
	}
	HH_2->Ve(DS_HinhAnh::get_TH()->BOSS2_png, false, ToaDo_HH2, in_DoDoi);
	HH_1->Ve(DS_HinhAnh::get_TH()->BOSS2_png, false, ToaDo_HH1, in_DoDoi);
	mBox[0]->Ve(in_DoDoi);
	mBox[1]->Ve(in_DoDoi);
	mPet1[0]->Ve(in_DoDoi);
	mPet1[1]->Ve(in_DoDoi);
	mDanSang->Ve(in_DoDoi);
}

void BOSS2::XuatHien()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_XuatHien;
	mVanToc.y = 40.0f;
	ToaDo_HH1 = mToaDo;
	ToaDo_HH2 = mToaDo + Vec2(56.0f, -10.0f);
	SoHop = MAXBOX;
}

void BOSS2::BocVac()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BocVac;
	mVanToc.y = 0.0f;
	DEM_HoiChieuBox1 = TG_HoiChieuBox;
	DEM_HoiChieuBox2 = 0.0f;
}

void BOSS2::BoChay()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BoChay;
	mVanToc.y = -40.0f;
}

void BOSS2::BienMat()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BienMat;
	mVanToc.y = 0.0f;

	// CAMERA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if (Camera::CheckPoint == 9)
	{
		Camera::mGioiHanPhaiTiepTheo = 5647;
		Camera::speed = 4;
	}
}

void BOSS2::CapNhat_XuatHien(float in_tg)
{
	if (DEM < TG_XuatHien / 2.0f)
	{
		ToaDo_HH1.y += mVanToc.y * in_tg;
	}
	ToaDo_HH2.y += mVanToc.y * in_tg;
	if (DEM > TG_XuatHien)
	{
		BocVac();
	}
}

void BOSS2::CapNhat_BoChay(float in_tg)
{
	if (DEM >= TG_BoChay / 2.0f + 0.05f)
	{
		ToaDo_HH1.y += mVanToc.y *in_tg;
	}
	ToaDo_HH2.y += mVanToc.y * in_tg;
	if (DEM > TG_BoChay)
	{
		BienMat();
	}
}

void BOSS2::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(256, 88, HCN(0, 256, 0, 88)));
	HH_1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(144, 108, HCN(112, 112 + 144, 89, 89 + 108)));
	HH_2 = new HoatHinh(lDSTTFrame);


	
}

BOSS2::~BOSS2()
{
}
