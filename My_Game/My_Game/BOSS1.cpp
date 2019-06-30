#include "BOSS1.h"
#include <time.h>    
#include "DanLv.h"
#include "VaChamGame.h"
#include "Sound.h"

BOSS1::BOSS1(const Vec2& in_ToaDo, CuaDanhBoss* in_CuaDanhBoss)
	:
	DoiTuong(in_ToaDo, Vec2(), 46, 46)
{
	mLoaiDoiTuong = eLDT_BOSS1;
	ToaDo_Pet = in_ToaDo - Vec2(0.0f, 170.0f);
	ToaDo_BanDau = in_ToaDo;
	srand((int)time(NULL));
	mCuaDanhBoss = in_CuaDanhBoss;

	LoadThongTinHoatHinh();

	BienMat();
}

void BOSS1::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (in_DoiTuong->get_ToaDo().x >= 2300.0f && in_DoiTuong->get_ToaDo().x <= 2315.0f &&
		in_DoiTuong->get_ToaDo().y >= 1050.0f && in_DoiTuong->get_ToaDo().y <= 1200.0f &&
		mTrangThai != eTT_BOSS1_XuatHien)
	{
		XuatHien();
	}

	if (mTrangThai == eTT_BOSS1_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_BOSS1_PhatNo)
	{
		TG_Dem += in_tg;

		if (!PlaySound_HieuUngNo)
		{
			Sound::getInstance()->play("Hieu_Ung_No", false, 1);
			PlaySound_HieuUngNo = true;
		}
		DEM_PlaySound += in_tg;
		if (DEM_PlaySound > 0.48f)
		{
			DEM_PlaySound = 0.0f;
			PlaySound_HieuUngNo = false;
		}


		if (TG_Dem > TG_PhatNo)
		{
			BienMat();
		}

		if (TGDem2 >= 0.0f && TGDem2 < 0.48f * 1 ||
			TGDem2 >= 0.48f * 4 && TGDem2 < 0.48f * 5)
		{
			mHH_HieuUngPhatNo[0]->CapNhat(in_tg);

		}
		else if (TGDem2 >= 0.48f * 1 && TGDem2 < 0.48f * 2||
			TGDem2 >= 0.48f * 5 && TGDem2 < 0.48f * 6)
		{
			mHH_HieuUngPhatNo[1]->CapNhat(in_tg);

		}
		else if (TGDem2 >= 0.48f * 2 && TGDem2 < 0.48f * 3||
			TGDem2 >= 0.48f * 6 && TGDem2 < 0.48f * 7)
		{
			mHH_HieuUngPhatNo[2]->CapNhat(in_tg);

		}
		else if (TGDem2 >= 0.48f * 3 && TGDem2 < 0.48f * 4 ||
			TGDem2 >= 0.48f * 7 && TGDem2 < 0.48f * 8)
		{
			mHH_HieuUngPhatNo[3]->CapNhat(in_tg);

		}

		TGDem2 += in_tg;
		TGDem3 += in_tg;
		if (TGDem3 > 0.1f)
		{
			TGDem3 = 0.0f;
		}

		return;
	}

	if (TGDem_Shining <= TG_Shining)
	{
		TGDem_Shining += in_tg;
	}

	if (HP <= 0)
	{
		PhatNo();
	}

	if (mTrangThai == eTT_BOSS1_XuatHien)
	{
		TG_Dem += in_tg;
		if (TG_Dem > 3.0f)
		{
			HH_HienTai->CapNhat(in_tg * 1.55f);
		}
		if (TG_Dem > 3.0f + (0.12f * 50) / 1.4f)
		{
			HH_HienTai = HH_TanCong;
		}

		if (TG_Dem > 3.0f && TG_Dem <= 3.0f + 0.25f * 7 * 2)
		{
			HH_ConPet->CapNhat(in_tg / 1.8f);
		}
		else if (TG_Dem > 3.0f * 0.25f * 7 * 2 && TG_Dem <= 3.0f * 0.25f * 14 * 2)
		{
			HH_ConPet->CapNhat(in_tg / 1.8f);
		}
		if (TG_Dem > 0.5f && TG_Dem <= 3.0f)
		{
			ToaDo_Pet.y += 55.0f * in_tg;
		}
		else if (TG_Dem > 5.0f && TG_Dem <= 8.5f)
		{
			ToaDo_Pet.y -= 55.0f * in_tg;
		}

		if (TG_Dem > 3.0f && TG_Dem <= 4.0f)
		{
			if (Color_AnhSang != 240)
			{
				Color_AnhSang+= 2;
			}
		}
		else
		{
			if (Color_AnhSang != 0)
			{
				Color_AnhSang -= 2;
			}
		}

		if (TG_Dem > 8.7f)
		{
			TanCong1();
		}
	}

	if (mTrangThai == eTT_BOSS1_TanCong1)
	{
		TG_Dem += in_tg;

		if (TG_Dem <= 1.5f)
		{
			HH_HienTai->CapNhat(in_tg * (TG_Dem + 1.5f) * 4.0f);
		}
		else
		{
			HH_HienTai->CapNhat(in_tg * 3.0f* 4.0f);
		}

		if (TG_Dem > 1.5f && TG_Dem <= 3.0f ||
			TG_Dem > 4.5f && TG_Dem <= 6.0f ||
			TG_Dem > 7.5f && TG_Dem <= 9.0f)
		{
			mToaDo.x -= 115.0f * in_tg;
			
			if ((TG_Dem > 2.2f && TG_Dem <= 2.7f ||
				TG_Dem > 5.2f && TG_Dem <= 5.7f ||
				TG_Dem > 8.2f && TG_Dem <= 8.7f) 
				&& mVanToc.y == 0.0f)
			{
				int l = rand() % 40 + 1;
				if (l <= 3)
				{
					mVanToc.y = -VanTocRoiToiDa *  1.4f;
				}
			}
		}
		else if (TG_Dem > 3.0f && TG_Dem <= 4.5f || 
			TG_Dem > 6.0f && TG_Dem <= 7.5f ||
			TG_Dem > 9.0f && TG_Dem <= 10.5f)
		{
			mToaDo.x += 115.0f * in_tg;
		}

		if (mToaDo.x != ToaDo_BanDau.x)
		{
			mVanToc.y += GiaTocTrongTruong * in_tg;
		}
		if (mToaDo.y > ToaDo_BanDau.y)
		{
			mVanToc.y = 0.0f;
			mToaDo.y = ToaDo_BanDau.y;
		}
		mToaDo.y += mVanToc.y * in_tg;

		if (TG_Dem > 10.6f)
		{
			TanCong2();
		}

	}

	if (mTrangThai == eTT_BOSS1_TanCong2)
	{
		TG_Dem += in_tg;

		if (TG_Dem <= 1.5f)
		{
			HH_HienTai->CapNhat(in_tg * (TG_Dem + 1.5f)* 4.0f);
		}
		else
		{
			HH_HienTai->CapNhat(in_tg * 3.0f * 4.5f);
		}

		if (TG_Dem > 1.5f && TG_Dem <= 3.0f)
		{
			mToaDo.x -= 115.0f * in_tg;
		}
		else if (TG_Dem > 3.0f && TG_Dem <= 4.5f)
		{
			mToaDo.y -= 74.0f * in_tg;
		}
		else if (TG_Dem > 4.5f && TG_Dem <= 6.0f)
		{
			mToaDo.x += 115.0f * in_tg;
		}
		else if (TG_Dem > 6.0f && TG_Dem <= 7.5f)
		{
			mToaDo.y += 74.0f * in_tg;
		}

		if (TG_Dem > 8.0f)
		{


				TanCong3();


		}
	}

	if (mTrangThai == eTT_BOSS1_TanCong3)
	{
		TG_Dem += in_tg;

		if (TG_Dem <= 1.5f)
		{
			HH_HienTai->CapNhat(in_tg * (TG_Dem + 1.5f) *  4.0f	);
		}
		else
		{
			HH_HienTai->CapNhat(in_tg * 3 * 4.0f);
		}

		if (TG_Dem > 1.5f && TG_Dem <= 3.0f)
		{
			mToaDo.x -= 115.0f * in_tg;

		}
		else if (TG_Dem > 3.0f && TG_Dem <= 4.5f)
		{
			mToaDo.x += 115.0f * in_tg;
		}
		else if (TG_Dem > 4.5f && TG_Dem <= 6.0f)
		{
			mToaDo.x -= 115.0f * in_tg;
		}
		else if (TG_Dem > 6.0f && TG_Dem <= 7.5f)
		{
			mToaDo.x += 115.0f * in_tg;
		}
		if (TG_Dem > 7.5f)
		{
			mToaDo.x = ToaDo_BanDau.x;
		}
		
		if (TG_Dem > 1.5f)
		{
			mVanToc.y += GiaTocTrongTruong * in_tg;
			if (mToaDo.y > ToaDo_BanDau.y)
			{
				mToaDo.y = ToaDo_BanDau.y;
				if (TG_Dem > 7.5f)
				{
					mVanToc.y = 0.0f;
				}
				else
				{
					mVanToc.y = -VanTocRoiToiDa;
				}
			}

			mToaDo.y += mVanToc.y * in_tg;
		}


		if (TG_Dem > 8.3f)
		{
			mVanToc.y = 0;

				TanCong1();
		}

	}
}

