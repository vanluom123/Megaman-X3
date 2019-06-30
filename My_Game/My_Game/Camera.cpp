#include "Camera.h"
#include "ToanCauGame.h"
#include "GameLog.h"

// bắt buộc cung cấp cho Compiler
Vec2 Camera::mToaDo = Vec2(0.0f, 0.0f); 
int Camera::mChieuRong = 0;
int Camera::mChieuCao = 0;
int Camera::mGioiHanTrai = 0;
int Camera::mGioiHanPhai = 769 + 254;
int Camera::mGioiHanTren = 770;
int Camera::mGioiHanDuoi = 770 + 220;

int Camera::mGioiHanTraiTiepTheo = 0;
int Camera::mGioiHanPhaiTiepTheo = 769 + 254;
int Camera::mGioiHanTrenTiepTheo = 770;
int Camera::mGioiHanDuoiTiepTheo = 770 + 220;
int Camera::CheckPoint = -1;
int Camera::speed = 4;

void Camera::set_ToaDo(const Vec2& in_ToaDo) 
{
	switch (CheckPoint)
	{
	case -1:
		speed = 4;
		mGioiHanTrai = 0;
		mGioiHanPhai = 769 + 254;
		mGioiHanTren = 770;
		mGioiHanDuoi = 770 + 220;

		mGioiHanTraiTiepTheo = 0;
		mGioiHanPhaiTiepTheo = 769 + 254;
		mGioiHanTrenTiepTheo = 770;
		mGioiHanDuoiTiepTheo = 770 + 220;

		CheckPoint++;
		break;
	case 0:
		if (in_ToaDo.x >= 790.0f && in_ToaDo.x <= 950.0f &&
			in_ToaDo.y >= 800.0f && in_ToaDo.y <= 950.0f)
		{
			mGioiHanTrai = 660;
			mGioiHanTraiTiepTheo = 769;
			mGioiHanTren = mGioiHanTrenTiepTheo = 256;

			CheckPoint++;
		}
		break;

	case 1:
		if (in_ToaDo.x >= 850.0f && in_ToaDo.x <= 950.0f &&
			in_ToaDo.y >= 350.0f && in_ToaDo.y <= 430.0f)
		{
			mGioiHanDuoi = 550;
			mGioiHanDuoiTiepTheo = 256 + mChieuCao;
			mGioiHanPhaiTiepTheo = 2048;

			CheckPoint++;
		}

	case 2:
		if (in_ToaDo.x >= 1650.0f && in_ToaDo.x <= 1700.0f &&
			in_ToaDo.y >= 200.0f && in_ToaDo.y <= 450.0f)
		{
			mGioiHanTrai = 1450;
			mGioiHanTraiTiepTheo = 1536;
			mGioiHanDuoiTiepTheo = 1248;

			CheckPoint++;
		}
		break;

	case 3:
		if (in_ToaDo.x >= 1750.0f && in_ToaDo.x <= 1850.0f &&
			in_ToaDo.y >= 1000.0f && in_ToaDo.y <= 1200.0f)
		{
			mGioiHanPhaiTiepTheo = 2319;

			CheckPoint++;
		}
		break;

	case 4:
		if (in_ToaDo.x >= 2300.0f && in_ToaDo.x <= 2315.0f &&
			in_ToaDo.y >= 1050.0f && in_ToaDo.y <= 1200.0f)
		{
			mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 2305;
			mGioiHanPhaiTiepTheo = mGioiHanTraiTiepTheo + mChieuRong;
			mGioiHanTrenTiepTheo = mGioiHanTren = 1248 - mChieuCao;
			CheckPoint++;
			speed = 2;
		}
		break;


	case 5:
		if (in_ToaDo.x >= 2548.0f && in_ToaDo.x <= 2555.0f)
		{
			mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 2548;
			mGioiHanPhaiTiepTheo = 6144;
			mGioiHanTrenTiepTheo = 840;
			speed = 4;
			CheckPoint++;
		}

		break;

	case 6:
		if (in_ToaDo.x >= 2950.0f && in_ToaDo.x <= 3000.0f)
		{
			mGioiHanTrai = mGioiHanTraiTiepTheo = 2817;
			mGioiHanPhai = mGioiHanPhaiTiepTheo = 4864 + mChieuRong;
			mGioiHanTren = mGioiHanTrenTiepTheo = 840;
			mGioiHanDuoi = mGioiHanDuoiTiepTheo = 1248;
			CheckPoint++;
		}
		break;

	case 7:
		if (in_ToaDo.x >= 4400.0f &&
			in_ToaDo.x <= 4430.0f)
		{
			mGioiHanTrenTiepTheo = 1248 - mChieuCao;
			CheckPoint++;
		}
		break;

	case 8:
		if (in_ToaDo.x >= 4800.0f &&
			in_ToaDo.x <= 4830.0f)
		{
			mGioiHanTrai = mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 4864;
			CheckPoint++;
			speed = 2;
		}

		break;

	// SAU KHI BOSS 2 CHET <<>>
	case 9:
		if (in_ToaDo.x >= 5250.0f &&
			in_ToaDo.x <= 5300.0f)
		{
			mGioiHanTrai = mGioiHanTraiTiepTheo = 4864;
			mGioiHanPhai = mGioiHanPhaiTiepTheo = 5649;
			mGioiHanTren = mGioiHanTrenTiepTheo = 1248 - mChieuCao;
			mGioiHanDuoi = mGioiHanDuoiTiepTheo = 1248;
			speed = 4;
			CheckPoint++;
		}

	case 10:
		if (in_ToaDo.x >= 5635.0f &&
			in_ToaDo.x <= 5645.0f)
		{
			mGioiHanTrai = mGioiHanTrai = mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 5633;
			mGioiHanPhaiTiepTheo = 5633 + mChieuRong;
			speed = 2;
			CheckPoint++;
		}
		break;

	case 11:
		if (in_ToaDo.x >= 5875.0f && in_ToaDo.x <= 5885.0f)
		{
			mGioiHanTraiTiepTheo = 5871;
			mGioiHanPhaiTiepTheo = 6144;
			CheckPoint++;
		}
		break;

	case 12:
		if (in_ToaDo.x >= 6035.0f && in_ToaDo.x <= 6045.0f)
		{
			mGioiHanTraiTiepTheo = 5889;
			mGioiHanDuoiTiepTheo = 1794 + 220;
			speed = 5;
			CheckPoint++;
		}
		break;

	case 13:
		if (in_ToaDo.x >= 5985.0f && in_ToaDo.x <= 6015.0f &&
			in_ToaDo.y >= 1790.0f && in_ToaDo.y <= 1990.0f)
		{
			mGioiHanPhaiTiepTheo = 7934;
			mGioiHanTrenTiepTheo = 1794;
			CheckPoint++;
		}
		break;

		// CHECK_TIEPTHEO
	case 14:
		if (in_ToaDo.x >= 6300.0f && in_ToaDo.x <= 6350.0f)
		{
			mGioiHanTrai = mGioiHanTraiTiepTheo = 4864;
			mGioiHanPhai = mGioiHanPhaiTiepTheo = /*7934*/7408;
			mGioiHanTren = mGioiHanTrenTiepTheo = 1794;
			mGioiHanDuoi = mGioiHanDuoiTiepTheo = 1794 + 220;
			speed = 4;
			CheckPoint++;
		}
		break;
	case 15:
		if (in_ToaDo.x >= 7395.0f && in_ToaDo.x <= 7405.0f)
		{
			mGioiHanTrai = mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 7392;
			mGioiHanPhaiTiepTheo = 7696;
			speed = 2;
			CheckPoint++;
		}
		break;

	case 16:
		if (in_ToaDo.x >= 7500.0f && in_ToaDo.x <= 7530.0f)
		{
			mGioiHanTrai = mGioiHanTraiTiepTheo = 7392;
			mGioiHanPhai = mGioiHanPhaiTiepTheo = 7696;
			mGioiHanTren = mGioiHanTrenTiepTheo = 1794;
			mGioiHanDuoi = mGioiHanDuoiTiepTheo = 1794 + 220;
			CheckPoint++;
		}
		break;

	case 17:
		if (in_ToaDo.x >= 7683.0f && in_ToaDo.x <= 7690.0f)
		{
			mGioiHanTrai = mGioiHanTrai = (int)in_ToaDo.x - mChieuRong / 2 - 1;
			mGioiHanTraiTiepTheo = 7934 - mChieuRong;
			mGioiHanPhaiTiepTheo = 7934;
			speed = 2;
			CheckPoint++;
		}
		break;

	default:
		break;
	}
	
	GAMELOG("%d", CheckPoint);

	mToaDo = in_ToaDo;

	if (mToaDo.x < mGioiHanTrai + mChieuRong / 2.0f)
	{
		mToaDo.x = mGioiHanTrai + mChieuRong / 2.0f;
	}
	if (mToaDo.x > mGioiHanPhai - mChieuRong / 2.0f)
	{
		mToaDo.x = mGioiHanPhai - mChieuRong / 2.0f;
	}
	if (mToaDo.y < mGioiHanTren + mChieuCao / 2.0f)
	{
		mToaDo.y = mGioiHanTren + mChieuCao / 2.0f;
	}
	if (mToaDo.y > mGioiHanDuoi - mChieuCao / 2.0f)
	{
		mToaDo.y = mGioiHanDuoi - mChieuCao / 2.0f;
	}

	for (int k = 0; k < speed; k++)
	{
		if (mGioiHanTrai < mGioiHanTraiTiepTheo)
			mGioiHanTrai++;
		else if (mGioiHanTrai > mGioiHanTraiTiepTheo)
			mGioiHanTrai--;

		if (mGioiHanPhai < mGioiHanPhaiTiepTheo)
			mGioiHanPhai++;
		else if (mGioiHanPhai > mGioiHanPhaiTiepTheo)
			mGioiHanPhai--;

		if (mGioiHanTren < mGioiHanTrenTiepTheo)
			mGioiHanTren++;
		else if (mGioiHanTren > mGioiHanTrenTiepTheo)
			mGioiHanTren--;

		if (mGioiHanDuoi < mGioiHanDuoiTiepTheo)
			mGioiHanDuoi++;
		else if (mGioiHanDuoi > mGioiHanDuoiTiepTheo)
			mGioiHanDuoi--;
	}

}

