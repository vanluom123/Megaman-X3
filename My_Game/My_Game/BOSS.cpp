#include "BOSS.h"
#include <cmath>
#include "VaChamGame.h"
#include <ctime>
#include "Sound.h"

BOSS::BOSS(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 26, 46),
	ViTri1(7710.0f, 1880.0f),
	ViTri2(7904.0f, 1880.0f),
	ViTri3(7810.0f, 1876.f)
{
	mLoaiDoiTuong = eLDT_BOSS;
	ViTri_CanDenHienTai = ViTri2;
	for (int i = 0; i < 5; i++)
	{
		DS_OngCon[i] = new OngCon();
	}
	ToaDo_XuatHien = in_ToaDo;
	mHongTam = new HongTam();
	LoadThongTinHoatHinh();
	srand((int)time(NULL));
	BienMat();
}

void BOSS::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{

	if (mTrangThai == eTT_BOSS_BienMat)
	{
		if (in_DoiTuong->get_ToaDo().x >= 7683.0f && in_DoiTuong->get_ToaDo().x <= 7690.0f)
		{
			XuatHien();
		}
		return;
	}

	DX = in_DoiTuong->get_ToaDo().x - mToaDo.x;
	DY = in_DoiTuong->get_ToaDo().y - mToaDo.y;
	HH_HienTai->CapNhat(in_tg);
	HH_CanhOng->CapNhat(in_tg);
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;
	DEM += in_tg;
	KC_BOSS_XMAN = mToaDo.x - in_DoiTuong->get_ToaDo().x;
	DEM_KoAnDan += in_tg;
	DEM_KoAnDan2 += in_tg;
	if (DEM_KoAnDan2 >= 0.1f)
	{
		DEM_KoAnDan2 = 0.0f;
	}

	if (mTrangThai == eTT_BOSS_XuatHien)
	{
		const float WaitingTime = 2.0f;
		if (DEM < WaitingTime)
		{
			mVanToc = Vec2();
		}
		if (DEM >= WaitingTime &&
			DEM < 1.2f + WaitingTime)
		{
			mVanToc = Vec2(0.0f, 90.0f);
		}
		if (DEM >= 1.2 + WaitingTime &&
			DEM < 2.05f + WaitingTime)
		{
			mVanToc = Vec2();
			HH_HienTai = HH_ThaOng;
		}
		if (DEM >= 2.05f + WaitingTime &&
			DEM < 2.8f + WaitingTime)
		{
			HH_HienTai = HH_ChuanBiDamKim;
		}
		if (DEM >= 2.8f + WaitingTime &&
			DEM < 3.8f + WaitingTime)
		{
			HH_HienTai = HH_DamKim;
		}
		if (DEM >= 3.8f + WaitingTime &&
			DEM < 5.0f + WaitingTime)
		{
			if (HP_DuTru > 0)
			{
				HP_DuTru -= 2;
				HP += 2;
				if (HP > MAXHP)
				{
					HP = MAXHP;
				}
				Sound::getInstance()->play("XMan_Hoi_Mau", false, 1);
			}
		}
		if (DEM >= 5.0f + WaitingTime &&
			DEM < 5.2f + WaitingTime)
		{
			mVanToc.y = -40.0f;
			mVanToc.x = -30.0f;
			if (!PlaySound_NhacDanhBoss)
			{
				Sound::getInstance()->stop("Nhac_Nen");
				Sound::getInstance()->play("Nhac_Danh_Boss", true, 0);
				PlaySound_NhacDanhBoss = true;
			}
		}
		if (DEM >= 5.2f + WaitingTime)
		{
			ChuanBiDamKim();
			DEM = 0.0f;
		}
	}
	if (mTrangThai == eTT_BOSS_ChuanBiDamKim)
	{
		if (KC_BOSS_XMAN < 0)
		{
			LatHinh = true;
		}
		else
		{
			LatHinh = false;
		}
		if (DEM > TG_ChuanBiDamKim)
		{
			DamKim();
			DEM = 0.0f;
		}
	}
	if (mTrangThai == eTT_BOSS_DamKim)
	{

		if (DEM > TG_DamKim)
		{
			if (HP < MAXHP / 2)
			{
				ViTri_CanDenHienTai = ViTri3;
				VaoViTri(ViTri_CanDenHienTai);
			}
			else
			{
				VaoViTri(ViTri_CanDenHienTai);
			}
		}
	}
	if (mTrangThai == eTT_BOSS_VaoViTri)
	{

		if (HP < MAXHP / 2)
		{
			if (ViTri_CanDenHienTai.x != ViTri3.x ||
				ViTri_CanDenHienTai.y != ViTri3.y)
			{
				ViTri_CanDenHienTai = ViTri3;
				VaoViTri(ViTri_CanDenHienTai);
			}
			if (VaChamGame::get_DiemVaHCN((int)mToaDo.x, (int)mToaDo.y, HCN(
				(int)ViTri3.x - 2, (int)ViTri3.x + 2,
				(int)ViTri3.y - 2, (int)ViTri3.y + 2)))
			{
				BayVongVong();
				mVanToc = Vec2();
				mToaDo = ViTri3;
			}
		}
		else if (VaChamGame::get_DiemVaHCN((int)ViTri_CanDenHienTai.x, (int)ViTri_CanDenHienTai.y, get_HCNGioiHan()))
		{
			ThaOng();
			DEM = 0.0f;
		}
	}
	if (mTrangThai == eTT_BOSS_ThaOng)
	{
		if (DEM > 0.45f && !DaThaOng)
		{
			Vec2 lToaDo;
			if (LatHinh)
			{
				lToaDo = mToaDo + Vec2(31.0f, 0.0f);
			}
			else
			{
				lToaDo = mToaDo + Vec2(-31.0f, 0.0f);
			}
			float K = sqrt((130.0f * 130.0f) / (DX * DX + DY * DY));
			Vec2 lVanToc = Vec2(DX * K, DY * K);

			for (int i = 0; i < 5; i++)
			{
				int l = rand() % 50 - 25;
				int r = rand() % 50 - 25;
				DS_OngCon[i]->BanRa(lToaDo, lVanToc + Vec2(30.0f - 15.0f * i + (float)l, 
					-30.0f + 15.0f * i + r));
			}
			DaThaOng = true;
		}
		if (DEM > TG_ThaOng)
		{
			BayVongSo8();
		}
	}
	if (mTrangThai == eTT_BOSS_BayVongSo8)
	{
		GocSin += in_tg * 230;
		mVanToc.y = 120.0f * (float)sin(GocSin * VAL);

		if (mToaDo.x < ViTri1.x - 20.0f)
		{
			mVanToc.x = VanTocX_VongSo8;
		}

		if (mToaDo.x > ViTri2.x + 20.0f)
		{
			mVanToc.x = -VanTocX_VongSo8;
		}
		if (KC_BOSS_XMAN < 0)
		{
			LatHinh = true;
		}
		else
		{
			LatHinh = false;
		}

		if (VaChamGame::get_DiemVaHCN((int)ViTri_CanDenHienTai.x, (int)ViTri_CanDenHienTai.y, get_HCNGioiHan()))
		{
			ChuanBiDamKim();
			DEM = 0.0f;
		}
	}
	if (mTrangThai == eTT_BOSS_BayVongVong)
	{
		for (int i = 0; i < 5; i++)
		{
			int l = rand() % 81 - 40;
			int r = rand() % 81 - 40;
			if (mHongTam->get_TrangThai() == eTT_HongTam_LockMucTieu)
			{
				DS_OngCon[i]->TanCongMucTieu();
			}
			else if (DS_OngCon[i]->get_TrangThai() == eTT_OngCon_ChoDoiHongTam)
			{
				DS_OngCon[i]->set_VanToc(mVanToc + Vec2((float)l, (float)r));
			}
		}
		if (DEM > 6.0f)
		{
			DEM = 0.0f;
			DEM_SinhOng = 0.0f;
			HH_HienTai = HH_Bay;
			HH_SinhOng->Remake();
			mHongTam->DiChuyen(mToaDo);
		}

		if (DEM >= 2.0f)
		{
			if (DEM_SinhOng >= 1.0f)
			{
				DEM_SinhOng = 0.0f;
				// Viết hàm Sinh Ong
				for (int i = 0; i < 5; i++)
				{
					if (DS_OngCon[i]->get_TrangThai() == eTT_OngCon_BienMat)
					{
						if (LatHinh)
						{
							DS_OngCon[i]->ChoDoiHongTam(mToaDo + Vec2(10.0f, 22.0f));
						}
						else
						{
							DS_OngCon[i]->ChoDoiHongTam(mToaDo + Vec2(-10.0f, 22.0f));
						}
						break;
					}
				}
			}
			DEM_SinhOng += in_tg;
			HH_HienTai = HH_SinhOng;
		}

		if (GocSin >= 270.0f + 360.0f)
		{
			GocSin = -90.0f;
			mToaDo = ViTri3;
		}

		mVanToc.y = VanToc_VONGVONG * (float)sin(GocSin * VAL);
		float lVanTocXThichUng = sqrt(VanToc_VONGVONG * VanToc_VONGVONG - mVanToc.y * mVanToc.y) / 1.1f;

		if (GocSin >= -90.0f && GocSin < 90.0f ||
			GocSin >= 90.0f + 360.0f && GocSin < 270.0f + 360.0f)
		{
			mVanToc.x = -lVanTocXThichUng;
		}
		else if (GocSin >= 90.0f && GocSin < 90.0f + 360.0f)
		{
			mVanToc.x = lVanTocXThichUng;
		}

		if (KC_BOSS_XMAN < 0)
		{
			LatHinh = true;
		}
		else
		{
			LatHinh = false;
		}
		GocSin += in_tg * 190;
	}
	if (mTrangThai != eTT_BOSS_PhatNo &&
		mTrangThai != eTT_BOSS_XuatHien &&
		HP <=0)
	{
		PhatNo();
		DEM = 0.0f;
	}
	if (mTrangThai == eTT_BOSS_PhatNo)
	{
		if (HH_PhatNo->get_ViTriFrame() == 8)
		{
			index_ToaDoNgauNhien++;
			if (index_ToaDoNgauNhien > 10)
			{
				index_ToaDoNgauNhien = 0;
			}
			ToaDo_PhatNoHienTai = ToaDo_NgauNhien[index_ToaDoNgauNhien];
			HH_PhatNo->Remake();
			Sound::getInstance()->play("Hieu_Ung_No", false, 1);
		}
		HH_PhatNo->CapNhat(in_tg);
		if (DEM_NhapNhayLucBiDanhBai > 0.06f)
		{
			DEM_NhapNhayLucBiDanhBai = 0.0f;
		}
		DEM_NhapNhayLucBiDanhBai += in_tg;
		if (DEM > 5.0f)
		{
			BienMat();
			Sound::getInstance()->stop("Nhac_Danh_Boss");
			Sound::getInstance()->play("Diet_Xong_Boss", false, 1);
		}
	}
}

