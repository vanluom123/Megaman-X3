#include "HieuUngMap.h"
#include "DS_HinhAnh.h"



HieuUngMap::HieuUngMap(const Vec2& in_ToaDo, int in_Rong, int in_Cao, HoatHinh *in_HieuUng, int in_PhanLoai)
	:
	DoiTuong(in_ToaDo, Vec2(), in_Rong, in_Cao)
{
	HH_HieuUng = in_HieuUng;
	PhanLoai = in_PhanLoai;
}


HieuUngMap::~HieuUngMap()
{
}

void HieuUngMap::Ve(const Vec2 & in_DoDoi)
{
	switch (PhanLoai)
	{
	case 1:
		HH_HieuUng->Ve(DS_HinhAnh::get_TH()->HieuUngMap1, false, mToaDo, Vec2(in_DoDoi.x / 2.0f, in_DoDoi.y));
		break;

	case 2:
		HH_HieuUng->Ve(DS_HinhAnh::get_TH()->HieuUngMap2, false, mToaDo, Vec2(in_DoDoi.x / 2.0f, in_DoDoi.y));
		break;

	default:
		break;
	}
}
