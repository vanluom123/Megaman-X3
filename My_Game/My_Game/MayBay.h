#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "Bui.h"
#include "TenLua.h"
#include "Item.h"

class MayBay :
	public DoiTuong
{
public:
	MayBay(const Vec2& in_ToaDo, std::vector<TenLua*>& in_DS_TenLua, 
		std::vector<Bui*>& in_Bui, Item *in_Item);

	void CapNhat(float in_tg) {}

// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại

// INFORMATION
private:
	Item *mItem;
	std::vector<TenLua*> mDS_TenLua; // trỏ đến Tên Lửa Màn 1
	std::vector<Bui*> mDS_Bui;

	HoatHinh *HH_DiChuyen;
	HoatHinh *HH_PhatNo;

// SUB-FUNCTION
private:
	static constexpr int MAXHP = 3;
	int HP = MAXHP;
	bool mLatHinh = false;

	float TGDem = 0.0f;
	static constexpr float TG_PhatNo = 0.48f;
	static constexpr float TG_BanTenLua = 2.0f;
	float TGDem_BanTenLua = 0.0f;
	static constexpr float VanTocBay = 45.0f;
	bool NamTrongCamera = false;
	Vec2 ToaDo_XuatHien;
	Vec2 ToaDo_PhatNo;
	float TGDem_Shining = TG_Shining + 0.1f;
	static constexpr float TG_Shining = 0.1f;

	void DiChuyen();
	void BanDan();
	void BoChay();
	void PhatNo();

	void LoadThongTinHoatHinh();

// DESTRUCTURE
	~MayBay();
};