void BOSS::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_BOSS_XuatHien ||
		mTrangThai == eTT_BOSS_PhatNo ||
		mTrangThai == eTT_BOSS_BienMat)
	{
		return;
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

		if (DEM_KoAnDan <= TG_KoAnDan)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		HP -= ((DanLv*)in_DoiTuong)->get_Damage();
		DEM_KoAnDan = DEM_KoAnDan2 = 0.0f;
	}

	if (mTrangThai == eTT_BOSS_DamKim)
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh ||
			in_DoiTuong->get_LoaiDoiTuong() == eLDT_CuaDanhBoss)
		{
			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

			if (lKQVC.eKQVC_DaVaCham)
			{

				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
				switch (lPVC)
				{
				case ePVC_Duoi:
					mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					mVanToc = Vec2();
					break;
				case ePVC_Tren:
					mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					break;


				case ePVC_TraiTren:
				case ePVC_Trai:
				case ePVC_TraiDuoi:
					mToaDo.x += lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
					mVanToc = Vec2();
					break;

				case ePVC_Phai:
				case ePVC_PhaiTren:
				case ePVC_PhaiDuoi:
					mToaDo.x -= lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
					mVanToc = Vec2();
					break;

				default:
					break;
				}
			}
		}
	}

}

void BOSS::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_BOSS_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_BOSS_PhatNo)
	{
		if (DEM_NhapNhayLucBiDanhBai < 0.03f)
		{
			HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(175, 255, 255, 255));
		}
		else
		{
			HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(150, 255, 255, 255));
		}
		HH_PhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo2, false, ToaDo_PhatNoHienTai, in_DoDoi);
	}
	else
	{
		HH_CanhOng->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo + Vec2(0.0f, -29.0f), in_DoDoi);
		HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi);
		if (DEM_KoAnDan < TG_KoAnDan)
		{
			if (DEM_KoAnDan2 < 0.033f)
			{
				HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS_Shining1, LatHinh, mToaDo, in_DoDoi);
			}
			else if (DEM_KoAnDan2 < 0.066f)
			{
				HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS_Shining2, LatHinh, mToaDo, in_DoDoi);
			}
			else
			{
				HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi);
			}
		}
	}
}