void BOSS1::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_BOSS1_BienMat ||
		mTrangThai == eTT_BOSS1_XuatHien ||
		mTrangThai == eTT_BOSS1_PhatNo)
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

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		HP -= ((DanLv*)in_DoiTuong)->get_Damage();
		TGDem_Shining = 0.0f;
	}
}

void BOSS1::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_BOSS1_BienMat)
	{
		return;
	}

	if (mTrangThai == eTT_BOSS1_PhatNo)
	{
		if (TGDem3 < 0.05f)
		{
			HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS1_png, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(160, 255, 255, 255));
		}
		else
		{
			HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS1_png, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(140, 255, 255, 255));
		}
		if (TGDem2 >= 0.0f && TGDem2 < 0.48f * 1 ||
			TGDem2 >= 0.48f * 4 && TGDem2 < 0.48f * 5)
		{
			mHH_HieuUngPhatNo[0]->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_HieuUngPhatNo[0], in_DoDoi);
		}
		else if (TGDem2 >= 0.48f * 1 && TGDem2 < 0.48f * 2 ||
			TGDem2 >= 0.48f * 5 && TGDem2 < 0.48f * 6)
		{
			mHH_HieuUngPhatNo[1]->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_HieuUngPhatNo[1], in_DoDoi);
		}
		else if (TGDem2 >= 0.48f * 2 && TGDem2 < 0.48f * 3 ||
			TGDem2 >= 0.48f * 6 && TGDem2 < 0.48f * 7)
		{
			mHH_HieuUngPhatNo[2]->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_HieuUngPhatNo[2], in_DoDoi);
		}
		else if (TGDem2 >= 0.48f * 3 && TGDem2 < 0.48f * 4 ||
			TGDem2 >= 0.48f * 7 && TGDem2 < 0.48f * 8)
		{
			mHH_HieuUngPhatNo[3]->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, ToaDo_HieuUngPhatNo[3], in_DoDoi);
		}

		return;
	}

	if (mTrangThai == eTT_BOSS1_XuatHien)
	{
		HH_ConPet->Ve(DS_HinhAnh::get_TH()->BOSS1_png, false, ToaDo_Pet, in_DoDoi);
		HH_AnhSang->Ve(DS_HinhAnh::get_TH()->BOSS1_png, false, mToaDo - Vec2(0.0f, 2.0f), in_DoDoi, D3DCOLOR_ARGB(Color_AnhSang, 255, 255, 255));
	}


	if (TGDem_Shining <= TG_Shining)
	{
		HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS1_Shining_png, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(200, 255, 50, 50));
	}
	else
	{
		HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS1_png, false, mToaDo, in_DoDoi, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void BOSS1::XuatHien()
{
	mTrangThai = eTT_BOSS1_XuatHien;
	mToaDo = ToaDo_BanDau;
	HH_HienTai = HH_XuatHien;
	HH_HienTai->Remake();
	HH_ConPet->Remake();
	Color_AnhSang = 0;
	TG_Dem = 0.0f;
	HP = MAX_HP;
	mCuaDanhBoss->ChoPhepMoCua = false;
}

void BOSS1::TanCong1()
{
	mToaDo = ToaDo_BanDau;
	mTrangThai = eTT_BOSS1_TanCong1;
	HH_HienTai = HH_TanCong;
	HH_HienTai->Remake();
	TG_Dem = 0.0f;
}

void BOSS1::TanCong2()
{
	mToaDo = ToaDo_BanDau;
	mTrangThai = eTT_BOSS1_TanCong2;
	HH_HienTai = HH_TanCong;
	TG_Dem = 0.0f;
}

void BOSS1::TanCong3()
{
	mToaDo = ToaDo_BanDau;
	mTrangThai = eTT_BOSS1_TanCong3;
	HH_HienTai = HH_TanCong3;
	HH_HienTai->Remake();
	TG_Dem = 0.0f;
	mVanToc.y = -VanTocRoiToiDa;
}

void BOSS1::PhatNo()
{
	mTrangThai = eTT_BOSS1_PhatNo;
	mVanToc.x = mVanToc.y = 0.0f;
	TG_Dem = 0.0f;
	TGDem2 = 0.0f;
	ToaDo_HieuUngPhatNo[0] = mToaDo + Vec2(-7.0f, -8.0f);
	ToaDo_HieuUngPhatNo[1] = mToaDo + Vec2(10.0f, -9.0f);
	ToaDo_HieuUngPhatNo[2] = mToaDo + Vec2(-11.0f, 14.0f);
	ToaDo_HieuUngPhatNo[3] = mToaDo + Vec2(13.0f, 11.0f);
	for (int i = 0; i < 4; i++)
	{
		mHH_HieuUngPhatNo[i]->Remake();
	}

}

void BOSS1::BienMat()
{
	mTrangThai = eTT_BOSS1_BienMat;
	mCuaDanhBoss->ChoPhepMoCua = true;
}

void BOSS1::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

#pragma region DONE
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(246, 246 + 22, 10, 10 + 22),  0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(126, 126 + 22, 10, 10 + 22),  0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(166, 166 + 22, 10 , 10 + 26), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(206, 206	 + 22, 10 , 10 + 28),0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(166, 166 + 22, 10, 10 + 26),  0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(126, 126 + 22, 10, 10 + 22),  0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 22, HCN(246, 246 + 22, 10, 10 + 22),  0.25f));
	HH_ConPet = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(32, 48, HCN(281, 281 + 32, 10, 10 + 48), 0.25f));
	HH_AnhSang = new HoatHinh(lDSTTFrame);
