#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "Camera.h"
#include "Bui.h"
#include "DS_HinhAnh.h"
#include "DanNo1.h"
#include "Item.h"

class Ech : public DoiTuong
{
public:
	Ech(const Vec2& in_ToaDo, const Vec2& in_VanToc,
		std::vector<DanNo1*>& in_DS_DanNo1, std::vector<Bui*>& in_Bui, Item *in_Item, 
		int in_Rong = 26, int in_Cao = 30, bool in_EchKoNhay = false);

	// ko xài cái này
	void CapNhat(float in_tg) 
	{
	}

// FUNCTION

	void CapNhat(float in_tg, const DoiTuong *in_XMan);
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);

// INFORMATION
private:
	bool mDangDungTuNhienRoi = false;
	Vec2 VanTocKhachQuan;
	bool mEchKoNhay = false;

	// ĐẠN NỔ và BỤI này chỉ là con trỏ
	std::vector<DanNo1*> mDS_DanNo1; // Khoảng 6 viên
	std::vector<Bui*> mDS_Bui;
	Item *mItem;

	Vec2 mToaDo_HieuUngNoTung;
	Vec2 mToaDoXuatHien;

	const int mMaxHP = 4;
	int mHP = mMaxHP;

	HoatHinh *mHH_ChuanBiNhay,
		*mHH_Nhay,
		*mHH_Roi,
		*mHH_NhamBan1,
		*mHH_BanDan1,
		*mHH_HaNhamBan1,
		*mHH_NhamBan3,
		*mHH_BanDan3,
		*mHH_HaNhamBan3,
		*mHH_NhamBan2,
		*mHH_BanDan2,
		*mHH_HaNhamBan2,
		*mHH_DangTanBien;
	HoatHinh *mHH_HienTai;	
	HoatHinh *mHH_HieuUngNoTung;

	static constexpr float mTG_HieuUngNoTung = 0.08f * 6;
	float mTGDem_HieuUngNoTung = mTG_HieuUngNoTung + 0.1f;
	
	float mKhoangCach_XMan;

	bool mNamTrongCamera = false;

	static constexpr float mTG_TanBien = 0.3f;
	float mTGDem_TanBien = 0.0f;

	bool mIsShining = false;
	static constexpr float mTG_Shining = 0.15f;
	float mTGDem_Shining = 0.0f;

	float mTGDem_BuiXuatHien = 0.35f;

	static constexpr float mTG_ChuanBiNhay = 0.12f * 5 - 0.05f;
	float mTGDem_ChuanBiNhay = 0.0f;

	static constexpr float mTG_TiepDat = 0.12f * 5;
	float mTGDem_TiepDat = 0.0f;

	static constexpr float mTG_NhamBan1 = 0.14f * 3;
	float mTGDem_NhamBan1 = 0.0f;

	static constexpr float mTG_HaNhamBan1 = 0.14f * 3;
	float mTGDem_HaNhamBan1 = 0.0f;

	static constexpr float mTG_BanDan = 0.25f * 2 * 3;
	float mTGDem_BanDan = 0.0f;

	static constexpr float mTG_NhamBan2 = 0.14f * 4;
	float mTGDem_NhamBan2 = 0.0f;

	static constexpr float mTG_HaNhamBan2 = 0.14f * 4;
	float mTGDem_HaNhamBan2 = 0.0f;

	static constexpr float mTG_NhamBan3 = 0.14f * 5;
	float mTGDem_NhamBan3 = 0.0f;

	static constexpr float mTG_HaNhamBan3 = 0.14f * 5;
	float mTGDem_HaNhamBan3 = 0.0f;

	static constexpr float mGiaTocTrongTruong = 1000.0f;
	static constexpr float mVanTocRoiToiDa = 300.0f;
	static constexpr float mVanTocNhay = 120.0f;

	bool mLatHinh = false;


// SUB-FUNCTION
private:
	void LoadThongTinHoatHinh();

	void NhamBan2();
	void BanDan2();
	void HaNhamBan2();
	void NhamBan3();
	void BanDan3();
	void HaNhamBan3();
	void BanDan1();
	void NhamBan1();
	void HaNhamBan1();
	void ChuanBiNhay();
	void Nhay();
	void Roi();
	void TiepDat();
	void DangTanBien();

	void CapNhat_NhamBan2(float in_tg);
	void CapNhat_BanDan2(float in_tg);
	void CapNhat_HaNhamBan2(float in_tg);
	void CapNhat_ChuanBiNhay(float in_tg);
	void CapNhat_Nhay(float in_tg);
	void CapNhat_Roi(float in_tg);
	void CapNhat_TiepDat(float in_tg);
	void CapNhat_NhamBan1(float in_tg);
	void CapNhat_HaNhamBan1(float in_tg);
	void CapNhat_BanDan1(float in_tg);
	void CapNhat_NhamBan3(float in_tg);
	void CapNhat_BanDan3(float in_tg);
	void CapNhat_HaNhamBan3(float in_tg);
	void CapNhat_DangTanBien(float in_tg);

// DESTRUCTURE
public:
	~Ech();
};

