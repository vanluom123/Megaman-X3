#include "DoiTuong.h"

DoiTuong::DoiTuong(const Vec2& in_ToaDo, const Vec2& in_VanToc, int in_ChieuRong, int in_ChieuCao)
{
	mToaDo = in_ToaDo;
	mVanToc = in_VanToc;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

void DoiTuong::set_ToaDo(Vec2 in_ToaDo)
{
	mToaDo = in_ToaDo;
}

void DoiTuong::set_VanToc(Vec2 in_VanToc)
{
	mVanToc = in_VanToc;
}

void DoiTuong::set_ChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

void DoiTuong::set_ChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

Vec2 DoiTuong::get_ToaDo() const
{
	return mToaDo;
}

Vec2 DoiTuong::get_VanToc() const
{
	return mVanToc;
}

int DoiTuong::get_ChieuRong() const
{
	return mChieuRong;
}

int DoiTuong::get_ChieuCao() const
{
	return mChieuCao;
}

HCN DoiTuong::get_HCNGioiHan() const
{
	return HCN(
		int(mToaDo.x - mChieuRong / 2.0f),
		int(mToaDo.x + mChieuRong / 2.0f),
		int(mToaDo.y - mChieuCao / 2.0f),
		int(mToaDo.y + mChieuCao / 2.0f));
}

RECT DoiTuong::get_RECT() const
{
	RECT a;
	HCN mGioiHan = get_HCNGioiHan();
	a.left = mGioiHan.Trai;
	a.right = mGioiHan.Phai;
	a.top = mGioiHan.Tren;
	a.bottom = mGioiHan.Duoi;
	return a;
}

eLoaiDoiTuong DoiTuong::get_LoaiDoiTuong() const 
{
	return mLoaiDoiTuong;
}
