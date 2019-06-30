#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"

class DanLv3 :
	public DanLv
{

public:
	DanLv3(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2());
	~DanLv3();

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
		return 4;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_BanRa;
	HoatHinh *mHH_HienTai;

	bool mLatHinh = false;

	float mTG_PhaHuy = 0.03f * 2; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;

	const float mTG_BanRa = 0.03f * 2;
	float mTG_DemBanRa = 0.0f;


	void LoadHinhAnhVao();
	void DangTanBien();
	void DangTonTai();
	void Ban();
public:
	static constexpr float mVanTocDan = 400.0f /*0.0f*/;


};