void BOSS::XuatHien()
{
	mTrangThai = eTT_BOSS_XuatHien;
	HH_ChuanBiDamKim->Remake(1);
	HH_DamKim->Remake(1);
	HH_ThaOng->Remake(1);
	HH_HienTai = HH_Bay;

	HP = 0;
	HP_DuTru = MAXHP;
	mToaDo = ToaDo_XuatHien;
	LatHinh = false;
	ViTri_CanDenHienTai = ViTri2;
	DEM = 0.0f;

	PlaySound_NhacDanhBoss = false;
}

void BOSS::BayVongSo8()
{
	GocSin = 90.0f;
	mTrangThai = eTT_BOSS_BayVongSo8;
	HH_HienTai = HH_Bay;
	// thay đổi vị trí để chuẩn bị bay vòng 8
	if (ViTri_CanDenHienTai.x == ViTri1.x)
	{
		ViTri_CanDenHienTai = ViTri2;
		LatHinh = true;
	}
	else
	{
		ViTri_CanDenHienTai = ViTri1;
		LatHinh = false;
	}
	if (ViTri_CanDenHienTai.x == ViTri1.x)
	{
		mVanToc.x = -VanTocX_VongSo8;
	}
	else
	{
		mVanToc.x = VanTocX_VongSo8;
	}
}

