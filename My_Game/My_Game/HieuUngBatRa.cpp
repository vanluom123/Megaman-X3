#include "HieuUngBatRa.h"



HieuUngBatRa::HieuUngBatRa()
	:
	DoiTuong(Vec2(), Vec2(), 0, 0)
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(-6, -2, HCN(126 - 124, 138 - 124, 607 - 604, 619 - 604)));
	mHoatHinh = new HoatHinh(lDSTTFrame);


	mBienMat = true;
	mTG_DemTonTai = 999.9f;
}

HieuUngBatRa::~HieuUngBatRa()
{
	if (mHoatHinh)
		delete mHoatHinh;
}

void HieuUngBatRa::CapNhat(float in_tg)
{
	if (mBienMat)
	{
		return;
	}
	if (!mBienMat)
	{
		mTG_DemTonTai += in_tg;
	}
	if (mTG_DemTonTai > mTG_TonTai && !mBienMat)
	{
		mBienMat = true;
	}
}

void HieuUngBatRa::Ve(const Vec2 & in_DoDoi)
{
	if (!mBienMat)
	{
		mHoatHinh->Ve(DS_HinhAnh::get_TH()->HieuUngBatRa_png, mLatHinh, mToaDo, in_DoDoi);
	}
}

void HieuUngBatRa::Remake()
{
	mTG_DemTonTai = 0.0f;
	mBienMat = false;
	mHoatHinh->Remake();
}
