#include "VaChamGame.h"
#include "map"

eKetQuaVaCham VaChamGame::get_KetQuaVaCham(const HCN& in_HCN1, const HCN& in_HCN2)
{
	eKetQuaVaCham lKetQuaVaCham;

	if (!get_DaVaCham(in_HCN1, in_HCN2))
	{
		lKetQuaVaCham.eKQVC_DaVaCham = false;

		return lKetQuaVaCham;
	}

	lKetQuaVaCham.eKQVC_DaVaCham = true;

	// vùng va chạm hình chữ nhật
	lKetQuaVaCham.eKQVC_VungVaCham.Trai = in_HCN1.Trai > in_HCN2.Trai ? in_HCN1.Trai : in_HCN2.Trai;
	lKetQuaVaCham.eKQVC_VungVaCham.Phai = in_HCN1.Phai < in_HCN2.Phai ? in_HCN1.Phai : in_HCN2.Phai;
	lKetQuaVaCham.eKQVC_VungVaCham.Duoi = in_HCN1.Duoi < in_HCN2.Duoi ? in_HCN1.Duoi : in_HCN2.Duoi;
	lKetQuaVaCham.eKQVC_VungVaCham.Tren = in_HCN1.Tren > in_HCN2.Tren ? in_HCN1.Tren : in_HCN2.Tren;

	return lKetQuaVaCham;
}

ePhiaVaCham VaChamGame::get_PhiaVaCham(const DoiTuong * in_DoiTuong, eKetQuaVaCham in_KetQuaVaCham)
{
	float lTrungTamVaChamX = in_KetQuaVaCham.eKQVC_VungVaCham.Trai + (in_KetQuaVaCham.eKQVC_VungVaCham.Phai - in_KetQuaVaCham.eKQVC_VungVaCham.Trai) / 2.0f;
	float lTrungTamVaChamY = in_KetQuaVaCham.eKQVC_VungVaCham.Tren + (in_KetQuaVaCham.eKQVC_VungVaCham.Duoi - in_KetQuaVaCham.eKQVC_VungVaCham.Tren) / 2.0f;

	D3DXVECTOR2 lTrungTamVaCham = D3DXVECTOR2(
		lTrungTamVaChamX, 
		lTrungTamVaChamY);
	D3DXVECTOR2 lTrungTamThucThe = D3DXVECTOR2(
		in_DoiTuong->get_ToaDo().x, 
		in_DoiTuong->get_ToaDo().y);

	// lấy vector nối từ Thực Thể đến Vùng Va Chạm
	D3DXVECTOR2 lVec = lTrungTamVaCham - lTrungTamThucThe;

	// chuẩn hóa Vector
	D3DXVec2Normalize(&lVec, &lVec);

	/*
	- nếu vector chuẩn hóa có y > 0 => nằm phía bên trên Thực Thể
	- nếu vector chuẩn hóa có y < 0 => nằm phía bên dưới Thực Thể
	- nếu vector chuẩn hoá có x > 0 => nam phia ben phai Entity
	- neu vector chuan hoa co x < 0 => nam phia ben trai Entity
	*/


	if (lVec.y < 0)
	{
		// va chạm phía bên trên
		//lay cos cua goc neu ma nam trong khoang goc 55 -> 125 thi va cham Tren
		if (lVec.x <= 0.57f && lVec.x >= -0.57f)
		{
			return ePhiaVaCham::ePVC_Tren;
		}
		else if (lVec.x > 0.57f && lVec.x < 0.82f)
		{
			//goc trong khoang 35 -> 55 phia ben Tren - Phai
			return ePhiaVaCham::ePVC_PhaiTren;
		}
		else if (lVec.x >= 0.82f)
		{
			return ePhiaVaCham::ePVC_Phai;
		}
		else if (lVec.x < -0.57f && lVec.x > -0.82f)
		{
			// va chạm phía Trên - Trái
			return ePhiaVaCham::ePVC_TraiTren;
		}
		else
		{
			return ePhiaVaCham::ePVC_Trai;
		}
	}
	else
	{
		// va chạm phía bên dưới
		//lay cos cua goc neu ma nam trong khoang goc 55 -> 125 thi va cham top
		if (lVec.x <= 0.57f && lVec.x >= -0.57f)
		{
			return ePhiaVaCham::ePVC_Duoi;
		}
		else if (lVec.x > 0.57f && lVec.x < 0.82f)
		{
			//goc trong khoang 35 -> 55 phia ben top - right
			return ePhiaVaCham::ePVC_PhaiDuoi;
		}
		else if (lVec.x >= 0.82f)
		{
			return ePhiaVaCham::ePVC_Phai;
		}
		else if (lVec.x < -0.57f && lVec.x > -0.82f)
		{
			//va cham phia top - left
			return ePhiaVaCham::ePVC_TraiDuoi;
		}
		else
		{
			return ePhiaVaCham::ePVC_Trai;
		}
	}

	return ePhiaVaCham::ePVC_KhongXacDinh;
}

