#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Bui : public DoiTuong
{
public:
	Bui(const Vec2& in_ToaDo, const Vec2& in_VanToc = Vec2(0.0f, -35.0f));
	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại

	// ko xài đến hàm này
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
	}

	void Remake();
private:
	HoatHinh *mHoatHinh;

	const float mTG_TonTai = 0.08f * 6;
	float mTGDem_TonTai = mTG_TonTai + 0.1f;



// DESTRUCTURE
public:
	~Bui();
	bool get_BienMat() const { return (mTGDem_TonTai > mTG_TonTai); }
};
