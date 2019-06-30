#pragma once

#include "DoiTuong.h"

class VaChamGame
{
public:
	static eKetQuaVaCham get_KetQuaVaCham(const HCN& in_HCN1, const HCN& in_HCN2);
	static ePhiaVaCham get_PhiaVaCham(const DoiTuong *in_DoiTuong, eKetQuaVaCham in_KetQuaVaCham);
	// nếu Rectangle quá to thì va chạm có thể bị sai
	static ePhiaVaCham get_PhiaVaCham(const DoiTuong *in_DoiTuong1, const DoiTuong *in_DoiTuong2);

	static bool get_DaVaCham(const HCN& in_HCN1, const HCN& in_HCN2);
	static bool get_DiemVaHCN(int in_X, int in_Y, const HCN& in_HCN);
	static bool get_HCNVaHinhTron(const HCN& in_HCN, int in_TamX, int in_TamY, int in_BanKinh);
};

