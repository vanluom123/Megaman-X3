#include "DanNo1.h"
#include "DanLv.h"
#include "Sound.h"
#include "Camera.h"



// FUNCTION

DanNo1::DanNo1()
	:DoiTuong(Vec2(), Vec2(), 8, 8)
{
	mLoaiDoiTuong = eLDT_DanNo1;
	mTrangThai = eTT_DanNo1_BienMat;

	LoadThongTinHoatHinh();

}

void DanNo1::CapNhat(float in_tg)
{
	// cập nhật hiệu ứng
	if (mTGDem_NoTung <= mTG_NoTung)
	{
		mTGDem_NoTung += in_tg;
		mHH_HieuUngPhatNo->CapNhat(in_tg);
	}

	// nếu đạn đã bị phá hủy -> ko cần Cập Nhật
	if (mTrangThai == eTT_DanNo1_BienMat)
	{
		return;
	}

	mTGDem_TonTai += in_tg;
	if (mTGDem_TonTai > mTG_TonTai)
	{
		mTrangThai = eTT_DanNo1_BienMat;
	}
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (mVanToc.y > mVanTocRoiToiDa)
	{
		mVanToc.y = mVanTocRoiToiDa;
	}
}

void DanNo1::Ve(const Vec2 & in_DoDoi)
{
	if (mTGDem_NoTung <= mTG_NoTung)
	{
		mHH_HieuUngPhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, mToaDo_HieuUngNoTung, in_DoDoi);
	}

	// nếu đã bị phá hủy -> ko cần phải Vẽ ra
	if (mTrangThai == eTT_DanNo1_BienMat)
	{
		return;
	}

	mHH_Dan->Ve(DS_HinhAnh::get_TH()->DanNo1_png, false, mToaDo, in_DoDoi);
}

void DanNo1::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	// nếu đã bị phá hủy -> ko cần phải xét va chạm
	if (mTrangThai == eTT_DanNo1_BienMat)
	{
		return;
	}


	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_XMan)
	{
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		mTrangThai = eTT_DanNo1_BienMat;
		mTGDem_NoTung = 0.0f;
		// set tọa độ hiệu ứng nổ tung 
		mToaDo_HieuUngNoTung = mToaDo;
		mHH_HieuUngPhatNo->Remake();
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			Sound::getInstance()->play("Hieu_Ung_No", false, 1);
		}
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

		mTrangThai = eTT_DanNo1_BienMat;
		mTGDem_NoTung = 0.0f;
		// set tọa độ hiệu ứng nổ tung 
		mToaDo_HieuUngNoTung = mToaDo;
		mHH_HieuUngPhatNo->Remake();
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			Sound::getInstance()->play("Hieu_Ung_No", false, 1);
		}
	}
}

void DanNo1::BanRa(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
{
	mToaDo = in_ToaDo;
	mVanToc = in_VanToc;
	mTrangThai = eTT_DanNo1_TonTai;
	mTGDem_TonTai = 0.0f;
}

void DanNo1::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.push_back(ThongTinFrame(8, 8, HCN(0, 8, 0, 8)));
	mHH_Dan = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	mHH_HieuUngPhatNo = new HoatHinh(lDSTTFrame);
}

DanNo1::~DanNo1()
{
	if (mHH_Dan)
		delete mHH_Dan;

	if (mHH_HieuUngPhatNo)
		delete mHH_HieuUngPhatNo;
}
