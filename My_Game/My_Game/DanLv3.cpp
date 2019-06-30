#include "DanLv3.h"
#include "Ech.h"
#include "LoCot.h"



DanLv3::DanLv3(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:
	DanLv(in_ToaDo, in_VanToc, 24, 20)
{
	mLoaiDoiTuong = eLDT_DanLv3;
	mDamage = 4;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTT_Dan_BienMat;
}

DanLv3::~DanLv3()
{
	if (mHH_BanRa)
		delete mHH_BanRa;
	
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;

	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
}

void DanLv3::CapNhat(float in_tg)
{
	if (mTrangThai == eTT_Dan_BienMat)
		return;

	mHH_HienTai->CapNhat(in_tg);

	if (mTrangThai == eTT_Dan_BanRa)
	{
		mTG_DemBanRa += in_tg;

		if (mTG_DemBanRa > mTG_BanRa)
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

void DanLv3::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_Dan_BienMat)
		return;

	mHH_HienTai->Ve(DS_HinhAnh::get_TH()->DanLv3_png, mLatHinh, mToaDo, in_DoDoi);
}

void DanLv3::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_Dan_BienMat || mTrangThai == eTT_Dan_DangTanBien)
	{
		return;
	}


	//if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Ech)
	//{
	//	if (((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_BienMat ||
	//		((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_DangTanBien)
	//	{
	//		return;

	//	}

	//	if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
	//	{
	//		return;
	//	}

	//	if (!mLatHinh)
	//		mToaDo.x += 10.0f;
	//	else
	//		mToaDo.x -= 10.0f;

	//	DangTanBien();
	//}

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

void DanLv3::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(14, 20, HCN(15, 15 + 14, 10, 10 + 20), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(24, 16, HCN(46, 46 + 24, 2, 2 + 16), 0.03f));
	mHH_BanRa = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame( 54, 32, HCN(64, 64 + 46, 5, 5 + 32), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame( 52, 30, HCN(115, 115 + 46, 6, 6 + 30), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame( 48, 32, HCN(164, 164 + 42, 5, 5 + 32), 0.03f));
	mHH_DangTonTai = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(14, 20, HCN(258, 258 + 14, 10, 10 + 20), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(24, 28, HCN(276, 276 + 24, 6, 6 + 28), 0.03f));
	mHH_DangTanBien = new HoatHinh(lDSTTFrame);
}

void DanLv3::DangTanBien()	
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_DangTanBien;
	mTG_DemPhaHuy = 0.0f;
}

void DanLv3::DangTonTai()
{
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_TonTai;
}

void DanLv3::Ban()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTT_Dan_BanRa;
	mTG_DemBanRa = 0.0f;
}