void BOSS::BayVongVong()
{
	GocSin = -90.0f;
	mTrangThai = eTT_BOSS_BayVongVong;
	HH_HienTai = HH_Bay;
	HH_HienTai->Remake();
	DEM = 10.0f;
	DEM_SinhOng = 0.0f;
}

void BOSS::PhatNo()
{
	DEM_SoundHieuUngNo = 0.0f;
	for (int i = 0; i < 10; i++)
	{
		int w = rand() % 51 - 25;
		int h = rand() % 51 - 25;
		ToaDo_NgauNhien[i] = Vec2(mToaDo + Vec2((float)w, (float)h));
	}
	index_ToaDoNgauNhien = 0;
	ToaDo_PhatNoHienTai = ToaDo_NgauNhien[index_ToaDoNgauNhien]; //nhận tọa độ ngãu nhiên đầu tiên
	HH_PhatNo->Remake();
	mTrangThai = eTT_BOSS_PhatNo;
	DEM_NhapNhayLucBiDanhBai = 0.0f;
	HH_HienTai = HH_BiDanhBai;
	mVanToc = Vec2();
	for (int i = 0; i < 5; i++)
	{
		if (DS_OngCon[i]->get_TrangThai() != eTT_OngCon_BienMat &&
			DS_OngCon[i]->get_TrangThai() != eTT_OngCon_PhatNo)
		{
			DS_OngCon[i]->PhatNo();
		}
	}
	if (mHongTam->get_TrangThai() != eTT_HongTam_BienMat)
	{
		mHongTam->BienMat();
	}
}

void BOSS::BienMat()
{
	mTrangThai = eTT_BOSS_BienMat;
	for (int i = 0; i < 5; i++)
	{
		DS_OngCon[i]->BienMat();
	}
	mHongTam->BienMat();
	mToaDo = ToaDo_XuatHien;
	mVanToc = Vec2();
}

void BOSS::ChuanBiDamKim()
{
	mTrangThai = eTT_BOSS_ChuanBiDamKim;
	HH_HienTai = HH_ChuanBiDamKim;
	HH_HienTai->Remake();
	mVanToc = Vec2();
}

void BOSS::DamKim()
{
	mTrangThai = eTT_BOSS_DamKim;

	float K = sqrt((VanTocTiepCan * VanTocTiepCan) / (DX * DX + DY * DY));
	mVanToc = Vec2(DX * K, DY * K);
	HH_HienTai = HH_DamKim;
	HH_HienTai->Remake();
}

void BOSS::VaoViTri(const Vec2 & in_ViTriCanDen)
{
	mTrangThai = eTT_BOSS_VaoViTri;
	float lDX = in_ViTriCanDen.x - mToaDo.x;
	float lDY = in_ViTriCanDen.y - mToaDo.y;
	float K = sqrt((VanTocBay * VanTocBay) / (lDX * lDX + lDY * lDY));
	mVanToc = Vec2(lDX * K,  lDY * K);
	HH_HienTai = HH_Bay;
	if (ViTri_CanDenHienTai.x == ViTri1.x)
	{
		LatHinh = true;
	}
	else
	{
		LatHinh = false;
	}
}

