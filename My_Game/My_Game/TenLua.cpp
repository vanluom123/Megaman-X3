#include "TenLua.h"
#include "DanLv.h"
#include "Camera.h"

#include "Sound.h"

// FUNCTION

TenLua::TenLua()
	:DoiTuong(Vec2(), Vec2(), 24, 8)
{
	mLoaiDoiTuong = eLDT_TenLua;
	mTrangThai = eTT_TenLua_BienMat;

	LoadThongTinHoatHinh();

}

void TenLua::CapNhat(float in_tg)
{

}

void TenLua::CapNhat(float in_tg, const DoiTuong * in_XMan)
{

	// nếu đạn đã bị phá hủy -> ko cần Cập Nhật
	if (mTrangThai == eTT_TenLua_BienMat)
	{
		return;
	}

	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	if (HP <= 0)
	{
		PhatNo();
	}

	TGDem_TuDongBienMat += in_tg;
	if (TGDem_TuDongBienMat > TG_TuDongBienMat)
	{
		mTrangThai = eTT_TenLua_BienMat;
	}

	if (mTrangThai == eTT_TenLua_PhatNo)
	{
		mHH_HieuUngPhatNo->CapNhat(in_tg);

		TGDem_NoTung += in_tg;
		if (TGDem_NoTung > TG_NoTung)
		{
			mTrangThai = eTT_TenLua_BienMat;
		}
	}

	if (!ChuyenDang)
	{
		if (mToaDo.y - in_XMan->get_ToaDo().y < 0.0f)
		{
			if (mVanToc.y < 0.0f)
				mVanToc.y = 0.0f;
			mVanToc.y += 300.0f * in_tg;
		}
		else
		{
			if (mVanToc.y >= 0.0f)
				mVanToc.y = 0.0f;
			mVanToc.y -= 300.0f * in_tg;
		}
	}
}

void TenLua::Ve(const Vec2 & in_DoDoi)
{
	// nếu đã bị phá hủy -> ko cần phải Vẽ ra
	if (mTrangThai == eTT_TenLua_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_TenLua_PhatNo)
	{
		mHH_HieuUngPhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false , mToaDo, in_DoDoi);
	}
	else
	{
		if (!ChuyenDang)
		{
			mHH_Dan->Ve(DS_HinhAnh::get_TH()->LoCot_png, (mVanToc.x > 0.0f), mToaDo, in_DoDoi);
		}
		else
		{
			HH_ChuyenDang->Ve(DS_HinhAnh::get_TH()->MayBay_png, (mVanToc.x > 0.0f), mToaDo, in_DoDoi);
		}
	}
}

void TenLua::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	// nếu đã bị phá hủy -> ko cần phải xét va chạm
	if (mTrangThai == eTT_TenLua_BienMat ||
		mTrangThai == eTT_TenLua_PhatNo)
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

		PhatNo();
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

void TenLua::BanRa(const Vec2 & in_ToaDo, const Vec2 & in_VanToc, bool in_ChuyenDang)
{
	ChuyenDang = in_ChuyenDang;
	mToaDo = in_ToaDo;
	mVanToc = in_VanToc;
	mTrangThai = eTT_TenLua_TonTai;
	TGDem_TuDongBienMat = 0.0f;
}

void TenLua::PhatNo()
{	
	mVanToc.x = 0.0f;
	mVanToc.y = 0.0f;
	mTrangThai = eTT_TenLua_PhatNo;
	TGDem_NoTung = 0.0f;
	mHH_HieuUngPhatNo->Remake();
	HP = MAXHP;
	if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		Sound::getInstance()->play("Hieu_Ung_No", false, 1);
	}
}

void TenLua::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;


	lDSTTFrame.push_back(ThongTinFrame(24, 8, HCN(200, 224, 11, 19)));
	mHH_Dan = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 10, HCN(138, 138 + 16, 68, 68 + 10)));
	HH_ChuyenDang = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	mHH_HieuUngPhatNo = new HoatHinh(lDSTTFrame);


}

TenLua::~TenLua()
{
	if (mHH_Dan)
		delete mHH_Dan;

	if (mHH_HieuUngPhatNo)
		delete mHH_HieuUngPhatNo;
}

