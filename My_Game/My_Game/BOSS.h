#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "OngCon.h"
#include "ThanhMau.h"
#include "HongTam.h"
#define VAL 0.0174532925199444

class BOSS :
	public DoiTuong
{
// CONSTRUCTURE
public:
	BOSS(const Vec2& in_ToaDo);
	void CapNhat(float in_tg) {} // NOT USE
// FUNCTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	Vec2 ViTri_CanDenHienTai; // có 2 Vị Trí cho BOSS
	OngCon* get_OngCon0() { return DS_OngCon[0]; }
	OngCon* get_OngCon1() { return DS_OngCon[1]; }
	OngCon* get_OngCon2() { return DS_OngCon[2]; }
	OngCon* get_OngCon3() { return DS_OngCon[3]; }
	OngCon* get_OngCon4() { return DS_OngCon[4]; }
	int get_HP() { return HP; }
	HongTam* get_HongTam() { return mHongTam; }
	bool get_KoNhanSatThuong() { return (DEM_KoAnDan <= TG_KoAnDan); }
	void BienMat();
// INFORMATION
private:
	bool DEM_SoundHieuUngNo = 0.0f;
	bool PlaySound_HieuUngNo = false;
	bool PlaySound_NhacDanhBoss = false;
	Vec2 ToaDo_XuatHien;
	int index_ToaDoNgauNhien;
	Vec2 ToaDo_NgauNhien[10];
	Vec2 ToaDo_PhatNoHienTai;
	HongTam *mHongTam;
	float DEM_NhapNhayLucBiDanhBai = 0.0f;
	static constexpr float TG_KoAnDan = 0.6f;
	float DEM_KoAnDan = TG_KoAnDan + 0.1f;
	float DEM_KoAnDan2 = TG_KoAnDan + 0.1f;
	static constexpr int MAXHP = 132;
	int HP;
	int HP_DuTru;
	float DX, DY;
	OngCon *DS_OngCon[5];
	Vec2 ViTri1;
	Vec2 ViTri2;
	Vec2 ViTri3;
	float KC_BOSS_XMAN;
	float GocSin = 45.0f;
	static constexpr float TG_ThaOng = 0.1f * 9;
	static constexpr float TG_DamKim = 0.6f + 0.06f * 4;
	static constexpr float TG_ChuanBiDamKim = 0.06f * 13;
	static constexpr float VanTocTiepCan = 400.0f;
	static constexpr float VanTocBay = 150.0f;
	static constexpr float VanTocX_VongSo8 = 120.0f;
	static constexpr float VanToc_VONGVONG = 140.0f;
	float DEM = 0.0f;
	float DEM_SinhOng = 0.0f;
	bool DaThaOng = false;
	bool LatHinh = false;
	HoatHinh *HH_HienTai,
		*HH_Bay,
		*HH_ChuanBiDamKim,
		*HH_DamKim,
		*HH_ThaOng,
		*HH_SinhOng,
		*HH_BiDanhBai;
	HoatHinh *HH_CanhOng;
	HoatHinh *HH_PhatNo;
// SUB-FUNCTION
private:
	void XuatHien();
	void ChuanBiDamKim();
	void DamKim();
	void VaoViTri(const Vec2& in_ViTriCanDen);
	void ThaOng();
	void BayVongSo8();
	void BayVongVong();
	void PhatNo();

	void LoadThongTinHoatHinh();
// DESTRUCTURE
public:
	~BOSS();
};