#pragma endregion

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(2, 2, HCN(75, 75 + 2, 80, 80 + 2),			0.12f));
	lDSTTFrame.push_back(ThongTinFrame(2, 2, HCN(83, 83 + 2, 80, 80 + 2),			0.12f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(4, 4, HCN(88, 88 + 4, 79, 79 + 4),			0.12f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(4, 4, HCN(94, 94 + 4, 79, 79 + 4),			0.12f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(8, 8, HCN(101, 101 + 8, 77, 77 + 8),			0.12f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(8, 8, HCN(113, 113 + 8, 77, 77 + 8),			0.12f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(10, 10, HCN(124, 124 + 10, 76, 76 + 10),		0.12f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(10, 10, HCN(137, 137 + 10, 76, 76 + 10),		0.12f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(12, 12, HCN(150, 150 + 12, 75, 75 + 12),		0.12f)); // 8
	lDSTTFrame.push_back(ThongTinFrame(12, 12, HCN(165, 165 + 12, 75, 75 + 12),		0.12f)); // 9
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(181, 181 + 14, 74, 74 + 14),		0.12f)); // 10
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(198, 198 + 14, 74, 74 + 14),		0.12f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(16, 16, HCN(217, 217 + 16, 73, 73 + 16),		0.12f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(18, 18, HCN(236, 236 + 18, 73, 73 + 18),		0.12f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(18, 18, HCN(257, 257 + 18, 73, 73 + 18),		0.12f)); // 14
	lDSTTFrame.push_back(ThongTinFrame(18, 18, HCN(280, 280 + 18, 72, 72 + 18),		0.12f)); // 15
	lDSTTFrame.push_back(ThongTinFrame(18, 18, HCN(308, 308 + 18, 72, 72 + 18),		0.12f)); // 16
	lDSTTFrame.push_back(ThongTinFrame(20, 20, HCN(333, 333 + 20, 70, 70 + 20),		0.12f)); // 17
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(358, 358 + 22, 69, 69 + 22),		0.12f)); // 18
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(387, 387 + 22, 69, 69 + 22),		0.12f)); // 19
	lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(419, 419 + 24, 67, 67 + 24),		0.12f)); // 20
	lDSTTFrame.push_back(ThongTinFrame(24, 24, HCN(448, 448 + 24, 67, 67 + 24),		0.12f)); // 21
	lDSTTFrame.push_back(ThongTinFrame(26, 26, HCN(58, 58 + 26, 112, 112 + 26),		0.12f)); // 22
	lDSTTFrame.push_back(ThongTinFrame(28, 28, HCN(90, 90 + 28, 111, 111 + 28),		0.12f)); // 23
	lDSTTFrame.push_back(ThongTinFrame(28, 28, HCN(122, 122 + 28, 111, 111 + 28),	0.12f)); // 24
	lDSTTFrame.push_back(ThongTinFrame(28, 28, HCN(156, 156 + 28, 110, 110 + 28),	0.12f)); // 25
	lDSTTFrame.push_back(ThongTinFrame(28, 28, HCN(190, 190 + 28, 112, 112 + 28),	0.12f)); // 26
	lDSTTFrame.push_back(ThongTinFrame(30, 30, HCN(226, 226 + 30, 111, 111 + 30),	0.12f)); // 27
	lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(262, 262 + 32, 109, 109 + 32),	0.12f)); // 28
	lDSTTFrame.push_back(ThongTinFrame(34, 34, HCN(301, 301 + 34, 109, 109 + 34),	0.12f)); // 29
	lDSTTFrame.push_back(ThongTinFrame(34, 34, HCN(341, 341 + 34, 109, 109 + 34),	0.12f)); // 30
	lDSTTFrame.push_back(ThongTinFrame(34, 34, HCN(382, 382 + 34, 109, 109 + 34),	0.12f)); // 31
	lDSTTFrame.push_back(ThongTinFrame(34, 34, HCN(423, 423 + 34, 108, 108 + 34),	0.12f)); // 32
	lDSTTFrame.push_back(ThongTinFrame(36, 36, HCN(464, 464 + 36, 107, 107 + 36),	0.12f)); // 33
	lDSTTFrame.push_back(ThongTinFrame(38, 38, HCN(70, 70 + 38, 154, 154 + 38),		0.12f)); // 34
	lDSTTFrame.push_back(ThongTinFrame(40, 40, HCN(114, 114 + 40, 155, 155 + 40),	0.12f)); // 35
	lDSTTFrame.push_back(ThongTinFrame(40, 40, HCN(160, 160 + 40, 158, 158 + 40),	0.12f)); // 36
	lDSTTFrame.push_back(ThongTinFrame(38, 38, HCN(207, 207 + 38, 159, 159 + 38),	0.12f)); // 37
	lDSTTFrame.push_back(ThongTinFrame(40, 40, HCN(255, 255 + 40, 158, 158 + 40),	0.12f)); // 38
	lDSTTFrame.push_back(ThongTinFrame(42, 42, HCN(305, 305 + 42, 158, 158 + 42),	0.12f)); // 39
	lDSTTFrame.push_back(ThongTinFrame(44, 44, HCN(352, 352 + 44, 158, 158 + 44),	0.12f)); // 40
	lDSTTFrame.push_back(ThongTinFrame(44, 44, HCN(401, 401 + 44, 156, 156 + 44),	0.12f)); // 41
	lDSTTFrame.push_back(ThongTinFrame(44, 44, HCN(452, 452 + 44, 157, 157 + 44),	0.12f)); // 42
	lDSTTFrame.push_back(ThongTinFrame(46, 46, HCN(46, 46 + 46, 209, 209 + 46),		0.12f)); // 43
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(96, 96 + 48, 209, 209 + 48),		0.12f)); // 44
	lDSTTFrame.push_back(ThongTinFrame(50, 50, HCN(147, 147 + 50, 210, 210 + 50),	0.12f)); // 45
	lDSTTFrame.push_back(ThongTinFrame(50, 50, HCN(202, 202 + 50, 208, 208 + 50),	0.12f)); // 46
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(259, 259 + 48, 210, 210 + 48),	0.12f)); // 47
	lDSTTFrame.push_back(ThongTinFrame(46, 46, HCN(316, 316 + 46, 211, 211 + 46),	0.12f)); // 48
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(369, 369 + 48, 211, 211 + 48),	0.12f)); // 49
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(429, 429 + 48, 209, 209 + 48),	99.9f)); // 50
	HH_XuatHien = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(46, 48, HCN(0, 0 + 46, 356, 356 + 48), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(52, 52 + 48, 355, 355 + 48), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(46, 46, HCN(106, 106 + 46, 357, 357 + 46), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(162, 162 + 48, 355, 355 + 48), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(50, 50, HCN(222, 222 + 50, 355, 355 + 50), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(50, 50, HCN(280, 280 + 50, 354, 354 + 50), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(50, 50, HCN(335, 335 + 50, 354, 354 + 50), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(390, 390 + 48, 353, 353 + 48), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(46, 46, HCN(446, 446 + 46, 355, 355 + 46), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(498, 498 + 48, 353, 353 + 48), 0.12f));
	HH_TanCong = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 50, HCN(2, 2 + 48, 412, 412 + 50), 0.12f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(46, 50, HCN(54, 54 + 46, 412, 412 + 50), 0.12f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(44, 50, HCN(103, 103 + 44, 412, 412 + 50), 0.12f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(42, 50, HCN(150, 150 + 42, 412, 412 + 50), 0.12f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(38, 50, HCN(197, 197 + 38, 412, 412 + 50), 0.12f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(36, 50, HCN(238, 238 + 36, 412, 412 + 50), 0.12f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(34, 50, HCN(278, 278 + 34, 412, 412 + 50), 0.12f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(32, 50, HCN(314, 314 + 32, 412, 412 + 50), 0.12f)); // 8
	lDSTTFrame.push_back(ThongTinFrame(30, 50, HCN(348, 348 + 30, 412, 412 + 50), 0.12f)); // 9
	lDSTTFrame.push_back(ThongTinFrame(28, 50, HCN(381, 381 + 28, 412, 412 + 50), 0.12f)); // 10
	lDSTTFrame.push_back(ThongTinFrame(24, 50, HCN(412, 412 + 24, 412, 412 + 50), 0.12f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(20, 50, HCN(441, 441 + 20, 412, 412 + 50), 0.12f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(14, 50, HCN(465, 465 + 14, 412, 412 + 50), 0.12f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(487, 487 + 10, 412, 412 + 50), 0.12f)); // 14
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(504, 504 + 10, 412, 412 + 50), 0.12f)); // 15
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(518, 518 + 8, 412, 412 + 50), 0.12f)); // 16
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(530, 530 + 8, 412, 412 + 50), 0.12f)); // 17
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(518, 518 + 8, 412, 412 + 50), 0.12f)); // 16
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(504, 504 + 10, 412, 412 + 50), 0.12f)); // 15
	lDSTTFrame.push_back(ThongTinFrame(8, 50, HCN(487, 487 + 10, 412, 412 + 50), 0.12f)); // 14
	lDSTTFrame.push_back(ThongTinFrame(14, 50, HCN(465, 465 + 14, 412, 412 + 50), 0.12f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(20, 50, HCN(441, 441 + 20, 412, 412 + 50), 0.12f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(24, 50, HCN(412, 412 + 24, 412, 412 + 50), 0.12f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(28, 50, HCN(381, 381 + 28, 412, 412 + 50), 0.12f)); // 10
	lDSTTFrame.push_back(ThongTinFrame(30, 50, HCN(348, 348 + 30, 412, 412 + 50), 0.12f)); // 9
	lDSTTFrame.push_back(ThongTinFrame(32, 50, HCN(314, 314 + 32, 412, 412 + 50), 0.12f)); // 8
	lDSTTFrame.push_back(ThongTinFrame(34, 50, HCN(278, 278 + 34, 412, 412 + 50), 0.12f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(36, 50, HCN(238, 238 + 36, 412, 412 + 50), 0.12f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(38, 50, HCN(197, 197 + 38, 412, 412 + 50), 0.12f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(42, 50, HCN(150, 150 + 42, 412, 412 + 50), 0.12f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(44, 50, HCN(103, 103 + 44, 412, 412 + 50), 0.12f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(46, 50, HCN(54, 54 + 46, 412, 412 + 50), 0.12f)); // 2
	HH_TanCong3 = new HoatHinh(lDSTTFrame);
	
	for (int i = 0; i < 4; i++)
	{
		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
		lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
		mHH_HieuUngPhatNo[i] = new HoatHinh(lDSTTFrame);
	}
}

BOSS1::~BOSS1()
{
}
