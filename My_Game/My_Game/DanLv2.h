#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"

class DanLv2 : public DanLv
{

public:
	DanLv2(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2());
	~DanLv2();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong);

	void Remake()
	{
		Ban();
	}

	eTrangThai get_TrangThai() const
	{
		return mTrangThai;
	}

	void set_LatHinh(bool a)
	{
		mLatHinh = a;
	}

	int get_Damage() const
	{
		return 2;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_HienTai;

	bool mLatHinh = false;

	const float mTG_PhaHuy = 0.03f * 2; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;


	void LoadHinhAnhVao();
	void DangTanBien();
	void DangTonTai();
	void Ban();
public:
	static constexpr float mVanTocDan = 400.0f;

};
