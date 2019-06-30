#include "XMan.h"
#include <vector>
#include "VaChamGame.h"
#include "GameLog.h"
#include "Camera.h"
#include "Ech.h"
#include "DanNo1.h"
#include "TenLua.h"
#include "LoCot.h"
#include "ThangMay.h"
#include "TrucXoay.h"
#include "OngCon.h"
#include "Sound.h"



XMan::XMan(const Vec2& in_ToaDo)
	:DoiTuong(in_ToaDo, Vec2(), 18, 32)
{
	DoiTuong::mLoaiDoiTuong = eLDT_XMan;

	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i] = new Bui(Vec2());
	}

	mHieuUngLuot = new HieuUngLuot();
	mHieuUngBatRa = new HieuUngBatRa();

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		mDS_DanLv1[i] = new DanLv1();
	}

	mDanLv2 = new DanLv2();
	mDanLv3 = new DanLv3();

	LoadThongTinHoatHinh();

	XuatHien(in_ToaDo);
}

XMan::~XMan()
{

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		if (mDS_DanLv1[i])
			delete mDS_DanLv1[i];
	}

	if (mHH_DungIm)
	{
		delete mHH_DungIm;
	}
	if (mHH_DungIm_Ban)
	{
		delete mHH_DungIm_Ban;
	}

	if (mHH_ChuanBiChay)
	{
		delete mHH_ChuanBiChay;
	}
	if (mHH_ChuanBiChay_Ban)
	{
		delete mHH_ChuanBiChay_Ban;
	}

	if (mHH_Chay)
	{
		delete mHH_Chay;
	}
	if (mHH_Chay_Ban)
	{
		delete mHH_Chay_Ban;
	}

	if (mHH_Nhay)
	{
		delete mHH_Nhay;
	}
	if (mHH_Nhay_Ban)
	{
		delete mHH_Nhay_Ban;
	}
	
	if (mHH_TiepDat)
	{
		delete mHH_TiepDat;
	}
	if (mHH_TiepDat_Ban)
	{
		delete mHH_TiepDat_Ban;
	}

	if (mHH_Roi)
	{
		delete mHH_Roi;
	}
	if (mHH_Roi_Ban)
	{
		delete mHH_Roi_Ban;
	}

	if (mHH_Luot)
	{
		delete mHH_Luot;
	}
	if (mHH_Luot_Ban)
	{
		delete mHH_Luot_Ban;
	}

	if (mHH_Truot)
	{
		delete mHH_Truot;
	}
	if (mHH_Truot_Ban)
	{
		delete mHH_Truot_Ban;
	}

	if (mHH_BatRa)
	{
		delete mHH_BatRa;
	}
	if (mHH_BatRa_Ban)
	{
		delete mHH_BatRa_Ban;
	}

	for (int i = 0; i < mSoLuongBui; i++)
	{
		if (mDS_BuiKhiLuot[i])
		{
			delete mDS_BuiKhiLuot[i];
		}
	}
	if (mHieuUngBatRa)
		delete mHieuUngBatRa;
	if (mHieuUngLuot)
		delete mHieuUngLuot;
}

void XMan::CapNhat(float in_tg)
{
	if (HP_DuTru > 0)
	{
		HP_DuTru -= 3;
		mHP += 3;
		DEM_Sound_XMan_Hoi_Mau += in_tg;
	/*	if (DEM_Sound_XMan_Hoi_Mau >= 0.02f)
		{
			DEM_Sound_XMan_Hoi_Mau = 0.0f;*/
			Sound::getInstance()->play("XMan_Hoi_Mau", false, 1);
	/*	}*/

		if (mHP > 100)
		{
			mHP = 100;
			HP_DuTru = 0;
			//Sound::getInstance()->stop("XMan_Hoi_Mau");
		}
	}

	mToaDo.x += (mVanToc.x + VanTocKhachQuan.x)* in_tg;
	mToaDo.y += (mVanToc.y + VanTocKhachQuan.y)* in_tg;

	VanTocKhachQuan.x = 0.0f;
	VanTocKhachQuan.y = 0.0f;

	if (TGDem_ChayTuDo < TG_ChayTuDo)
	{
		TGDem_ChayTuDo += in_tg;
	}

	if (mToaDo.x >= 4800.0f &&
		mToaDo.x <= 4830.0f &&
		DEM_ChayTuDo2 > TG_ChayTuDo2)
	{
		DEM_ChayTuDo2 = 0.0f;
	}

	if (DEM_ChayTuDo2 <= TG_ChayTuDo2)
	{
		DEM_ChayTuDo2 += in_tg;
	}

	if ((mHP <= 0 && mTrangThai != eTT_XMan_PhatNo) ||
		(mToaDo.y > Camera::mGioiHanDuoi && mTrangThai != eTT_XMan_PhatNo))
	{
		PhatNo();
	}

	if (mTGDem_KoNhanST <= mTG_KoNhanST)
	{
		mTGDem_KoNhanST += in_tg;
		mTGDem_NhapNhay += in_tg;
		if (mTGDem_NhapNhay > 0.08f)
		{
			mTGDem_NhapNhay = 0.0f;
		}
	}

	if (mTG_DemTichDan > mTG_TichDanLv2 * 2.5f)
	{
		mHH_HieuUngNapDanLv3->CapNhat(in_tg);
		if (!PlaySound_GongSucKeoDai &&
			(mTG_DemTichDan > mTG_TichDanLv2 * 4.0f))
		{
			Sound::getInstance()->play("Gong_Suc_Keo_Dai", true, 0);
			PlaySound_GongSucKeoDai = true;
		}
	}
	else if (mTG_DemTichDan > mTG_TichDanLv2)
	{
		mHH_HieuUngNapDanLv2->CapNhat(in_tg);
		if (!PlaySound_GongSuc)
		{
			Sound::getInstance()->play("Gong_Suc", false, 1);
			PlaySound_GongSuc = true;
		}
	}



	if (mTG_DemTichDan > mTG_TichDanLv2)
	{
		mTimeCount_ChangeShining += in_tg;
		if (mIsShining)
		{
			if (mTimeCount_ChangeShining > mTimeChangeShining)
			{
				mTimeCount_ChangeShining = 0.0f;

				mIsShining = false;
			}
		}

		if (!mIsShining)
		{
			if (mTimeCount_ChangeShining > 1.5f * mTimeChangeShining)
			{
				mTimeCount_ChangeShining = 0.0f;

				mIsShining = true;


			}
		}
	}
	else
	{
		mIsShining = false;
	}

	if (mToaDo.x < Camera::mGioiHanTrai + float(mChieuRong / 2))
		mToaDo.x = Camera::mGioiHanTrai + float(mChieuRong / 2);

	if (mToaDo.x > Camera::mGioiHanPhai - float(mChieuRong / 2))
		mToaDo.x = Camera::mGioiHanPhai - float(mChieuRong / 2);

	if (mTrangThai != eTT_XMan_XuatHien)
	{
		if (mToaDo.y < Camera::mGioiHanTren - float(mChieuCao / 2))
			mToaDo.y = Camera::mGioiHanTren - float(mChieuCao / 2);
	}


	mTimes = in_tg;
	if (TGDem_ChayTuDo < TG_ChayTuDo)
	{
		mHH_HienTai->CapNhat(in_tg / 1.25f);
	}
	else
	{
		mHH_HienTai->CapNhat(in_tg);
	}


	switch (mTrangThai)
	{
	case eTT_XMan_PhatNo:
		CapNhat_PhatNo();
		break;

	case eTT_XMan_XuatHien:
		CapNhat_XuatHien();
		break;

	case eTT_XMan_DungIm:
		CapNhat_DungIm();
		break;

	case eTT_XMan_ChuanBiChay:
		CapNhat_ChuanBiChay(in_tg);
		break;

	case eTT_XMan_Chay:
		CapNhat_Chay();
		break;

	case eTT_XMan_TiepDat:
		CapNhat_TiepDat(in_tg);
		break;

	case eTT_XMan_Nhay:
		CapNhat_Nhay(in_tg);
		break;

	case eTT_XMan_Roi:
		CapNhat_Roi(in_tg);
		break;

	case eTT_XMan_Luot:
		CapNhat_Luot(in_tg);
		break;

	case eTT_XMan_BatRa:
		CapNhat_BatRa(in_tg);
		break;

	case eTT_XMan_Truot:
		CapNhat_Truot(in_tg);
		break;

	case eTT_XMan_DinhSatThuong:
		CapNhat_DinhSatThuong(in_tg);
		break;

	default:
		break;
	}

	mDangDungTuNhienRoi = true;

	mCoChuongNgaiVatTrai = mCoChuongNgaiVatPhai = false;

	//Cap Nhat Bui
	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i]->CapNhat(in_tg);
	}
	mHieuUngLuot->CapNhat(in_tg);

	if (mTrangThai != eTT_XMan_Luot)
	{
		mHieuUngLuot->BienMat();
	}

	mHieuUngBatRa->CapNhat(in_tg);
}