void BOSS::ThaOng()
{
	mTrangThai = eTT_BOSS_ThaOng;
	HH_HienTai = HH_ThaOng;
	HH_HienTai->Remake();
	mVanToc = Vec2();
	DaThaOng = false;
}

void BOSS::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 36, HCN(10, 10 + 16, 10, 10 + 36)  , 0.05f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(31, 31 + 32, 10, 10 + 36)  , 0.05f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(67, 67 + 28, 10, 10 + 36)  , 0.05f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(30, 38, HCN(100, 100 + 30,10, 10 + 36) , 0.05f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(138, 138 + 32, 10, 10 + 36), 0.05f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(32, 52, HCN(177, 177 + 32, 10, 10 + 36), 0.05f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(32, 52, HCN(220, 220 + 32, 10, 10 + 36), 0.05f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(32, 54, HCN(261, 261 + 32, 10, 10 + 36), 0.05f)); // 8
	lDSTTFrame.push_back(ThongTinFrame(2, 2, HCN(0, 2, 0, 2), 0.02f)); // hình rỗng
	HH_PhatNo = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(96, 48, HCN(414, 414 + 96, 102, 102 + 48))); // 1
	HH_BiDanhBai = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),		0.6f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61, 61 + 44, 8, 8 + 60),		0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58),	0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54),   0.1f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(215, 215 + 40, 8, 8 + 54),   0.1f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54),	0.9f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(215, 215 + 40, 8, 8 + 54),	0.1f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54),	0.9f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(215, 215 + 40, 8, 8 + 54),	0.1f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54),	0.4f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58),	0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61, 61 + 44, 8, 8 + 60),		0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),		99.9f)); // 1
	HH_SinhOng = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 52, HCN(6, 6 + 50, 10, 10 + 62), 0.1f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(52, 58, HCN(263, 263 + 52, 4, 78),   0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(320, 320 + 48, 4, 78),   0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(56, 56, HCN(377, 377 + 48, 4, 78),   0.1f)); // 4 
	lDSTTFrame.push_back(ThongTinFrame(52, 54, HCN(431, 431 + 46, 4, 78),   0.1f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(483, 483 + 46, 4, 78),   0.1f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(320, 320 + 48, 4, 78),   0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(52, 58, HCN(263, 263 + 52, 4, 78),   0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(48, 52, HCN(6, 6 + 50, 10, 10 + 62), 99.9f)); // 1
	HH_ThaOng = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62))); // 1
	HH_Bay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),     0.06f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61,	61 + 44,  8, 8 + 60 ),  0.06f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58),   0.06f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(41, 41 + 40, 92, 92 + 54),   0.06f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58),   0.06f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(132, 132 + 40, 92, 92 + 58), 0.06f)); // 8 
	lDSTTFrame.push_back(ThongTinFrame(42 + 4, 56, HCN(177, 177 + 40, 93, 93 + 58), 0.06f)); // 9
	lDSTTFrame.push_back(ThongTinFrame(48 + 4, 56, HCN(222, 222 + 44, 93, 93 + 58), 0.06f)); // 10
	lDSTTFrame.push_back(ThongTinFrame(42 + 4, 56, HCN(272, 272 + 40, 94, 94 + 58), 0.06f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(48 + 4, 56, HCN(315, 315 + 44, 94, 94 + 58), 0.06f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(50 + 4, 56, HCN(364, 364 + 44, 94, 94 + 58), 0.06f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58), 99.9f)); // 7
	HH_ChuanBiDamKim = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58), 0.6f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(41, 41 + 40, 92, 92 + 54), 0.06f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58), 0.06f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61, 61 + 44, 8, 8 + 60),   0.06f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),   99.9f)); // 1
	HH_DamKim = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(94, 6, HCN(417, 417 + 98, 171, 171 + 24),	0.032f));
	lDSTTFrame.push_back(ThongTinFrame(94, 42, HCN(417, 417 + 98, 203, 203 + 42),	0.032f));
	HH_CanhOng = new HoatHinh(lDSTTFrame);
}

BOSS::~BOSS()
{
}
