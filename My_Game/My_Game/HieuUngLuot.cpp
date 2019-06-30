#include "HieuUngLuot.h"
#include "XMan.h"

HieuUngLuot::HieuUngLuot()
	:
	DoiTuong(Vec2(), Vec2(), 0, 0)
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 154, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 157, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 166, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 169, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(185, 212, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(232, 256, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(273, 301, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(312, 340, 812, 842)));
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(349, 377, 812, 842)));
	lDSTTFrame.push_back(ThongTinFrame(32, 30, HCN(349, 377, 812, 842), 0.001f));
	mHoatHinh = new HoatHinh(lDSTTFrame);
	//mHoatHinh->set_TiLe(Vec2(1.0f, 1.3f));

	mTG_TonTai = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_TonTai += lDSTTFrame[i].ThoiGian;
	}

	//mHoatHinh->set_GocXoayHinh(180.0f);

	mBienMat = true;
	mTG_DemTonTai = 999.9f;
}

HieuUngLuot::~HieuUngLuot()
{
	delete mHoatHinh;
}

void HieuUngLuot::CapNhat(float in_tg)
{
	if (!mBienMat)
	{
		mTG_DemTonTai += in_tg;
		mHoatHinh->CapNhat(in_tg);
	}
	if (mTG_DemTonTai > mTG_TonTai && !mBienMat)
	{
		mBienMat = true;
	}
}

void HieuUngLuot::Ve(const Vec2 & in_DoDoi)
{
	//if (!mBienMat)
	//{
	//	if (!mLatHinh)
	//	{
	//		mHoatHinh->set_GocXoayHinh(180.0f);
	//		mHoatHinh->set_LatTheoChieuDoc(mLatHinh);
	//	}
	//	else
	//	{
	//		mHoatHinh->set_GocXoayHinh(181.0f);
	//		mHoatHinh->set_LatTheoChieuDoc(mLatHinh);
	//	}
	//	mHoatHinh->set_ToaDo(mToaDo);
	//	mHoatHinh->set_DoDoi(in_DoDoi);
	//	mHoatHinh->Ve();
	//}
}

 void HieuUngLuot::Remake()
{
	mTG_DemTonTai = 0.0f;
	mBienMat = false;
	mHoatHinh->Remake();
}
