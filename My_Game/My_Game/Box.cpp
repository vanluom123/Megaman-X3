#include "Box.h"
#include "DanLv.h"
#include "VaChamGame.h"
#include "GameLog.h"
#include <time.h>    
#include "Sound.h"
#include "Camera.h"

Box::Box(const Vec2 & in_ToaDo, const Vec2& in_VanToc, int in_K)
	:
	DoiTuong(in_ToaDo, in_VanToc, 48, 48)
{
	ToaDo_BanDau = in_ToaDo;
	srand((int)time(NULL));

	mLoaiDoiTuong = eLDT_Box;

	LoadThongTinHoatHinh();

	K = in_K;

	if (K == 0 || K == 2)
	{
		mTrangThai = eTT_Box_BienMat;
	}

	if (K == 1)
	{
		mChieuCao = 192;
		mTrangThai = eTT_Box_DiChuyen;
	}

}

void Box::CapNhat(float in_tg)
{

}


// FUNCTION

void Box::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_Box_BienMat)
	{
		if (K == 2)
		{
			DiChuyen(ToaDo_BanDau, Vec2(0.0f, 400.0f), 1000.0f);
		}
		return;
	}

	DEM += in_tg;

	HH_1->CapNhat(in_tg);

	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	if (DEM_Shining <= TG_Shining)
	{
		DEM_Shining += in_tg;
	}

	if (HP <= 0)
	{
		PhatNo();
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			Sound::getInstance()->play("Hieu_Ung_No", false, 1);
		}
	}

	if (mTrangThai == eTT_Box_DiChuyen)
	{
		if (DEM > TG_DiChuyen)
		{
			mVanToc = Vec2();
		}
	}
	if (mTrangThai == eTT_Box_PhatNo)
	{
		HH_PhatNo->CapNhat(in_tg);
		if (DEM > TG_PhatNo)
		{
			BienMat();
		}
	}
}

void Box::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_Box_BienMat ||
		mTrangThai == eTT_Box_PhatNo)
	{
		return;
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv1 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv2 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv3)
	{

		if (in_DoiTuong->get_TrangThai() == eTT_Dan_BienMat ||
			in_DoiTuong->get_TrangThai() == eTT_Dan_DangTanBien)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DEM_Shining = 0.0f;
		HP -= ((DanLv*)in_DoiTuong)->get_Damage();
	}

	if (K == 2)
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{

			if (in_DoiTuong->get_TrangThai() == eTT_Dan_BienMat ||
				in_DoiTuong->get_TrangThai() == eTT_Dan_DangTanBien)
			{
				return;
			}

			if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				return;
			}

			HP -= 1000;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Box)
		{
			if (in_DoiTuong->get_TrangThai() == eTT_Box_PhatNo ||
				in_DoiTuong->get_TrangThai() == eTT_Box_BienMat)
			{
				return;
			}

			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

			if (lKQVC.eKQVC_DaVaCham)
			{
				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
				switch (lPVC)
				{
				case ePVC_Duoi:
					mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					break;
				default:
					break;
				}
			}
		}
	}
}
void Box::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_Box_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_Box_PhatNo)
	{
		for (int i = 0; i < 5; i++)
		{
			HH_PhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_PhatNo[i], in_DoDoi);
		}
		return;
	}

	if (K == 0 || K == 2)
	{
		HH_1->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo, in_DoDoi);

		if (DEM_Shining <= TG_Shining)
		{
			HH_1->Ve(DS_HinhAnh::get_TH()->Box_Shining_png, false, mToaDo, in_DoDoi);
		}
	}
	if (K == 1)
	{
		HH_1->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo + Vec2(0.0f, -24.0f), in_DoDoi);
		HH_1->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo + Vec2(0.0f, 24.0f), in_DoDoi);
		HH_1->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo + Vec2(0.0f, -72.0f), in_DoDoi);
		HH_1->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo + Vec2(0.0f, 72.0f), in_DoDoi);

		if (DEM_Shining <= TG_Shining)
		{
			HH_1->Ve(DS_HinhAnh::get_TH()->Box_Shining_png, false, mToaDo + Vec2(0.0f, -24.0f), in_DoDoi);
			HH_1->Ve(DS_HinhAnh::get_TH()->Box_Shining_png, false, mToaDo + Vec2(0.0f, 24.0f), in_DoDoi);
			HH_1->Ve(DS_HinhAnh::get_TH()->Box_Shining_png, false, mToaDo + Vec2(0.0f, -72.0f), in_DoDoi);
			HH_1->Ve(DS_HinhAnh::get_TH()->Box_Shining_png, false, mToaDo + Vec2(0.0f, 72.0f), in_DoDoi);
		}
	}
}

void Box::DiChuyen(const Vec2 & in_ToaDo, const Vec2 & in_VanToc, float in_TG)
{
	DEM = 0.0f;
	mTrangThai = eTT_Box_DiChuyen;
	DEM = 0.0f;
	TG_DiChuyen = in_TG;
	mVanToc = in_VanToc;
	mToaDo = in_ToaDo;
	HP = MAXHP;
}

void Box::PhatNo()
{
	DEM = 0.0f;
	mTrangThai = eTT_Box_PhatNo;
	mVanToc.x = 0.0f;
	mVanToc.y = 0.0f;
	HH_PhatNo->Remake();
	HP = MAXHP;
	for (int i = 0; i < 5; i++)
	{
		int l = rand() % 40 - 25;
		int r = rand() % 40 - 21;
		ToaDo_PhatNo[i] = Vec2(mToaDo + Vec2(float(l), float(r)));
	}

}

void Box::BienMat()
{
	DEM = 0.0f;
	mTrangThai = eTT_Box_BienMat;
}

void Box::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(0, 48, 0, 48), 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(48, 48 + 48, 0, 48), 0.1f));
	HH_1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.1f));
	HH_PhatNo = new HoatHinh(lDSTTFrame);
}
