#include "Bui.h"



Bui::Bui(const Vec2 & in_ToaDo, const Vec2& in_VanToc)
	:
	DoiTuong(in_ToaDo, in_VanToc, 0, 0)
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(8, 8,   HCN(30 - 26, 38 - 26, 609 - 601, 617 - 601), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(10, 11, HCN(40 - 26, 50 - 26, 610 - 601, 621 - 601), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(13, 13, HCN(53 - 26, 66 - 26, 610 - 601, 623 - 601), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(71 - 26, 85 - 26, 609 - 601, 623 - 601), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(88 - 26, 102 - 26, 609 - 601, 623 - 601), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(14, 14, HCN(106 - 26, 120 - 26, 609 - 601, 623 - 601), 0.08f));
	mHoatHinh = new HoatHinh(lDSTTFrame);
}

Bui::~Bui()
{
	delete mHoatHinh;
}

void Bui::CapNhat(float in_tg)
{
	// nếu không còn tồn tại thì ko cần Cập Nhật
	if (mTGDem_TonTai > mTG_TonTai)
	{
		return;
	}

	mTGDem_TonTai += in_tg;
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;
	mHoatHinh->CapNhat(in_tg);
}

void Bui::Ve(const Vec2 & in_DoDoi)
{
	// nếu không còn tồn tại thì ko cần Vẽ
	if (mTGDem_TonTai > mTG_TonTai)
	{
		return;
	}

	mHoatHinh->Ve(DS_HinhAnh::get_TH()->Bui_png, false, mToaDo, in_DoDoi);
}

void Bui::Remake()
{
	mTGDem_TonTai = 0.0f;
	mHoatHinh->Remake();
}