void Camera::set_KichThuoc(int in_ChieuRong, int in_ChieuCao)
{
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

void Camera::set_GioiHan(int in_Trai, int in_Phai, int in_Tren, int in_Duoi)
{
	mGioiHanTrai = in_Trai;
	mGioiHanPhai = in_Phai;
	mGioiHanTren = in_Tren;
	mGioiHanDuoi = in_Duoi;
}

HCN Camera::get_HCNGioiHan()
{
	return HCN(
		int(mToaDo.x - mChieuRong / 2.0f),
		int(mToaDo.x + mChieuRong / 2.0f),
		int(mToaDo.y - mChieuCao / 2.0f),
		int(mToaDo.y + mChieuCao / 2.0f));
}

HCN Camera::get_HCNGioiHan_MoRong()
{
	return HCN(
		int(mToaDo.x - mChieuRong / 1.2f),
		int(mToaDo.x + mChieuRong / 1.2f),
		int(mToaDo.y - mChieuCao / 1.2f ),
		int(mToaDo.y + mChieuCao / 1.2f ));
}

HCN Camera::get_HCNGioiHan_MoRong_1()
{
	return HCN(
		int(mToaDo.x - mChieuRong / 1.8f),
		int(mToaDo.x + mChieuRong / 1.8f),
		int(mToaDo.y - mChieuCao / 1.8f),
		int(mToaDo.y + mChieuCao / 1.8f));
}

int Camera::get_ChieuRong()
{
	return mChieuRong;
}

int Camera::get_ChieuCao()
{
	return mChieuCao;
}

Vec2 Camera::get_ToaDo()
{
	return mToaDo;
}
