#pragma once

#include "KieuDuLieu.h"

class Camera
{
private:
	static Vec2 mToaDo; // chính giữa camera
	static int mChieuRong;
	static int mChieuCao;

public:
	static int mGioiHanTrai;
	static int mGioiHanPhai;
	static int mGioiHanTren;
	static int mGioiHanDuoi;

	static int CheckPoint;

	static int mGioiHanTraiTiepTheo;
	static int mGioiHanPhaiTiepTheo;
	static int mGioiHanTrenTiepTheo;
	static int mGioiHanDuoiTiepTheo;
	static int speed;










	
	
/////////////////////////////
/*  Các thủ tục SET - GET  */
public:
	static void set_ToaDo(const Vec2& in_ToaDo);
	static void set_KichThuoc(int in_ChieuRong, int in_ChieuCao);
	static void set_GioiHan(int in_Trai, int in_Phai, int in_Tren, int in_Duoi);

	static Vec2 get_ToaDo();
	static int get_ChieuRong();
	static int get_ChieuCao();
	static HCN get_HCNGioiHan();
	static HCN get_HCNGioiHan_MoRong();
	static HCN get_HCNGioiHan_MoRong_1();
};