void XMan::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_XMan_PhatNo)
	{
		mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XManPhatNo_png, mLatHinh, mToaDo, in_DoDoi);

		for (int i = 0; i < 8; i++)
		{
			mHH_HatPhatNo->Ve(DS_HinhAnh::get_TH()->XManPhatNo_png, false, ToaDo_HatPhatNo[i], in_DoDoi);
		}
	}
	else if (mTGDem_KoNhanST < mTG_KoNhanST)
	{
		if ((mTGDem_NhapNhay < 0.04f))
		{
			mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XMan_png, mLatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(160, 255, 255, 255));
		}
		else
		{
			mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XMan_png, mLatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(210, 255, 255, 255));
		}
	}
	else
	{
		mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XMan_png, mLatHinh, mToaDo, in_DoDoi);
	}

	if (mIsShining)
	{
		DrawAnimationShining(in_DoDoi);
	}
	//Vẽ đối tượng Bụi, LayDa
	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i]->Ve(in_DoDoi);
	}

	mHieuUngLuot->Ve(in_DoDoi);
	mHieuUngBatRa->Ve(in_DoDoi);


	if (mTrangThai == eTT_XMan_PhatNo)
	{
		return;
	}

	if (mTG_DemTichDan > mTG_TichDanLv2 * 2.5f)
	{
		mHH_HieuUngNapDanLv3->Ve(DS_HinhAnh::get_TH()->HieuUngNapDanLv3_png, false, mToaDo, in_DoDoi);
	}
	else if (mTG_DemTichDan > mTG_TichDanLv2)
	{
		mHH_HieuUngNapDanLv2->Ve(DS_HinhAnh::get_TH()->HieuUngNapDanLv2_png, false, mToaDo, in_DoDoi);
	}



}

void XMan::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_XMan_PhatNo)
	{
		return;
	}

#pragma region XỬ LÝ BIẾN mDangDungTuNhienRoi
	if (mDangDungTuNhienRoi == true)
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_ThangMay ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh2)
		{
			HCN lHCNGioiHanMoRongDay = get_HCNGioiHan();
			lHCNGioiHanMoRongDay.Duoi += 2;

			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanMoRongDay, in_DoiTuong->get_HCNGioiHan());


			if (lKQVC.eKQVC_DaVaCham == true)
			{
				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

				if (lPVC == ePVC_Duoi)
				{
					mDangDungTuNhienRoi = false;

				}
			}
		}
	}
