#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "DS_HinhAnh.h"


class TenLua :
	public DoiTuong
{
public:
	TenLua();

// FUNCTION
	void CapNhat(float in_tg);
	void CapNhat(float in_tg, const DoiTuong *in_XMan);
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc, bool in_ChuyenDang = false);
	void PhatNo();

// INFORMATION
private:
	static constexpr int MAXHP = 2;
	int HP = MAXHP;
	HoatHinh *mHH_Dan;
	HoatHinh *mHH_HieuUngPhatNo;
	HoatHinh *HH_ChuyenDang;
	HoatHinh *HH_ChuyenDang2;

	bool ChuyenDang = false;

	static constexpr float TG_NoTung = 0.08f * 6;
	float TGDem_NoTung = TG_NoTung + 0.1f;

	// lỡ như ko va chạm thì Đạn có thể tự động biến mất để có thể dùng tiếp
	static constexpr float TG_TuDongBienMat = 2.5f;
	float TGDem_TuDongBienMat = 0.0f;




	// SUB-FUNCTION
	void LoadThongTinHoatHinh();

	//DESTRUCTURE
	~TenLua();

};

