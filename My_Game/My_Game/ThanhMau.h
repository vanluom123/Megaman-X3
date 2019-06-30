#pragma once

#include "HinhAnh.h"
#include "DS_HinhAnh.h"

class ThanhMau
{
public:
	ThanhMau(const Vec2& in_ToaDo = Vec2(10.0f, 110.0f), bool in_Boss = false) {
		LoadHinhAnhVao();
		mToaDo = in_ToaDo;
		mBieuTuong->set_ToaDo(mToaDo);
		mKhungTren->set_ToaDo(mToaDo + Vec2(0.0f, -58.0f));
		Boss = in_Boss;
	}


	void LoadHinhAnhVao()
	{
		mBieuTuong = new HinhAnh("Resources/XMan/ThanhMau.png", D3DCOLOR_XRGB(50, 96, 166));
		mBieuTuong->set_ChieuRong(14);
		mBieuTuong->set_ChieuCao(16);
		mBieuTuong->set_HCN(HCN(2, 2 + 14, 45, 45 + 16));

		mKhungGiua = new HinhAnh("Resources/XMan/ThanhMau.png", D3DCOLOR_XRGB(50, 96, 166));
		mKhungGiua->set_ChieuRong(14);
		mKhungGiua->set_ChieuCao(16);
		mKhungGiua->set_HCN(HCN(2, 2 + 14, 9, 9 + 16));

		mKhungTren = new HinhAnh("Resources/XMan/ThanhMau.png", D3DCOLOR_XRGB(50, 96, 166));
		mKhungTren->set_ChieuRong(14);
		mKhungTren->set_ChieuCao(4);
		mKhungTren->set_HCN(HCN(2, 2 + 14, 3, 3 + 4));

		mMau = new HinhAnh("Resources/XMan/ThanhMau.png", D3DCOLOR_XRGB(50, 96, 166));
		mMau->set_ChieuRong(6);
		mMau->set_ChieuCao(2);
		mMau->set_HCN(HCN(6, 6 + 6, 41, 41 + 2));
	}

	void Ve(int in_HP)
	{
		if (Boss)
		{
			DS_HinhAnh::get_TH()->BieuTuongThanhMauBoss->set_ToaDo(mToaDo);
			DS_HinhAnh::get_TH()->BieuTuongThanhMauBoss->Ve();

			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -16.0f));
			mKhungGiua->Ve();
			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -32.0f));
			mKhungGiua->Ve();
			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -48.0f));
			mKhungGiua->Ve();
			mKhungTren->Ve();
			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -64.0f));
			mKhungGiua->Ve();
			mKhungTren->set_ToaDo(mToaDo + Vec2(0.0f, -74.0f));
			mKhungTren->Ve();
		}
		else
		{
			mBieuTuong->Ve();

			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -16.0f));
			mKhungGiua->Ve();
			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -32.0f));
			mKhungGiua->Ve();
			mKhungGiua->set_ToaDo(mToaDo + Vec2(0.0f, -48.0f));
			mKhungGiua->Ve();
			mKhungTren->Ve();
		}

		for (int i = 0; i < int((in_HP + 4) / (mHPToiDa / 24.0f)); i++)
		{
			mMau->set_ToaDo(mToaDo + Vec2(0.0f, -9.0f - i * 2.0f));
			mMau->Ve();
		}
	}

private:
	bool Boss = false;
	HinhAnh *mBieuTuong;
	HinhAnh *mKhungGiua;
	HinhAnh *mKhungTren;
	HinhAnh *mMau;
	
	Vec2 mToaDo;

	int mHPToiDa = 100;

public:
	~ThanhMau()
	{

	}
};

