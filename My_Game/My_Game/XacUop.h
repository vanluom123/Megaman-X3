#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "DS_HinhAnh.h"

class XacUop :
	public DoiTuong
{
public:
	XacUop(const Vec2& in_ToaDo, const Vec2& in_VanToc)
		:
		DoiTuong(in_ToaDo, in_VanToc, 22, 38)
	{
		mLoaiDoiTuong = eLDT_XacUop;
		LoadThongTinHoatHinh();
		DungIm();
	}

	void CapNhat(float in_tg) {} // ko dùng 

	void CapNhat(float in_tg, const DoiTuong *in_XMan)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;

		mKhoangCach_XMan = mToaDo.x - in_XMan->get_ToaDo().x;

		mHH_HienTai->CapNhat(in_tg);

		switch (mTrangThai)
		{
		case eTT_XacUop_DungIm:
			mTGDem_DungIm += in_tg;
			if (mTGDem_DungIm > TG_DungIm)
			{
				TanCong();
			}

			if (mKhoangCach_XMan < -mKhoangCach_TanCong || mKhoangCach_XMan > mKhoangCach_TanCong)
			{
				DiChuyen();
			}

			if (mKhoangCach_XMan < 0)
			{
				mLatHinh = true;
			}
			else
			{
				mLatHinh = false;
			}

			break;

		case eTT_XacUop_DiChuyen:
			// xác định hướng quay mặt

			if (mLatHinh)
			{
				mVanToc.x = VanTocDiChuyen;

			}
			else
			{
				mVanToc.x = -VanTocDiChuyen;
			}

			if (mKhoangCach_XMan > -mKhoangCach_TanCong && mKhoangCach_XMan < mKhoangCach_TanCong)
			{
				TanCong();
			}

			if (mKhoangCach_XMan < 0)
			{
				mLatHinh = true;
			}
			else
			{
				mLatHinh = false;
			}

			break;

		case eTT_XacUop_TanCong:
			mTGDem_TanCong += in_tg;
			if (mLatHinh)
			{
				mVanToc.x = 50.0f / 3.2f;

			}
			else
			{
				mVanToc.x = -50.0f / 3.2f;
			}
			if (mTGDem_TanCong > TG_TanCong)
			{
				DungIm();

			}
			break;

		default:
			break;
		}
	}
	void Ve(const Vec2& in_DoDoi) // Độ dời phụ thuộc Camera hiện tại
	{
		mHH_HienTai->Ve(DS_HinhAnh::get_TH()->XacUop_png, mLatHinh, mToaDo, in_DoDoi);
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{

	}



private:
	void DungIm()
	{
		mTrangThai = eTT_XacUop_DungIm; // Thông tin Trạng Thái = DungIm
		mHH_HienTai = mHH_DungIm; // Hoạt Hình trỏ đến HH_DungIm
		mHH_HienTai->Remake(); // Hoạt Hình được reset lại
		mTGDem_DungIm = 0.0f;
		mVanToc.x = 0.0f;
	}

	void DiChuyen()
	{
		mTrangThai = eTT_XacUop_DiChuyen;
		mHH_HienTai = mHH_DiChuyen;
		mHH_HienTai->Remake();
		//mTGDem_DiChuyen = 0.0f;
	}

	void TanCong()
	{
		mTrangThai = eTT_XacUop_TanCong;
		mHH_HienTai = mHH_TanCong;
		mHH_HienTai->Remake();
		mTGDem_TanCong = 0.0f;
	}

	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(20, 38, HCN(85, 85 + 22, 4, 4 + 40)));
		mHH_DungIm = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(36, 36, HCN(50, 50 + 30, 60, 60 + 38), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(34, 38, HCN(80, 80 + 30, 58, 58 + 40), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(110,110+30 ,60,60+40 ), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(34, 38, HCN(80, 80 + 30, 58, 58 + 40), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(36, 36, HCN(50, 50 + 30, 60, 60 + 38), 0.1f));
		mHH_DiChuyen = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(26, 38,  HCN(3, 3 + 26, 107, 107 + 38), 0.12f));
		lDSTTFrame.push_back(ThongTinFrame(26 ,36 , HCN(30,30+34,108,108+36), 0.12f));
		lDSTTFrame.push_back(ThongTinFrame(32 ,38 , HCN(63, 63+32, 107, 107+36), 0.12f));
		lDSTTFrame.push_back(ThongTinFrame(52 ,38 , HCN(95, 95+44, 107, 107+36), 0.12f));
		lDSTTFrame.push_back(ThongTinFrame(74 ,38 , HCN(139, 139+54, 107, 107+36), 0.12f));
		mHH_TanCong = new HoatHinh(lDSTTFrame);
	}

	HoatHinh *mHH_DungIm,
		*mHH_DiChuyen,
		*mHH_TanCong;

	HoatHinh *mHH_HienTai;

	bool mLatHinh = false;
	eTrangThai mTrangThai;

	const float TG_DungIm = 0.4f;
	float mTGDem_DungIm = 0.0f;

	//const float TG_DiChuyen = 0.2f;
	//float mTGDem_DiChuyen = 0.0f;
	
	const float TG_TanCong = 0.12f * 5;
	float mTGDem_TanCong = 0.0f;

	float mKhoangCach_XMan;

	const float VanTocDiChuyen = 70.0f;

	float mKhoangCach_TanCong = 50.0f;

public:
	~XacUop() 
	{
		if (mHH_DungIm)
			delete mHH_DungIm;

		if (mHH_DiChuyen)
			delete mHH_DiChuyen;

		if (mHH_TanCong)
			delete mHH_TanCong;
	}


};

