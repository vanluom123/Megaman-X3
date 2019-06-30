#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Box :
	public DoiTuong
{
public:
	Box(const Vec2& in_ToaDo, const Vec2& in_VanToc = Vec2(), int in_K = 0);

	void CapNhat(float in_tg);
// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi);
	void DiChuyen(const Vec2& in_ToaDo, const Vec2& in_VanToc, float in_TG);
// INFORMATION
private:
	Vec2 ToaDo_BanDau;
	int K;
	HoatHinh *HH_1;
	float TG_DiChuyen = 0.0f;
	float DEM = 0.0f;
	static constexpr int MAXHP = 8;
	int HP = MAXHP;
	static constexpr float TG_Shining = 0.07f;
	float DEM_Shining = TG_Shining + 0.1f;
	static constexpr float TG_PhatNo = 0.48f;
	HoatHinh *HH_PhatNo;
	Vec2 ToaDo_PhatNo[5];
//SUB-FUNCTION
private:
	void PhatNo();
	void BienMat();
	void LoadThongTinHoatHinh();
// DESTRUCTURE
public:
	~Box()
	{

	}
};

