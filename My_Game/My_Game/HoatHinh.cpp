#include "HoatHinh.h"

HoatHinh::HoatHinh(const std::vector<ThongTinFrame>& in_DSThongTinFrame)
{
	for (int i = 0; i < (int)in_DSThongTinFrame.size(); i++)
	{
		mDSThongTinFrame.push_back(in_DSThongTinFrame[i]);
	}
	mViTriFrame = 0;
	mThoiGianDem = 0.0f;
}

void HoatHinh::CapNhat(float in_tg)
{
	// nếu chỉ có 1 Frame thì ko cần phải cập nhật
	if (mDSThongTinFrame.size() <= 1)
	{
		return;
	}

	mThoiGianDem += in_tg;

	// thời gian phải lớn hơn Thời gian Frame hiện tại thì mới đổi Frame
	if (mThoiGianDem < mDSThongTinFrame[mViTriFrame].ThoiGian)
	{
		return;
	}

	// thực hiện các dòng bên dưới để Cập Nhật
	mThoiGianDem = 0.0f; //TEST
	mViTriFrame++;

	if (mViTriFrame >= (int)mDSThongTinFrame.size())
	{
		mViTriFrame = 0;
	}
}

void HoatHinh::Ve(HinhAnh *in_HinhAnh, bool in_LatHinh, const Vec2& in_ToaDo, const Vec2& in_DoDoi,
	const D3DCOLOR &in_SubColor, bool in_LatDoc)
{
	// set THÔNG TIN cho Biến con trỏ hình ảnh được đưa vào và vẽ lên
	in_HinhAnh->set_ChieuRong(mDSThongTinFrame[mViTriFrame].ChieuRong);
	in_HinhAnh->set_ChieuCao(mDSThongTinFrame[mViTriFrame].ChieuCao);
	in_HinhAnh->set_HCN(mDSThongTinFrame[mViTriFrame].Hcn);

	in_HinhAnh->set_LatTheoChieuNgang(in_LatHinh);
	in_HinhAnh->set_LatTheoChieuDoc(in_LatDoc);
	in_HinhAnh->set_ToaDo(in_ToaDo);
	in_HinhAnh->set_DoDoi(in_DoDoi);

	in_HinhAnh->Ve(in_SubColor);
}

void HoatHinh::Remake(int in_ViTri, float in_Time)
{
	// nếu chỉ có 1 Frame thì ko cần phải cập nhật
	if (mDSThongTinFrame.size() <= 1)
		return;

	mThoiGianDem = in_Time;
	mViTriFrame = in_ViTri;
}
