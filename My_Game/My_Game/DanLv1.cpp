#include "DanLv1.h"
#include "Ech.h"
#include "LoCot.h"
#include "TenLua.h"




DanLv1::DanLv1(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:
	DanLv(in_ToaDo, in_VanToc, 6, 4)
{
	mLoaiDoiTuong = eLDT_DanLv1;
	mDamage = 1;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTonTai;
	mTrangThai = eTT_Dan_BienMat;

}

DanLv1::~DanLv1()
{
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;
	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
}

void DanLv1::CapNhat(float in_tg)
{
	if (mTrangThai == eTT_Dan_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_Dan_TonTai)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}

	if (mTrangThai == eTT_Dan_DangTanBien)
	{
		mHH_HienTai->CapNhat(in_tg);
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
		{
			mTrangThai = eTT_Dan_BienMat;
		}
	}

	if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_Dan_BienMat;
	}

}

void DanLv1::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai != eTT_Dan_BienMat)
	{
		mHH_HienTai->Ve(DS_HinhAnh::get_TH()->DanLv1_png, false, mToaDo, in_DoDoi);
	}
}

// Độ dời phụ thuộc Camera hiện tại

void DanLv1::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai != eTT_Dan_TonTai)
	{
		return;
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_MayBay ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_Pet2)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_MayBay_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Ech)
	{		
		if (((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_BienMat ||
			((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_DangTanBien)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_LoCot)
	{
		if (((LoCot*)in_DoiTuong)->get_TrangThai() == eTT_LoCot_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_BOSS1)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_BOSS1_BienMat ||
			in_DoiTuong->get_TrangThai() == eTT_BOSS1_XuatHien ||
			in_DoiTuong->get_TrangThai() == eTT_BOSS1_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_TenLua)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_TenLua_PhatNo ||
			in_DoiTuong->get_TrangThai() == eTT_TenLua_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Box)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_Box_PhatNo ||
			in_DoiTuong->get_TrangThai() == eTT_Box_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}


	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_OngCon)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_OngCon_PhatNo ||
			in_DoiTuong->get_TrangThai() == eTT_OngCon_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_BOSS)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_BOSS_XuatHien ||
			in_DoiTuong->get_TrangThai() == eTT_BOSS_PhatNo || 
			in_DoiTuong->get_TrangThai() == eTT_BOSS_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DangTanBien();
	}
}

void DanLv1::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(8, 6, HCN(113 - 108, 121 - 108, 535 - 521, 541 - 521)));
	mHH_DangTonTai = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(12, 12, HCN(127 - 108, 139 - 108, 532 - 521, 544 - 521), 0.07f));
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(144 - 108, 157 - 108, 531 - 521, 544 - 521), 0.07f));
	lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(162 - 108, 178 - 108, 530 - 521, 545 - 521), 0.07f));
	mHH_DangTanBien = new HoatHinh(lDSTTFrame);
}

void DanLv1::DangTanBien()
{
	mTG_DemPhaHuy = 0.0f;
	mTrangThai = eTT_Dan_DangTanBien;
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
}

void DanLv1::DangTonTai()
{
	mTrangThai = eTT_Dan_TonTai;
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
}
