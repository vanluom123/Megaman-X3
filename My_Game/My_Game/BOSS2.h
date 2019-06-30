#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"
#include "Box.h"
#include "Pet1.h"
#include "Pet2.h"
#include "DanSang.h"

class BOSS2 :
	public DoiTuong
{
public:
	BOSS2(const Vec2& in_ToaDo = Vec2(4990.0f, 984.0f));
	void CapNhat(float in_tg) {}
// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	Box* get_Box0() { return mBox[0] ; }
	Box* get_Box1() { return mBox[1] ; }
	DanSang* get_DanSang() { return mDanSang; }
	Pet2* get_Pet2() { return mPet2; }
	void BienMat();
// INFORMATION
private:
	static constexpr int MAXBOX = 8;
	int SoHop = MAXBOX;
	DanSang *mDanSang;
	Pet2 *mPet2;
	static constexpr float TG_Pet2 = 3.0f;
	float DEM_Pet2 = 0.0f;
	Pet1 *mPet1[2];
	Box *mBox[2];
	HoatHinh	*HH_1,
				*HH_2;
	Vec2 ToaDo_HH1;
	Vec2 ToaDo_HH2;
	float DEM = 0.0f;
	static constexpr float TG_XuatHien = 4.33f;
	static constexpr float TG_BoChay = 4.33f;
	static constexpr float TG_HoiChieuBox = 1.0f;
	float DEM_HoiChieuBox1 = 0.0f;
	float DEM_HoiChieuBox2 = 0.0f;
// SUB-FUNCTION
	void XuatHien();
	void BocVac();
	void BoChay();

	void CapNhat_XuatHien(float in_tg);
	void CapNhat_BoChay(float in_tg);
	void LoadThongTinHoatHinh();
// DESTRUCTURE
public:
	~BOSS2();
};

