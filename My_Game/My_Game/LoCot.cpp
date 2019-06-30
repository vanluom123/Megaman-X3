#include "LoCot.h"
#include "Camera.h"
#include "VaChamGame.h"
#include "DanLv.h"
#include "Sound.h"

LoCot::LoCot(const Vec2 & in_ToaDo, std::vector<DanNo1*>& in_DS_DanNo1, 
	std::vector<TenLua*>& in_DS_TenLua, std::vector<Bui*>& in_Bui, Item *in_Item)
	:
	DoiTuong(in_ToaDo, Vec2(), 28, 46)
{
	mLoaiDoiTuong = eLDT_LoCot;
	mItem = in_Item;

	LoadThongTinHoatHinh();

	for (int i = 0; i < (int)in_DS_DanNo1.size(); i++)
	{
		mDS_DanNo1.push_back(in_DS_DanNo1[i]);
	}
	for (int i = 0; i < (int)in_Bui.size(); i++)
	{
		mDS_Bui.push_back(in_Bui[i]);
	}// Gắn địa chỉ vào

	for (auto TL : in_DS_TenLua)
	{
		mDS_TenLua.push_back(TL);
	}

	mBui = new Bui(Vec2());
	mTrangThai = eTT_LoCot_BienMat;
	mNamTrongCamera = false;
}

void LoCot::CapNhat(float in_tg, const DoiTuong * in_XMan)
{
	if (mTGDem_HieuUngPhatNo <= TG_HieuUngPhatNo)
	{
		mTGDem_HieuUngPhatNo += in_tg;
		mHH_HieuUngPhatNo->CapNhat(in_tg);
	}

#pragma region XET CAMERA
	// nếu đang nằm trong Camera mà vẫn đang va chạm Camera thì ko có gì xảy ra
	if (mNamTrongCamera &&
		!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_LoCot_BienMat;
		// xét tiếp Tọa độ ban đầu có Nằm trong Camera hay ko?
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			mNamTrongCamera = false;
		}
	}
	// nếu đang nằm ngoài Camera mà ko có va chạm Camera thì ko có gì xảy ra
	else if (!mNamTrongCamera &&
		VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mNamTrongCamera = true;
		HP = MaxHP;
		BanTL();
	}
#pragma endregion

	if (mTrangThai == eTT_LoCot_BienMat)
		return;

	mHH_DuyNhat->CapNhat(in_tg);

	switch (mTrangThai)
	{
	case eTT_LoCot_BanDanNo:
		mTGDem_DanDuocBanRa += in_tg;
		if (mTGDem_DanDuocBanRa > TG_BanDan / 2.0f)
		{
			for (int i = 0; i < (int)mDS_DanNo1.size(); i++)
			{
				if (mDS_DanNo1[i]->get_TrangThai() == eTT_DanNo1_BienMat)
				{
					if (!mLatHinh)
					{
						mDS_DanNo1[i]->BanRa(mToaDo + Vec2(-8.0f, -19.0f), Vec2(-200.0f, -285.0f));
					}
					else
					{
						mDS_DanNo1[i]->BanRa(mToaDo + Vec2(8.0f, -19.0f), Vec2(200.0f, -285.0f));
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
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(8.0f, -19.0f));
					}
					else
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(-8.0f, -19.0f));
					}

					mDS_Bui[i]->Remake();
					break;
				}
			}

			mTGDem_DanDuocBanRa = 0.0f;
		}

		mTG_Dem += in_tg;
		if (mTG_Dem > TG_BanDan)
			BanTL();

		break;

	case eTT_LoCot_BanTenLua:
		mTGDem_DanDuocBanRa += in_tg;
		if (mTGDem_DanDuocBanRa > TG_BanDan / 2.0f)
		{
			for (auto TL : mDS_TenLua)
			{
				if (TL->get_TrangThai() == eTT_TenLua_BienMat)
				{
					if (!mLatHinh)
					{
						TL->BanRa(mToaDo + Vec2(-15.0f, -4.0f), Vec2(-180.0f, 0.0f));
					}
					else
					{
						TL->BanRa(mToaDo + Vec2(15.0f, -4.0f), Vec2(180.0f, 0.0f));
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
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(8.0f, -4.0f));
					}
					else
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(-8.0f, -4.0f));
					}

					mDS_Bui[i]->Remake();
					break;
				}
			}
			mTGDem_DanDuocBanRa = 0.0f;
		}

		mTG_Dem += in_tg;
		if (mTG_Dem > TG_BanTL)
			BanDan();

		break;

	default:
		break;
	}

	if (mToaDo.x - in_XMan->get_ToaDo().x < 0.0f)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}

	if (IsShining)
	{
		TGDem_IsShining += in_tg;
		if (TGDem_IsShining > 0.1f)
		{
			IsShining = false;
		}
	}

	if (HP <= 0)
	{
		BienMat();
		Sound::getInstance()->play("Hieu_Ung_No", false, 1);
	}
}

void LoCot::Ve(const Vec2 & in_DoDoi)
{
	if (mTGDem_HieuUngPhatNo <= TG_HieuUngPhatNo)
	{
		mHH_HieuUngPhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDoPhatNo, in_DoDoi);
	}

	if (mTrangThai == eTT_LoCot_BienMat)
	{
		return;
	}

	if (!IsShining)
	{
		mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->LoCot_png, mLatHinh, mToaDo, in_DoDoi);
	}
	else
	{
		mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->LoCot_Shining_png, mLatHinh, mToaDo, in_DoDoi);
	}
}

void LoCot::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_LoCot_BienMat)
	{
		return;
	}


	switch (in_DoiTuong->get_LoaiDoiTuong())
	{
	case eLDT_DanLv1:
	case eLDT_DanLv2:
	case eLDT_DanLv3:
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
		IsShining = true;
		break;
	default:
		break;
	}
}

void LoCot::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 44, HCN(1, 1 + 38, 3, 3 + 46)));
	mHH_DuyNhat = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	mHH_HieuUngPhatNo = new HoatHinh(lDSTTFrame);
}

void LoCot::BanDan()
{
	mTrangThai = eTT_LoCot_BanDanNo;
	mTG_Dem = 0.0f;
	mTGDem_DanDuocBanRa = 0.0f;
}

void LoCot::BanTL()
{
	mTrangThai = eTT_LoCot_BanTenLua;
	mTG_Dem = 0.0f;
	mTGDem_DanDuocBanRa = 0.0f;
}

void LoCot::BienMat()
{
	mTrangThai = eTT_LoCot_BienMat;
	mTGDem_HieuUngPhatNo = 0.0f;
	ToaDoPhatNo = mToaDo;
	mItem->Roi(mToaDo);
}

LoCot::~LoCot()
{
}
