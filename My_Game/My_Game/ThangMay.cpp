#include "ThangMay.h"
#include "Camera.h"
#include "VaChamGame.h"

ThangMay::ThangMay(const Vec2 & in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 96, 34)
{
	mLoaiDoiTuong = eLDT_ThangMay;

	ToaDoXuatHien = in_ToaDo;

	LoadThongTinHoatHinh();

	DungIm();
}

void ThangMay::Ve(const Vec2 & in_DoDoi)
{

	HH_DuyNhat->Ve(DS_HinhAnh::get_TH()->ThangMay_png, false, mToaDo, in_DoDoi);
}

void ThangMay::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void ThangMay::CapNhat(float in_tg, const DoiTuong * in_XMan)
{

	mToaDo.y += mVanToc.y * in_tg;

	switch (mTrangThai)
	{
	case eTT_ThangMay_DungIm:
		CapNhat_DungIm(in_tg, in_XMan);
		break;

	case eTT_ThangMay_DiChuyen:
		CapNhat_DiChuyen(in_tg, in_XMan);
		break;

	default:
		break;
	}

	if (mToaDo.y - in_XMan->get_ToaDo().y < -350.0f)
	{
		mToaDo.y = ToaDoXuatHien.y + 100.0f;
		DenViTriXuatHien = false;
		DiChuyen();
	}
}

void ThangMay::DiChuyen()
{
	mTrangThai = eTT_ThangMay_DiChuyen;
	mVanToc.y = -65.0f;
}

void ThangMay::DungIm()
{
	mTrangThai = eTT_ThangMay_DungIm;
	mVanToc.y = 0.0f;
}

void ThangMay::BienMat()
{
	mTrangThai = eTT_ThangMay_BienMat;
}

void ThangMay::CapNhat_DiChuyen(float in_tg, const DoiTuong* in_XMan)
{
	HH_DuyNhat->CapNhat(in_tg);
	if (mToaDo.y <= 451.0f)
	{
		DungIm();
	}
	
	if (!DenViTriXuatHien && mToaDo.y <= ToaDoXuatHien.y)
	{
		DenViTriXuatHien = true;
		DungIm();
	}
}

void ThangMay::CapNhat_DungIm(float in_tg, const DoiTuong *in_XMan)
{
	if (mToaDo.x - in_XMan->get_ToaDo().x < 30.0f &&
		mToaDo.x - in_XMan->get_ToaDo().x > -30.0f &&
		mToaDo.y > 451.0f)
	{
		DiChuyen();
	}
}


void ThangMay::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.push_back(ThongTinFrame(96, 52, HCN(0, 0 + 96, 0, 0 + 44), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(96, 54, HCN(0, 0 + 96, 45, 45 + 44), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(96, 56, HCN(0, 0 + 96, 90, 90 + 46), 0.05f));
	HH_DuyNhat = new HoatHinh(lDSTTFrame);
}
