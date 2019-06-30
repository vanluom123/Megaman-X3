#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class TrucXoay :
	public DoiTuong
{
public:
	TrucXoay(const Vec2& in_ToaDo, int in_ChieuRong = 32, int in_ChieuCao = 32, int k = 0) :
		DoiTuong(in_ToaDo, Vec2(), in_ChieuRong, in_ChieuCao)
	{
		mLoaiDoiTuong = eLDT_TrucXoay;
		K = k;
		if (K == 1 || 
			K == 2)
		{
			LatHinh = true;
		}
		if (K == -1 ||
			K == -2)
		{
			LatHinh = false;
		}
		if (K == 3)
		{
			LatHinh = false;
		}
		if (K == 4)
		{
			LatHinh = true;
		}
		if (K == 5)
		{
			LatHinh = false;
		}
		if (K == 6)
		{
			LatHinh = true;
		}


		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(102, 102 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(68, 68 + 32, 0, 32),   0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(34, 34 + 32, 0, 32),   0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(0, 32, 0, 32),         0.25f));
		HH_1 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(18, 32, HCN(60, 60 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(18, 32, HCN(40, 40 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(18, 32, HCN(20, 20 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(18, 32, HCN(0, 18, 0, 32), 0.25f));
		HH_2 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(128, 32, HCN(0, 0 + 128, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(128, 32, HCN(130, 130 + 128, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(128, 32, HCN(260, 260 + 128, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(128, 32, HCN(390, 390 + 128, 0, 32), 0.25f));
		HH_34= new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(19 ,  19 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(149, 149 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(279, 279 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(409, 409 + 32, 0, 32), 0.25f));
		HH_56 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(409, 409 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(279, 279 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(149, 149 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(19, 19 + 32, 0, 32), 0.25f));
		HH_5 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(0,     0 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(130, 130 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(260, 260 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(390, 390 + 32, 0, 32), 0.25f));
		HH_78 = new HoatHinh(lDSTTFrame);
	}

	void CapNhat(float in_tg) {}

// FUNCTION
	void Ve(const Vec2& in_DoDoi) 
	{
		if (K == 1 ||
			K == -1)
		{
			HH_1->Ve(DS_HinhAnh::get_TH()->TrucXoay1_png, LatHinh, mToaDo, in_DoDoi);
		}
		else if (K == 2 || K == -2)
		{
			HH_2->Ve(DS_HinhAnh::get_TH()->TrucXoay2_png, LatHinh, mToaDo, in_DoDoi);
		}
		if (K == 3 || K == 4)
		{
			HH_34->Ve(DS_HinhAnh::get_TH()->TrucXoayLan2, LatHinh, mToaDo, in_DoDoi);
		}
		if (K == 5 || K == 6)
		{
			HH_56->Ve(DS_HinhAnh::get_TH()->TrucXoayLan2, LatHinh, mToaDo, in_DoDoi);
		}
		if (K == 7 || K == 8)
		{
			HH_78->Ve(DS_HinhAnh::get_TH()->TrucXoayLan2, LatHinh, mToaDo, in_DoDoi);
		}
	} // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{
		if (K == 1 ||
			K == -1)
		{
			HH_1->CapNhat(in_tg);
		}
		else if (K == 2 ||
			K == -2)
		{
			HH_2->CapNhat(in_tg);
		}
		if (K == 3 ||
			K == 4)
		{
			HH_34->CapNhat(in_tg);
		}
		if (K == 5 || K == 6)
		{
			HH_56->CapNhat(in_tg);
		}
		if (K == 7 || K == 8)
		{
			HH_78->CapNhat(in_tg);
		}
	}


// INFORMATION
private:
	HoatHinh* HH_1;
	HoatHinh* HH_2;
	HoatHinh* HH_34;
	HoatHinh* HH_5;
	HoatHinh* HH_56;
	HoatHinh* HH_78;

	bool LatHinh = false;
public:
	int K = 0;

// DESTRUCTURE
	~TrucXoay()
	{

	}
};

