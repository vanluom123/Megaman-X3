#include "DanLv2.h"
#include "Ech.h"
#include "LoCot.h"


DanLv2::DanLv2(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:DanLv(in_ToaDo, in_VanToc, 15, 12)
{
	mLoaiDoiTuong = eLDT_DanLv2;
	mDamage = 2;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTT_Dan_BienMat;
}

DanLv2::~DanLv2()
{
	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;
}

void DanLv2::CapNhat(float in_tg)
{
	if (mTrangThai == eTT_Dan_BienMat)
		return;

	mHH_HienTai->CapNhat(in_tg);

	if (mTrangThai == eTT_Dan_BanRa)
	{
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
			DangTonTai();
	}

	if (mTrangThai == eTT_Dan_TonTai)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}

	if (mTrangThai == eTT_Dan_DangTanBien)
	{
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
			mTrangThai = eTT_Dan_BienMat;
	}

	if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_Dan_BienMat;
	}
}

void DanLv2::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_Dan_BienMat)
		return;

	mHH_HienTai->Ve(DS_HinhAnh::get_TH()->DanLv2_png, mLatHinh, mToaDo, in_DoDoi);
}

void DanLv2::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_Dan_BienMat || mTrangThai == eTT_Dan_DangTanBien)
	{
		return;
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

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

		DangTanBien();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_LoCot ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_Pet2)
	{
		if (((LoCot*)in_DoiTuong)->get_TrangThai() == eTT_LoCot_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

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

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

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

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

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

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

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

		if (!mLatHinh)
			mToaDo.x += 10.0f;
		else
			mToaDo.x -= 10.0f;

		DangTanBien();
	}


}

void DanLv2::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 14, HCN(26, 42, 7, 21), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(46, 70, 2, 26), 0.03f));
	mHH_DangTanBien = new HoatHinh(lDSTTFrame);


	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(36, 12, HCN(75, 103, 8, 20), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(40, 8,  HCN(109, 141, 10, 18), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(46, 12, HCN(148, 186, 8, 20), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(44, 22, HCN(191, 227, 3, 25), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(46, 12, HCN(232, 270, 8, 20), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(48, 22, HCN(276, 316, 3, 25), 0.08f));
	mHH_DangTonTai = new HoatHinh(lDSTTFrame);
}

void DanLv2::DangTanBien()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_DangTanBien;
	mTG_DemPhaHuy = 0.0f;
}

void DanLv2::DangTonTai()
{
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_TonTai;
}

void DanLv2::Ban()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_BanRa;
	mTG_DemPhaHuy = 0.0f;
}