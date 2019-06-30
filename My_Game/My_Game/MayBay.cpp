#include "MayBay.h"
#include "Camera.h"
#include "DanLv.h"
#include "Sound.h"



MayBay::MayBay(const Vec2& in_ToaDo, std::vector<TenLua*>& in_DS_TenLua,
	std::vector<Bui*>& in_Bui, Item *in_Item)
	:
	DoiTuong(in_ToaDo, Vec2(), 24, 36)
{
	mItem = in_Item;
	mLoaiDoiTuong = eLDT_MayBay;
	ToaDo_XuatHien = in_ToaDo;

	for (auto TenLua : in_DS_TenLua)
	{
		mDS_TenLua.push_back(TenLua);
	}
	for (auto Bui : in_Bui)
	{
		mDS_Bui.push_back(Bui);
	}

	LoadThongTinHoatHinh();

	DiChuyen();
	mTrangThai = eTT_MayBay_PhatNo;
}

void MayBay::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (NamTrongCamera &&
		!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_MayBay_PhatNo;
		// xét tiếp Tọa độ ban đầu có Nằm trong Camera hay ko?
		mToaDo = ToaDo_XuatHien;
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			NamTrongCamera = false;
		}
	}
	// nếu đang nằm ngoài Camera mà ko có va chạm Camera thì ko có gì xảy ra
	else if (!NamTrongCamera &&
		VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		DiChuyen();
		NamTrongCamera = true;
	}


	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		if (TGDem < TG_PhatNo)
		{
			TGDem += in_tg;
			HH_PhatNo->CapNhat(in_tg);
		}
		return;
	}

	if (in_DoiTuong->get_ToaDo().x > mToaDo.x)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}

	TGDem += in_tg;

	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	if (HP <= 0)
	{
		PhatNo();
		Sound::getInstance()->play("Hieu_Ung_No", false, 1);
	}

	if (TGDem_Shining <= TG_Shining)
	{
		TGDem_Shining += in_tg;
	}

	HH_DiChuyen->CapNhat(in_tg);

	if (mTrangThai == eTT_MayBay_DiChuyen)
	{
		if (TGDem > 2.0f)
		{
			TGDem = 0.0f;
		}
		if (TGDem <= 1.0f)
		{
			mVanToc.y = VanTocBay;
		}
		else
		{
			mVanToc.y = -VanTocBay;
		}

		if (
			(mToaDo.y >= in_DoiTuong->get_ToaDo().y - 10.0f &&
				mToaDo.y <= in_DoiTuong->get_ToaDo().y + 10.0f))
		{
			BanDan();
		}
	}

	if (mTrangThai == eTT_MayBay_BanDan)
	{
		if (TGDem > TG_BanTenLua)
		{
			BoChay();
		}

		TGDem_BanTenLua += in_tg;

		if (TGDem_BanTenLua > TG_BanTenLua / 2.0f)
		{
			for (auto TL : mDS_TenLua)
			{
				if (TL->get_TrangThai() == eTT_TenLua_BienMat)
				{
					if (!mLatHinh)
					{
						TL->BanRa(mToaDo + Vec2(-10.0f, 14.0f), Vec2(-180.0f, 0.0f), true);
					}
					else
					{
						TL->BanRa(mToaDo + Vec2(10.0f, 14.0f), Vec2(180.0f, 0.0f), true);
					}

					break; // chỉ dùng 1 viên mỗi lần
				}
			}
			for (int i = 0; i < (int)mDS_Bui.size(); i++)
			{
				// chỉ sử dụng BỤi đã biến mất
				if (mDS_Bui[i]->get_BienMat())
				{
					if (mLatHinh)
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(3.0f, 14.0f));
					}
					else
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(-3.0f, 14.0f));
					}

					mDS_Bui[i]->Remake();
					break;
				}
			}
			TGDem_BanTenLua = 0.0f;
		}

	}

}

void MayBay::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		return;
	}

	// xét va chạm với đạn Lv đang tồn tại
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

		TGDem_Shining = 0.0f;
		HP -= ((DanLv*)in_DoiTuong)->get_Damage();
	}
}

void MayBay::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		if (TGDem < TG_PhatNo)
		{
			HH_PhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_PhatNo, in_DoDoi);
		}
		return;
	}
	if (TGDem_Shining <= TG_Shining)
	{
		HH_DiChuyen->Ve(DS_HinhAnh::get_TH()->MayBay_Shining_png, mLatHinh, mToaDo, in_DoDoi);
	}
	else
	{
		HH_DiChuyen->Ve(DS_HinhAnh::get_TH()->MayBay_png, mLatHinh, mToaDo, in_DoDoi);
	}
}


void MayBay::DiChuyen()
{
	mTrangThai = eTT_MayBay_DiChuyen;
	TGDem = 0.0f;
	mToaDo = ToaDo_XuatHien;
	HP = MAXHP;
}

void MayBay::BanDan()
{
	mTrangThai = eTT_MayBay_BanDan;
	TGDem = 0.0f;
	mVanToc.x = 0.0f;
	mVanToc.y = 0.0f;
	TGDem_BanTenLua = TG_BanTenLua / 2.2f;
}

void MayBay::BoChay()
{
	mTrangThai = eTT_MayBay_BoChay;
	TGDem = 0.0f;
	mVanToc.y = -VanTocBay;
}

void MayBay::PhatNo()
{
	mTrangThai = eTT_MayBay_PhatNo;
	HH_PhatNo->Remake();
	ToaDo_PhatNo = mToaDo;
	mToaDo = ToaDo_XuatHien;
	TGDem = 0.0f;
	mItem->Roi(mToaDo);
}

void MayBay::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 38, HCN(9, 9 + 40, 6, 6 + 38),     0.1f));
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(50, 50 + 28, 6 , 6 +38),   0.1f));
	lDSTTFrame.push_back(ThongTinFrame(24, 38, HCN(80, 80 + 24, 6 , 6 +38),   0.1f));
	lDSTTFrame.push_back(ThongTinFrame(24, 38, HCN(108, 108 + 24, 6 , 6 +38), 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(136, 136 + 28, 6 , 6 +38), 0.1f));
	HH_DiChuyen = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	HH_PhatNo = new HoatHinh(lDSTTFrame);
}

MayBay::~MayBay()
{
}