#pragma endregion


	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh2)
	{
		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (lKQVC.eKQVC_DaVaCham)
		{
			mToaDo.y-= 1.42f;
		/*	VanTocKhachQuan.y = -110.0f;*/

			ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

			switch (lPVC)
			{
			case ePVC_Duoi:
				if (mTrangThai == eTT_XMan_Roi)
				{
					TiepDat();
				}
				
				break;
			}
		}

	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_ThangMay)
	{
		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (lKQVC.eKQVC_DaVaCham)
		{
			ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
			switch (lPVC)
			{
			case ePVC_Duoi:
				mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_XMan_Roi)
				{
					TiepDat();
					mVanToc.y = 0.0f;
				}
				if (mTrangThai == eTT_XMan_Truot)
				{
					TiepDat();
				}
				break;
			case ePVC_Tren:
				mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_XMan_Nhay || mTrangThai == eTT_XMan_BatRa)
				{
					Roi();
				}
				break;


			case ePVC_TraiTren:
			case ePVC_Trai:
			case ePVC_TraiDuoi:
				mToaDo.x += lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				mCoChuongNgaiVatTrai = true;

				if (mLatHinh &&
					(mTrangThai == eTT_XMan_Chay || mTrangThai == eTT_XMan_ChuanBiChay))
				{
					DungIm();
				}
				break;

			case ePVC_Phai:
			case ePVC_PhaiTren:
			case ePVC_PhaiDuoi:
				mToaDo.x -= lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				mCoChuongNgaiVatPhai = true;

				if (!mLatHinh &&
					(mTrangThai == eTT_XMan_Chay || mTrangThai == eTT_XMan_ChuanBiChay))
				{
					DungIm();
				}

				break;

			default:
				break;
			}
		}
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh4)
	{
		if (mTrangThai == eTT_XMan_XuatHien)
		{
			return;
		}

		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (lKQVC.eKQVC_DaVaCham)
		{
			ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
			switch (lPVC)
			{
				
			case ePVC_Tren:
				mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_XMan_Nhay || mTrangThai == eTT_XMan_BatRa)
				{
					Roi();
				}
				break;

			}
		}
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Ech)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if (((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_BienMat ||
			((Ech*)in_DoiTuong)->get_TrangThai() == eTT_Ech_DangTanBien)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_LoCot)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if (((LoCot*)in_DoiTuong)->get_TrangThai() == eTT_LoCot_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanNo1)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if (((DanNo1*)in_DoiTuong)->get_TrangThai() == eTT_DanNo1_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Gai)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		PhatNo();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_TenLua)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if (((TenLua*)in_DoiTuong)->get_TrangThai() == eTT_TenLua_BienMat ||
			((TenLua*)in_DoiTuong)->get_TrangThai() == eTT_TenLua_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}


	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_TrucXoay)
	{
		if (VanTocKhachQuan.x != 0.0f ||
			VanTocKhachQuan.y != 0.0f)
		{
			return;
		}
		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (!lKQVC.eKQVC_DaVaCham)
		{
			return;
		}

		ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

		if (lPVC != ePVC_Duoi)
		{
			return;
		}

		if (((TrucXoay*)in_DoiTuong)->K == 1 ||
			((TrucXoay*)in_DoiTuong)->K == 2 ||
			((TrucXoay*)in_DoiTuong)->K == 4 ||
			((TrucXoay*)in_DoiTuong)->K == 6)
		{
			VanTocKhachQuan.x = -40.0f;
		}
		else if (((TrucXoay*)in_DoiTuong)->K == -1 ||
			((TrucXoay*)in_DoiTuong)->K == -2 ||
			((TrucXoay*)in_DoiTuong)->K == 3 ||
			((TrucXoay*)in_DoiTuong)->K == 5)
		{
			VanTocKhachQuan.x = 40.0f;
		}
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_CuaDanhBoss)
	{
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		if (TGDem_ChayTuDo > TG_ChayTuDo)
		{
			TGDem_ChayTuDo = 0.0f;
		}
	}
	
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_BOSS1)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if (in_DoiTuong->get_TrangThai() == eTT_BOSS1_XuatHien ||
			in_DoiTuong->get_TrangThai() == eTT_BOSS1_PhatNo || 
			in_DoiTuong->get_TrangThai() == eTT_BOSS1_BienMat )
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}
		
		mHP -= 5;
		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh3)
	{
		if (mVaChamDoiTuongTinh3)
		{
			return;
		}

		if (mTrangThai == eTT_XMan_Nhay ||
			mTrangThai == eTT_XMan_Roi ||
			mTrangThai == eTT_XMan_TiepDat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		mVaChamDoiTuongTinh3 = true;
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_MayBay)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if ((in_DoiTuong)->get_TrangThai() == eTT_MayBay_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Box)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if ((in_DoiTuong)->get_TrangThai() == eTT_Box_PhatNo ||
			(in_DoiTuong)->get_TrangThai() == eTT_Box_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanSang)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Item)
	{
		if (in_DoiTuong->get_TrangThai() == eTT_Item_BienMat)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		HP_DuTru += 15;

	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_OngCon)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}

		if (((OngCon*)in_DoiTuong)->get_KoTheGaySatThuong())
		{
			return;
		}

		if ((in_DoiTuong)->get_TrangThai() == eTT_OngCon_BienMat ||
			(in_DoiTuong)->get_TrangThai() == eTT_OngCon_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();

		((OngCon*)in_DoiTuong)->DEM_KoTheGaySatThuong = 0.0f;
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_BOSS)
	{
		if (mTrangThai == eTT_XMan_DinhSatThuong)
		{
			return;
		}
		if (mTGDem_KoNhanST < mTG_KoNhanST)
		{
			return;
		}
		if ((in_DoiTuong)->get_TrangThai() == eTT_BOSS_BienMat ||
			(in_DoiTuong)->get_TrangThai() == eTT_BOSS_PhatNo)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		DinhSatThuong();

		if ((in_DoiTuong)->get_TrangThai() == eTT_BOSS_DamKim)
		{
			mHP -= 10;
		}
	}
}

void XMan::XuLyBanPhim(std::map<int, bool> in_Keys)
{
	if (mTrangThai == eTT_XMan_PhatNo)
	{
		return;
	}

	if (mVaChamDoiTuongTinh3 &&
		mDangDungTuNhienRoi)
	{
		mDangDungTuNhienRoi = false;
		mToaDo.y += 1.42f;
	}
	mVaChamDoiTuongTinh3 = false;

	if (in_Keys['O'])
	{
		mHP -= 5;
	}
	if (in_Keys['D'])
	{
		HP_DuTru = 100;

	}

	if (mTrangThai == eTT_XMan_XuatHien)
	{
		in_Keys[FIRE_BUTTON] = false;
	}

	if (TGDem_ChayTuDo <= TG_ChayTuDo)
	{
		if (TGDem_ChayTuDo >= 2.0f &&
			TGDem_ChayTuDo <= 3.9f)
		{
			in_Keys[VK_RIGHT] = true;
			mVanToc.x = 20.0f;
		}
		else
		{
			in_Keys[VK_RIGHT] = false;
		}
		in_Keys[VK_LEFT] = false;
		in_Keys[JUMP_BUTTON] = false;
		in_Keys[FIRE_BUTTON] = false;
		in_Keys[PUSH_BUTTON] = false;
	}
	if (DEM_ChayTuDo2 <= TG_ChayTuDo2)
	{
		in_Keys[VK_RIGHT] = true;
		in_Keys[VK_LEFT] = false;
		in_Keys[JUMP_BUTTON] = false;
		in_Keys[FIRE_BUTTON] = false;
		in_Keys[PUSH_BUTTON] = false;
	}

	mKeys = in_Keys;

	switch (mTrangThai)
	{
	case eTT_XMan_DungIm:
		XuLyBanPhim_DungIm(in_Keys);
		break;

	case eTT_XMan_Chay:
		XuLyBanPhim_Chay(in_Keys);
		break;

	case eTT_XMan_Roi:
		XuLyBanPhim_Roi(in_Keys);
		break;

	case eTT_XMan_TiepDat:
		XuLyBanPhim_TiepDat(in_Keys);
		break;

	case eTT_XMan_ChuanBiChay:
		XuLyBanPhim_ChuanBiChay(in_Keys);
		break;

	case eTT_XMan_Nhay:
		XuLyBanPhim_Nhay(in_Keys);
		break;

	case eTT_XMan_Luot:
		XuLyBanPhim_Luot(in_Keys);
		break;

	case eTT_XMan_Truot:
		XuLyBanPhim_Truot(in_Keys);
		break;

	default:
		break;
	}

	if (mTrangThai == eTT_XMan_DinhSatThuong ||
		mTrangThai == eTT_XMan_PhatNo)
	{
		return;
	}
	XuLyBanPhim_BanDan(in_Keys);
}

void XMan::PhatNo()
{
	mTrangThai = eTT_XMan_PhatNo;
	mHH_HienTai = mHH_PhatNo;
	mHH_HienTai->Remake();
	mVanToc.x = mVanToc.y = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		ToaDo_HatPhatNo[i] = mToaDo;
	}
	Sound::getInstance()->play("XMan_Chet", false, 1);
}

