#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"

class DanLv1 :
	public DanLv
{
public:
	DanLv1(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2());
	~DanLv1();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong);

	void Remake()
	{
		DangTonTai();
	}	

	eTrangThai get_TrangThai() const
	{
		return mTrangThai;
	}

	int get_Damage() const
	{
		return 1;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_HienTai;

	const float mTG_PhaHuy = 0.07f * 3; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;


	void LoadHinhAnhVao();

	void DangTanBien();

	void DangTonTai();

public :
	static constexpr float mVanTocDan = 380.0f;

};