ePhiaVaCham VaChamGame::get_PhiaVaCham(const DoiTuong * in_DoiTuong1, const DoiTuong * in_DoiTuong2)
{
	float lW = float(in_DoiTuong1->get_ChieuRong() + in_DoiTuong2->get_ChieuRong()) / 2.0f;
	float lH = float(in_DoiTuong1->get_ChieuCao() + in_DoiTuong2->get_ChieuCao()) / 2.0f;

	float lDx = in_DoiTuong1->get_ToaDo().x - in_DoiTuong2->get_ToaDo().y;
	float lDy = in_DoiTuong1->get_ToaDo().x - in_DoiTuong2->get_ToaDo().y;

	if (abs(lDx) <= lW && abs(lDy) <= lH)
	{
		/* có va chạm */
		float lWy = lW * lDy;
		float lHx = lH * lDx;

		if (lWy > lHx)
		{
			if (lWy > -lHx)
			{
				/*va cham phia tren Thực Thể 1*/
				return ePhiaVaCham::ePVC_Tren;
			}
			else
			{
				/*va chạm phía bên phải Thực Thể 1*/
				return ePhiaVaCham::ePVC_Phai;
			}
		}
		else if (lWy > -lHx)
		{
			/*va chạm phía bên trái Thực Thể 1*/
			return ePhiaVaCham::ePVC_Trai;
		}
		else
		{
			/*va chạm phía bên dưới Thực Thể 1*/
			return ePhiaVaCham::ePVC_Duoi;
		}
	}

	return ePhiaVaCham::ePVC_KhongXacDinh;
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

bool VaChamGame::get_DaVaCham(const HCN& in_HCN1, const HCN& in_HCN2)
{
	if (in_HCN1.Trai <= in_HCN2.Phai &&
		in_HCN1.Phai >= in_HCN2.Trai &&
		in_HCN1.Tren <= in_HCN2.Duoi &&
		in_HCN1.Duoi >= in_HCN2.Tren)
	{
		return true;
	}

	return false;
}

bool VaChamGame::get_DiemVaHCN(int in_X, int in_Y, const HCN& in_HCN)
{
	if (in_X < in_HCN.Trai ||
		in_X > in_HCN.Phai ||
		in_Y < in_HCN.Tren ||
		in_Y > in_HCN.Duoi)
	{
		return false;
	}

	return true;
}

bool VaChamGame::get_HCNVaHinhTron(const HCN& in_HCN, int in_TamX, int in_TamY, int in_BanKinh)
{
	int lPx = in_TamX;
	int lPy = in_TamY;

	if (lPx < in_HCN.Trai)
		lPx = in_HCN.Trai;
	else if (lPx > in_HCN.Phai)
		lPx = in_HCN.Phai;

	if (lPy > in_HCN.Duoi)
		lPy = in_HCN.Duoi;
	else if (lPy < in_HCN.Tren)
		lPy = in_HCN.Tren;

	int lDx = lPx - in_TamX;
	int lDy = lPy - in_TamY;

	return (lDx * lDx + lDy * lDy) <= in_BanKinh * in_BanKinh;
}