void XMan::CapNhat_PhatNo()
{
	for (int i = 0; i < 8; i++)
	{
		ToaDo_HatPhatNo[i].x += VanToc_HatPhatNo[i].x * mTimes;
		ToaDo_HatPhatNo[i].y += VanToc_HatPhatNo[i].y * mTimes;
	}
	mHH_HatPhatNo->CapNhat(mTimes);
}

void XMan::XuatHien(const Vec2 & in_ToaDo)
{
	mToaDo = in_ToaDo;
	mTrangThai = eTT_XMan_XuatHien;
	mHH_HienTai = mHH_XuatHien;
	mHH_HienTai->Remake();
	TGDem = 0.0f;
	mVanToc.y = 580.0f;
	mHP = 100;
	mLatHinh = false;
	Sound::getInstance()->play("XMan_Hoi_Sinh", false, 1);
}

void XMan::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(6, 6, HCN(69, 69 + 6, 14, 14 + 6), 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(8, 8, HCN(79, 79 + 8, 13, 13 + 8), 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(10, 10, HCN(90, 90 + 10, 12, 12 + 10), 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(12, 12, HCN(102, 102 + 12, 11, 11 + 12), 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(115, 115 + 16, 8, 8 + 16), 99.9f));
	mHH_HatPhatNo = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(26, 36, HCN(0, 26, 0, 36), 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(26, 36, HCN(30, 30 + 26, 0, 36), 0.4f));
	lDSTTFrame.push_back(ThongTinFrame(2, 2, HCN(0, 2, 0, 2), 99.9f));
	mHH_PhatNo = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 36, HCN(77, 77 + 30, 848, 848 + 36), 0.2f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(110, 110 + 30, 849, 849 + 34), 0.2f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(143, 143 + 30, 849, 849 + 34), 0.2f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(110, 110 + 30, 849, 849 + 34), 0.2f));
	mHH_DungIm2 = new HoatHinh(lDSTTFrame);



#pragma region DUNG_IM
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(323, 323 + 30, 17, 17 + 34), 3.0f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(357, 357 + 30, 17, 17 + 34), 0.075f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(391, 391 + 30, 17, 17 + 34), 0.075f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(357, 357 + 30, 17, 17 + 34), 0.075f));
	mHH_DungIm = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(133, 163, 66, 100), 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(168, 197, 66, 100), 0.15f));
	mHH_DungIm_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region CHUAN_BI_CHAY
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 36, HCN(106, 106 + 30, 106, 106 + 36)));
	mHH_ChuanBiChay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 34,HCN(61, 96, 192, 226)));
	mHH_ChuanBiChay_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region CHAY
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame( 18, 38, HCN(137, 157, 105, 141), 0.05f)); //1 
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(157, 181, 105, 141), 0.05f)); //2
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(181, 212, 105, 141), 0.05f)); //3 
	lDSTTFrame.push_back(ThongTinFrame(36, 38, HCN(213, 247, 105, 141), 0.05f)); //4
	lDSTTFrame.push_back(ThongTinFrame(28, 38, HCN(247, 275, 105, 143), 0.05f)); //5
	lDSTTFrame.push_back(ThongTinFrame(22, 38, HCN(276, 298, 105, 141), 0.05f)); //6
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(298, 326, 105, 141), 0.05f)); //7
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(327, 357, 105, 141), 0.05f)); //8
	lDSTTFrame.push_back(ThongTinFrame(34, 38, HCN(357, 391, 105, 141), 0.05f)); //9
	lDSTTFrame.push_back(ThongTinFrame(30, 38, HCN(391, 421, 105, 141), 0.05f)); //10
	mHH_Chay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(18, 34, HCN(97, 126, 193, 227), 0.05f)); //1 
	lDSTTFrame.push_back(ThongTinFrame(24, 34, HCN(126, 158, 192, 227), 0.05f)); //2
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(158, 193, 193, 227), 0.05f)); //3 
	lDSTTFrame.push_back(ThongTinFrame(36, 32, HCN(194, 232, 194, 227), 0.05f)); //4
	lDSTTFrame.push_back(ThongTinFrame(28, 32, HCN(233, 267, 194, 227), 0.05f)); //5
	lDSTTFrame.push_back(ThongTinFrame(22, 34, HCN(267, 298, 193, 227), 0.05f)); //6
	lDSTTFrame.push_back(ThongTinFrame(26, 34, HCN(298, 331, 192, 227), 0.05f)); //7
	lDSTTFrame.push_back(ThongTinFrame(30, 34, HCN(331, 366, 193, 227), 0.05f)); //8
	lDSTTFrame.push_back(ThongTinFrame(34, 32, HCN(367, 404, 194, 227), 0.05f)); //9
	lDSTTFrame.push_back(ThongTinFrame(30, 32, HCN(404, 439, 194, 227), 0.05f)); //10
	mHH_Chay_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region NHAY
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(12, 38, HCN(230, 246, 59, 101), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(252, 272, 52, 100), 99.9f));
	mHH_Nhay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(10, 38, HCN(97, 121, 148, 189), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(16, 44, HCN(121, 148, 143, 189), 99.9f));
	mHH_Nhay_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region ROI
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(26, 36, HCN(274, 298, 59, 101), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 36, HCN(299, 327, 58, 100), 99.9f));
	mHH_Roi = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(26, 36, HCN(149, 180, 148, 189), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(24, 36, HCN(181, 212, 147, 189), 99.9f));
	mHH_Roi_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region TIEP_DAT
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(20, 32, HCN(331, 355, 62, 100), 0.06f));
	lDSTTFrame.push_back(ThongTinFrame(30, 30, HCN(356, 386, 68, 100), 99.9f));
	mHH_TiepDat = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(20, 32, HCN(213, 243, 151, 189), 0.06f));
	lDSTTFrame.push_back(ThongTinFrame(30, 30, HCN(243, 279, 157, 189), 99.9f));
	mHH_TiepDat_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region LUOT
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(285, 313, 154, 190), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(44, 38, HCN(317, 361, 153, 189), 99.9f));
	mHH_Luot = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(28, 28, HCN(361, 399, 158, 189), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(44, 18, HCN(404, 453, 163, 189), 99.9f));
	mHH_Luot_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region TRUOT
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(28, 48, HCN(144, 144 + 28, 527, 527 + 48)));
	mHH_Truot = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(36, 48, HCN(310, 342, 526, 568)));
	mHH_Truot_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

#pragma region BAT_RA
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 42, HCN(177, 177 + 30, 530, 530 + 42), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(28, 50, HCN(207, 207 + 28, 525, 525 + 50), 99.9f));
	mHH_BatRa = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(237, 268, 531, 569), 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(28, 40, HCN(379, 412, 529, 568), 99.9f));
	mHH_BatRa_Ban = new HoatHinh(lDSTTFrame);
