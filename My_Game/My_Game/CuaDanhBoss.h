#pragma once
// tách cửa đánh boss và boss ra thành các đối tượng riêng
// truyền vào con boss 2 cửa

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class CuaDanhBoss :
	public DoiTuong
{
public:
	// CONSTRUCTURE
	CuaDanhBoss(const Vec2& in_ToaDo, bool in_ChuyenDang = false);

	void CapNhat(float in_tg) {}

	// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi);

	void set_ChoPhepMoCua(bool in) { ChoPhepMoCua = in; }
	bool ChoPhepMoCua = true;

// INFORMATION
private:
	bool ChuyenDang = false;
	static constexpr float TG_MoCua = 0.13f * 17 + 1.5f; 
	static constexpr float TG_DongCua = 0.13f * 16 + 1.1f;
	float TGDem = 0.0f;
	HoatHinh *HH_DongCua;
	HoatHinh *HH_MoCua,
		*HH_DongCua2,
		*HH_MoCua2;
	HoatHinh *HH_HienTai;


// FUNCTION
private:
	void MoCua();
	void DongCua();
	void KhoaCua();

	void LoadThongTinHoatHinh();

// DESTRUCTURE
public:
	~CuaDanhBoss();
};