#pragma endregion

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(115, 115 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(174, 174 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(227, 227 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(280, 280 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(330, 330 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(375, 375 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(431, 431 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(482, 482 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(533, 533 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(585, 585 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(647, 647 + 45, 0, 72), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 76, HCN(700, 700 + 45, 0, 72), 0.04f));
	mHH_HieuUngNapDanLv2 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(4,  50, HCN(23, 23 + 6, 12, 12 + 50), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(46, 46, HCN(60, 60 + 48, 15, 15 + 46), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 42, HCN(119, 119 + 44, 16, 16 + 42), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(38, 38, HCN(176, 176 + 40, 15, 15 + 38), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(36, 38, HCN(230, 230 + 38, 12, 12 + 46), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(34, 46, HCN(282, 282 + 36, 10, 10 + 46), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(34, 42, HCN(331, 331 + 34, 12, 12 + 44), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(44, 40, HCN(376, 376 + 46, 12, 12 + 40), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(40, 38, HCN(433, 433 + 44, 15, 15 + 38), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(40, 46, HCN(484, 484 + 42, 15, 15 + 46), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(38, 44, HCN(536, 536 + 40, 17, 17 + 44), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(44, 40, HCN(588, 588 + 46, 20, 20 + 40), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(42, 38, HCN(650, 650 + 44, 19, 19 + 38), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(36, 34, HCN(703, 703 + 38, 25, 25 + 34), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(34, 30, HCN(748, 748 + 36, 26, 26 + 30), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(32, 28, HCN(797, 797 + 34, 22, 22 + 28), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(30, 12, HCN(846, 846 + 32, 32, 32 + 12), 0.04f));
	lDSTTFrame.push_back(ThongTinFrame(40, 20, HCN(890, 890 + 30, 32, 32 + 20), 0.04f));
	mHH_HieuUngNapDanLv3 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(20, 36, HCN(15 + 25, 15 + 22 + 25, 13 + 689, 13 + 36 + 689), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(20, 36, HCN(40 + 25, 40 + 26 + 25, 13 + 689, 13 + 36 + 689), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(25, 52, HCN(68 + 25, 68 + 32 + 25, 4 + 689, 4 + 48 + 689), 0.08f));
	mHH_DinhSatThuong = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(8,  62, HCN(115, 115 + 8, 3, 51) , 0.4f));
	lDSTTFrame.push_back(ThongTinFrame(22, 62, HCN(127, 127 + 22, 3, 51), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(30, 62, HCN(153, 153 + 30, 3, 51), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(30, 62, HCN(187, 187 + 30, 3, 51), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(30, 62, HCN(221, 221 + 30, 3, 51), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(30, 62, HCN(255, 255 + 30, 3, 51), 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(30, 62, HCN(289, 289 + 30, 3, 51), 0.03f));
	mHH_XuatHien = new HoatHinh(lDSTTFrame);


}

void XMan::DungIm()
{
	mTrangThai = eTT_XMan_DungIm;
	if (!mBanDan)
	{
		if (mHP <= 20)
		{
			mHH_HienTai = mHH_DungIm2;
		}
		else
		{
			mHH_HienTai = mHH_DungIm;
		}
	}
	else
	{
		mHH_HienTai = mHH_DungIm_Ban;
	}
	mHH_HienTai->Remake();
	mVanToc = Vec2(0.0f, 0.0f);
	mDuocTangTocLucDangBay = false;
}

void XMan::ChuanBiChay()
{
	mTrangThai = eTT_XMan_ChuanBiChay;
	if (mBanDan)
	{
		mHH_HienTai = mHH_ChuanBiChay_Ban;
	}
	else
	{
		mHH_HienTai = mHH_ChuanBiChay;
	}
	mHH_HienTai->Remake();
	mTG_DemChuanBiChay = 0.0f;
}

void XMan::Chay()
{
	mTrangThai = eTT_XMan_Chay;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Chay;
	}
	else
	{
		mHH_HienTai = mHH_Chay_Ban;
	}
	mHH_HienTai->Remake();
}

void XMan::Nhay()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_XMan_Nhay;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Nhay;
	}
	else
	{
		mHH_HienTai = mHH_Nhay_Ban;
	}
	mHH_HienTai->Remake();
	mChoPhepNhay = false;
	Sound::getInstance()->play("XMan_Nhay", false, 1);
}

void XMan::Roi()
{
	mVanToc.y = 0;
	mTrangThai = eTT_XMan_Roi;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Roi;
	}
	else
	{
		mHH_HienTai = mHH_Roi_Ban;
	}
	mHH_HienTai->Remake();
	//GAMELOG("ROI");
}

void XMan::TiepDat()
{
	mTrangThai = eTT_XMan_TiepDat;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_TiepDat;
	}
	else
	{
		mHH_HienTai = mHH_TiepDat_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemTiepDat = 0.0f;
	mDuocTangTocLucDangBay = false;
	mVanToc.y = 0.0f;
	Sound::getInstance()->play("XMan_Tiep_Dat", false, 1);
}

void XMan::Luot()
{
	mTrangThai = eTT_XMan_Luot;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Luot;
	}
	else
	{
		mHH_HienTai = mHH_Luot_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemLuot = 0.0f;
	mChoPhepLuot = false;
	mDuocTangTocLucDangBay = true;
	mTG_DemBui = mTG_Bui;

	if (!mLatHinh)
	{
		mHieuUngLuot->LatHinh(true);
		mHieuUngLuot->set_ToaDo(mToaDo + Vec2(-14.0f, 2.0f));
	}
	else
	{
		mHieuUngLuot->LatHinh(false);
		mHieuUngLuot->set_ToaDo(mToaDo + Vec2(14.0f, 2.0f));
	}

	mHieuUngLuot->Remake();
}

void XMan::Truot()
{
	mVanToc = Vec2(0.0f, 0.0f);
	mTrangThai = eTT_XMan_Truot;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Truot;
	}
	else
	{
		mHH_HienTai = mHH_Truot_Ban;
	}
	mHH_HienTai->Remake();
	mDuocTangTocLucDangBay = false;
	mTG_DemBamTuong = 0.0f;
	mTG_DemBui = 0.0f;
}

void XMan::BatRa()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_XMan_BatRa;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_BatRa;
	}
	else
	{
		mHH_HienTai = mHH_BatRa_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemBatRa = 0.0f;

	mHieuUngBatRa->LatHinh(mLatHinh);
	mHieuUngBatRa->set_ToaDo(mToaDo);
	mHieuUngBatRa->Remake();
}

void XMan::DinhSatThuong()
{
	mTrangThai = eTT_XMan_DinhSatThuong;
	mHH_HienTai = mHH_DinhSatThuong;
	mHH_HienTai->Remake();
	if (!mLatHinh)
	{
		mVanToc.x = -20.0f;
	}
	else
	{
		mVanToc.x = 20.0f;
	}
	mVanToc.y = -30.0f;
	mHP -= 5;
	mTGDem_DinhST = 0.0f;
	mTGDem_KoNhanST = 0.0f;
	Sound::getInstance()->play("XMan_Bi_Thuong", false, 1);
}

void XMan::ChuyenHH_BanDan()
{
	int lViTri_Tam = mHH_HienTai->get_ViTriFrame();
	float lThoiGian_Tam = mHH_HienTai->get_ThoiGianDem();

	switch (mTrangThai)
	{
	case eTT_XMan_ChuanBiChay:
		mHH_HienTai = mHH_ChuanBiChay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Chay:
		mHH_HienTai = mHH_Chay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Nhay:
		mHH_HienTai = mHH_Nhay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Roi:
		mHH_HienTai = mHH_Roi_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_TiepDat:
		mHH_HienTai = mHH_TiepDat_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_DungIm:
		mHH_HienTai = mHH_DungIm_Ban;
		mHH_HienTai->Remake();
		break;

	case eTT_XMan_Luot:
		mHH_HienTai = mHH_Luot_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Truot:
		mHH_HienTai = mHH_Truot_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_BatRa:
		mHH_HienTai = mHH_BatRa_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	default:
		break;
	}
}

void XMan::ChuyenHH_KoBanDan()
{
	int lViTri_Tam = mHH_HienTai->get_ViTriFrame();
	float lThoiGian_Tam = mHH_HienTai->get_ThoiGianDem();

	switch (mTrangThai)
	{
	case eTT_XMan_ChuanBiChay:
		mHH_HienTai = mHH_ChuanBiChay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Chay:
		mHH_HienTai = mHH_Chay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Nhay:
		mHH_HienTai = mHH_Nhay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Roi:
		mHH_HienTai = mHH_Roi;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_TiepDat:
		mHH_HienTai = mHH_TiepDat;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_DungIm:
		mHH_HienTai = mHH_DungIm;
		mHH_HienTai->Remake();
		break;

	case eTT_XMan_Luot:
		mHH_HienTai = mHH_Luot;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_Truot:
		mHH_HienTai = mHH_Truot;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_XMan_BatRa:
		mHH_HienTai = mHH_BatRa;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	default:
		break;
	}
}

void XMan::CapNhat_DungIm()
{
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_ChuanBiChay(float in_tg)
{
	mTG_DemChuanBiChay += in_tg;
	if (mTG_DemChuanBiChay >= mTG_ChuanBiChay)
	{
		Chay();
	}
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_Chay()
{
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_TiepDat(float in_tg)
{
	mTG_DemTiepDat += in_tg;
	if (mTG_DemTiepDat >= mTG_TiepDat)
	{
		DungIm();
	}
}

void XMan::CapNhat_Nhay(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (!mKeys['C'])
	{
		mVanToc.y += mGiaTocTrongTruong * in_tg * 10;
	}
	if (mVanToc.y >= 0.0f)
	{
		Roi();
	}
}

void XMan::CapNhat_Roi(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (mVanToc.y > mVanTocRoiToiDa)
	{
		mVanToc.y = mVanTocRoiToiDa;
	}
}

void XMan::CapNhat_Luot(float in_tg)
{
	mTG_DemLuot += in_tg;
	mTG_DemBui += in_tg;
	if (mTG_DemBui >= mTG_Bui)
	{
		mTG_DemBui = 0.0f;
		for (int i = 0; i < mSoLuongBui; i++)
		{
			if (mDS_BuiKhiLuot[i]->get_BienMat())
			{
				if (!mLatHinh)
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(- float(mChieuRong / 2 + 3.0f), float(mChieuCao / 2) + 2.0f));
				}
				else
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(float(mChieuRong / 2 + 3.0f), float(mChieuCao / 2) + 2.0f));
				}
				mDS_BuiKhiLuot[i]->Remake();
				break;
			}
		}
	}

	if (mTG_DemLuot >= mTG_Luot)
	{
		DungIm();
	}
}

void XMan::CapNhat_BatRa(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	mTG_DemBatRa += in_tg;
	if (mTG_DemBatRa >= mTG_BatRa)
	{
		float lVanTocHienTai = mVanToc.y;
		Nhay();
		mHH_HienTai->Remake(1, 0.0f);
		mVanToc.y = lVanTocHienTai;
	}

}

void XMan::CapNhat_Truot(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg / 2.0f;
	if (mVanToc.y > mVanTocTruotToiDa)
	{
		mVanToc.y = mVanTocTruotToiDa;
	}
	if (!mCoChuongNgaiVatTrai && mLatHinh)
	{
		Roi();
	}
	if (!mCoChuongNgaiVatPhai && !mLatHinh)
	{
		Roi();
	}
	mTG_DemBui += in_tg;
	if (mTG_DemBui >= mTG_Bui)
	{
		mTG_DemBui = 0.0f;
		for (int i = 0; i < mSoLuongBui; i++)
		{
			if (mDS_BuiKhiLuot[i]->get_BienMat())
			{
				if (mLatHinh)
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(- float(mChieuRong / 2 + 5.0f), float(mChieuCao / 2) - 5.0f));
				}
				else
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(float(mChieuRong / 2 + 5.0f), float(mChieuCao / 2) - 5.0f));
				}
				mDS_BuiKhiLuot[i]->Remake();
				break;
			}
		}
	}
}

void XMan::CapNhat_DinhSatThuong(float in_tg)
{
	mTGDem_DinhST += in_tg;
	if (mTGDem_DinhST > mTG_DinhST)
	{
		Roi();
	}
}

void XMan::XuLyBanPhim_DungIm(std::map<int, bool> in_Keys)
{
	if (!in_Keys[VK_RIGHT] || !in_Keys[VK_LEFT])
	{
		if (in_Keys[VK_RIGHT] && !mCoChuongNgaiVatPhai)
		{
			mVanToc = Vec2(mVanTocChayToiDa, 0.0f);
			mLatHinh = false;
			ChuanBiChay();
		}
		if (in_Keys[VK_LEFT] && !mCoChuongNgaiVatTrai)
		{
			mVanToc = Vec2(-mVanTocChayToiDa, 0.0f);
			mLatHinh = true;
			ChuanBiChay();
		}
	}
	if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
	{
		Nhay();
	}
	if (!in_Keys[JUMP_BUTTON])
	{
		mChoPhepNhay = true;
	}
	if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
	{
		if (!mLatHinh)
		{
			if (!mCoChuongNgaiVatPhai)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
		}
		else
		{
			if (!mCoChuongNgaiVatTrai)
			{
				mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}
	}
	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_Chay(std::map<int, bool> in_Keys)
{
	if ((!in_Keys[VK_LEFT] && mLatHinh) ||
		(!in_Keys[VK_RIGHT] && !mLatHinh) ||
		(in_Keys[VK_LEFT] && in_Keys[VK_RIGHT]))
	{
		DungIm();
	}
	if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
	{
		Nhay();
	}
	if (!in_Keys[JUMP_BUTTON])
	{
		mChoPhepNhay = true;
	}
	if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
	{
		if (!mLatHinh)
		{
			mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
			Luot();
		}
		else
		{
			mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
			Luot();
		}
	}

	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_Roi(std::map<int, bool> in_Keys)
{
	if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
	{
		mVanToc.x = 0.0f;
		return;
	}
	if ((!in_Keys[VK_LEFT] && mLatHinh) ||
		(!in_Keys[VK_RIGHT] && !mLatHinh))
	{
		mVanToc.x = 0.0f;
	}
	if (in_Keys[VK_LEFT])
	{
		mLatHinh = true;
		mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
		if (mCoChuongNgaiVatTrai)
		{
			Truot();
		}
	}
	if (in_Keys[VK_RIGHT])
	{
		mLatHinh = false;
		mVanToc.x = (mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
		if (mCoChuongNgaiVatPhai)
		{
			Truot();
		}
	}
}

void XMan::XuLyBanPhim_TiepDat(std::map<int, bool> in_Keys)
{
	if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
	{
		mVanToc.x = 0.0f;
		return;
	}
	if ((!in_Keys[VK_LEFT] && mLatHinh) ||
		(!in_Keys[VK_RIGHT] && !mLatHinh))
	{
		mVanToc.x = 0.0f;
	}
	if (in_Keys[VK_LEFT])
	{
		mLatHinh = true;
		mVanToc.x = -mVanTocChayToiDa;
		Chay();
	}
	if (in_Keys[VK_RIGHT])
	{
		mLatHinh = false;
		mVanToc.x = mVanTocChayToiDa;
		Chay();
	}

	if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
	{
		Nhay();
	}
	if (!in_Keys[JUMP_BUTTON])
	{
		mChoPhepNhay = true;
	}

	if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
	{
		if (!mLatHinh)
		{
			mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
			Luot();
		}
		else
		{
			mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
			Luot();
		}
	}
	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_ChuanBiChay(std::map<int, bool> in_Keys)
{
	if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
	{
		mVanToc.x = 0.0f;
		return;
	}
	if ((!in_Keys[VK_LEFT] && mLatHinh) ||
		(!in_Keys[VK_RIGHT] && !mLatHinh))
	{
		mVanToc.x = 0.0f;
	}
	if (in_Keys[VK_LEFT])
	{
		mLatHinh = true;
		mVanToc.x = -mVanTocChayToiDa;
	}
	if (in_Keys[VK_RIGHT])
	{
		mLatHinh = false;
		mVanToc.x = mVanTocChayToiDa;
	}
	if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
	{
		Nhay();
	}
	if (!in_Keys[JUMP_BUTTON])
	{
		mChoPhepNhay = true;
	}
	if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
	{
		if (!mLatHinh)
		{
			mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
			Luot();
		}
		else
		{
			mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
			Luot();
		}
	}
	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_Nhay(std::map<int, bool> in_Keys)
{
	if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
	{
		mVanToc.x = 0.0f;
		return;
	}
	if ((!in_Keys[VK_LEFT] && mLatHinh) ||
		(!in_Keys[VK_RIGHT] && !mLatHinh))
	{
		mVanToc.x = 0.0f;
	}
	if (in_Keys[VK_LEFT])
	{
		mLatHinh = true;
		mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
	}
	if (in_Keys[VK_RIGHT])
	{
		mLatHinh = false;
		mVanToc.x = mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem;
	}
}

void XMan::XuLyBanPhim_Luot(std::map<int, bool> in_Keys)
{
	if (!in_Keys[PUSH_BUTTON])
	{
		DungIm();
	}
	if (mDangDungTuNhienRoi)
	{
		mDuocTangTocLucDangBay = false;
		Roi();
	}
	if (in_Keys[JUMP_BUTTON])
	{
		Nhay();
	}
	if (in_Keys[VK_LEFT] && !mLatHinh ||
		in_Keys[VK_RIGHT] && mLatHinh)
	{
		Chay();
	}
}

void XMan::XuLyBanPhim_Truot(std::map<int, bool> in_Keys)
{
	if (!in_Keys[VK_RIGHT] && !mLatHinh)
	{
		mTG_DemBamTuong += mTimes;
		if (mTG_DemBamTuong >= mTG_BamTuong)
		{
			mLatHinh = true;
			Roi();

		}
	}
	if (!in_Keys[VK_LEFT] && mLatHinh)
	{
		mTG_DemBamTuong += mTimes;
		if (mTG_DemBamTuong >= mTG_BamTuong)
		{
			mLatHinh = false;
			Roi();

		}
	}
	if (!in_Keys[JUMP_BUTTON])
	{
		mChoPhepNhay = true;
	}
	if ((in_Keys[JUMP_BUTTON]) && !mLatHinh && mChoPhepNhay) // XMan nhìn sang Trái
	{
		if (in_Keys[PUSH_BUTTON])
		{
			mDuocTangTocLucDangBay = true;
		}
		mChoPhepNhay = false;
		BatRa();
		mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
	}
	if ((in_Keys[JUMP_BUTTON]) && mLatHinh && mChoPhepNhay) // XMan nhìn sang Phải
	{
		if (in_Keys[PUSH_BUTTON])
		{
			mDuocTangTocLucDangBay = true;
		}
		mChoPhepNhay = false;
		BatRa();
		mVanToc.x = (mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
	}
}

void XMan::XuLyBanPhim_BanDan(std::map<int, bool> in_Keys)
{

	bool lBanDan_Tam = mBanDan;

	if (mBanDan)
	{
		mTG_DemBanDan += mTimes;
		if (mTG_DemBanDan >= mTG_BanDan)
		{
			mBanDan = false;
		}
	}
	if (in_Keys[FIRE_BUTTON] && mChoPhepBan)
	{
		mTG_DemBanDan = 0.0f;
		mBanDan = true;
		mChoPhepBan = false;

		// các đối tượng đạn bay ra
		BanDanLv1();
		Sound::getInstance()->play("Ban_Dan_Lv1", false, 1);
	}

	if (in_Keys[FIRE_BUTTON])
	{
		mTG_DemTichDan += mTimes;
	}
	if (!in_Keys[FIRE_BUTTON])
	{
		PlaySound_GongSuc = false;
		Sound::getInstance()->stop("Gong_Suc");
		PlaySound_GongSucKeoDai = false;
		Sound::getInstance()->stop("Gong_Suc_Keo_Dai");
		mChoPhepBan = true;

		if (mTG_DemTichDan > mTG_TichDanLv2 * 2.5f)
		{
			mTG_DemBanDan = 0.0f;
			mBanDan = true;
			mChoPhepBan = false;

			Sound::getInstance()->play("Ban_Dan_Lv3", false, 1);
			BanDanLv3();
		}
		else if (mTG_DemTichDan > mTG_TichDanLv2)
		{
			mTG_DemBanDan = 0.0f;
			mBanDan = true;
			mChoPhepBan = false;

			Sound::getInstance()->play("Ban_Dan_Lv2", false, 1);
			BanDanLv2();
		}

		mTG_DemTichDan = 0.0f;


	}

	if (mBanDan && (lBanDan_Tam != mBanDan))
	{
		ChuyenHH_BanDan();
	}
	if (!mBanDan && (lBanDan_Tam != mBanDan))
	{
		ChuyenHH_KoBanDan();
	}
}

void XMan::BanDanLv1()
{
	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		if (mDS_DanLv1[i]->get_TrangThai() == eTT_Dan_BienMat)
		{
			Vec2 lDoDoiDan = DoDoiDanLv1();

			mDS_DanLv1[i]->set_ToaDo(mToaDo + lDoDoiDan);

			if (!mLatHinh)
			{
				mDS_DanLv1[i]->set_VanToc(Vec2(DanLv1::mVanTocDan, 0.0f));
			}
			else
			{
				mDS_DanLv1[i]->set_VanToc(Vec2(-DanLv1::mVanTocDan, 0.0f));
			}

			if (mTrangThai == eTT_XMan_Truot)
			{
				if (mLatHinh)
				{
					mDS_DanLv1[i]->set_VanToc(Vec2(DanLv1::mVanTocDan, 0.0f));
				}
				else
				{
					mDS_DanLv1[i]->set_VanToc(Vec2(-DanLv1::mVanTocDan, 0.0f));
				}
			}

			mDS_DanLv1[i]-> Remake();
			break;
		}
	}
}

Vec2 XMan::DoDoiDanLv1() const
{
	Vec2 lDoDoi;

	if (mTrangThai == eTT_XMan_DungIm)
	{
		if (!mLatHinh)
		{
			lDoDoi = Vec2(16.0f, -2.0f);
		}
		else
		{
			lDoDoi = Vec2(-16.0f, -2.0f);
		}
	}
	else
	if (mTrangThai == eTT_XMan_Chay || mTrangThai == eTT_XMan_ChuanBiChay || mTrangThai ==  eTT_XMan_TiepDat)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(21.0f, -3.0f);
		else
			lDoDoi = Vec2(-21.0f, -3.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Luot)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(28.0f, 2.0f);
		else
			lDoDoi = Vec2(-28.0f, 2.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Nhay || mTrangThai == eTT_XMan_Roi)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(20.0f, -6.0f);
		else
			lDoDoi = Vec2(-20.0f, -6.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Truot)
	{
		if (mLatHinh)
		{
			lDoDoi = Vec2(20.0f, -4.0f);
		}
		else
		{
			lDoDoi = Vec2(-20.0f, -4.0f);
		}
	}
	else
	if (mTrangThai == eTT_XMan_BatRa)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(21.0f, -8.0f);
		else
			lDoDoi = Vec2(-21.0f, -8.0f);
	}

	return lDoDoi;
}

void XMan::BanDanLv2()
{
	if (mDanLv2->get_TrangThai() == eTT_Dan_BienMat)
	{
		Vec2 lDoDoiDan = DoDoiDanLv2();

		mDanLv2->set_ToaDo(mToaDo + lDoDoiDan);

		if (!mLatHinh)
		{
			mDanLv2->set_VanToc(Vec2(DanLv2::mVanTocDan, 0.0f));
		}
		else
		{
			mDanLv2->set_VanToc(Vec2(-DanLv2::mVanTocDan, 0.0f));
		}
		mDanLv2->set_LatHinh(mLatHinh);

		if (mTrangThai == eTT_XMan_Truot)
		{
			if (mLatHinh)
			{
				mDanLv2->set_VanToc(Vec2(DanLv2::mVanTocDan, 0.0f));
			}
			else
			{
				mDanLv2->set_VanToc(Vec2(-DanLv2::mVanTocDan, 0.0f));
			}
			mDanLv2->set_LatHinh(!mLatHinh);
		}

		mDanLv2->Remake();
	}
}

Vec2 XMan::DoDoiDanLv2() const
{
	Vec2 lDoDoi;

	if (mTrangThai == eTT_XMan_DungIm)
	{
		if (!mLatHinh)
		{
			lDoDoi = Vec2(24.0f, -1.0f);
		}
		else
		{
			lDoDoi = Vec2(-24.0f, -1.0f);
		}
	}
	else
	if (mTrangThai == eTT_XMan_Chay || mTrangThai == eTT_XMan_ChuanBiChay || mTrangThai == eTT_XMan_TiepDat)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(29.0f, -3.0f);
		else
			lDoDoi = Vec2(-29.0f, -3.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Luot)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(37.0f, 2.0f);
		else
			lDoDoi = Vec2(-37.0f, 2.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Nhay || mTrangThai == eTT_XMan_Roi)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(28.0f, -6.0f);
		else
			lDoDoi = Vec2(-28.0f, -6.0f);
	}
	else
	if (mTrangThai == eTT_XMan_Truot)
	{
		if (mLatHinh)
		{
			lDoDoi = Vec2(28.0f, 0.0f);
		}
		else
		{
			lDoDoi = Vec2(-28.0f, 0.0f);
		}
	}
	else
	if (mTrangThai == eTT_XMan_BatRa)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(29.0f, -8.0f);
		else
			lDoDoi = Vec2(-29.0f, -8.0f);
	}

	return lDoDoi;
}

void XMan::BanDanLv3()
{
	if (mDanLv3->get_TrangThai() == eTT_Dan_BienMat)
	{
		Vec2 lDoDoiDan = DoDoiDanLv2();

		mDanLv3->set_ToaDo(mToaDo + lDoDoiDan);

		if (!mLatHinh)
		{
			mDanLv3->set_VanToc(Vec2(DanLv3::mVanTocDan, 0.0f));
		}
		else
		{
			mDanLv3->set_VanToc(Vec2(-DanLv3::mVanTocDan, 0.0f));
		}
		mDanLv3->set_LatHinh(mLatHinh);

		if (mTrangThai == eTT_XMan_Truot)
		{
			if (mLatHinh)
			{
				mDanLv3->set_VanToc(Vec2(DanLv3::mVanTocDan, 0.0f));
			}
			else
			{
				mDanLv3->set_VanToc(Vec2(-DanLv3::mVanTocDan, 0.0f));
			}
			mDanLv3->set_LatHinh(!mLatHinh);
		}

		mDanLv3->Remake();
	}
}

void XMan::DrawAnimationShining(const Vec2 & in_DoDoi)
{
	mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XMan_Shining_png, mLatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(210, 255, 255, 255));
}

void XMan::get_DS_Dan(std::vector<DanLv*>& out)
{
	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		out.push_back(mDS_DanLv1[i]);
	}
	out.push_back(mDanLv2);
	out.push_back(mDanLv3);
}

