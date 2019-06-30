#include "QuadTree.h"

QuadTree::QuadTree(int in_CapDo, const HCN& in_HCN)
{
	mCapDo = in_CapDo;
	mGioiHan = in_HCN;
}

QuadTree::~QuadTree()
{
}

void QuadTree::DonDep()
{
	if (mBonNhanh)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mBonNhanh[i])
			{
				mBonNhanh[i]->DonDep();
				delete mBonNhanh[i];
				mBonNhanh[i] = nullptr;
			}
		}
		delete[] mBonNhanh;
	}
}

void QuadTree::ThemDoiTuong(DoiTuong * in_DoiTuong)
{
	int lViTri = get_ViTri(in_DoiTuong->get_HCNGioiHan());

	if (lViTri == -1)
	{
		mDSDoiTuong.push_back(in_DoiTuong);
	}
	else
	{
		if (mBonNhanh == NULL)
		{
			ChiaNhanh();
		}
		mBonNhanh[lViTri]->ThemDoiTuong(in_DoiTuong);
	}
}

void QuadTree::get_CacDoiTuongCoTheVaCham(std::vector<DoiTuong*>& out_CacDoiTuong, const DoiTuong * in_DoiTuong)
{
	int lViTri = get_ViTri(in_DoiTuong->get_HCNGioiHan());

	if (lViTri != -1)
	{
		for (int i = 0; i < (int)mDSDoiTuong.size(); i++)
		{
			out_CacDoiTuong.push_back(mDSDoiTuong[i]);
		}

		if (mBonNhanh != NULL)
		{
			mBonNhanh[lViTri]->get_CacDoiTuongCoTheVaCham(out_CacDoiTuong, in_DoiTuong);
		}
	}
	else
	{
		get_TatCaDoiTuong(out_CacDoiTuong);
	}
}

void QuadTree::get_CacDoiTuongCoTheVaCham(std::vector<DoiTuong*>& out_CacDoiTuong, const HCN& in_HCN)
{
	int lViTri = get_ViTri(in_HCN);

	if (lViTri != -1)
	{
		for (int i = 0; i < (int)mDSDoiTuong.size(); i++)
		{
			out_CacDoiTuong.push_back(mDSDoiTuong[i]);
		}

		if (mBonNhanh != NULL)
		{
			mBonNhanh[lViTri]->get_CacDoiTuongCoTheVaCham(out_CacDoiTuong, in_HCN);
		}
	}
	else
	{
		get_TatCaDoiTuong(out_CacDoiTuong);
	}
}

void QuadTree::get_TatCaDoiTuong(std::vector<DoiTuong*>& out_CacDoiTuong)
{
	for (int i = 0; i < (int)mDSDoiTuong.size(); i++)
	{
		out_CacDoiTuong.push_back(mDSDoiTuong[i]);
	}

	if (mBonNhanh)
	{
		for (int i = 0; i < 4; i++)
		{
			mBonNhanh[i]->get_TatCaDoiTuong(out_CacDoiTuong);
		}
	}
}

int QuadTree::get_TongDoiTuong()
{
	int lTong = mDSDoiTuong.size();

	if (mBonNhanh)
	{
		for (int i = 0; i < 4; i++)
		{
			lTong += mBonNhanh[i]->get_TongDoiTuong();
		}
	}

	return lTong;
}


int QuadTree::get_ViTri(const HCN& in_DoiTuong)
{
	float lDuongChiaDoc = (mGioiHan.Trai + mGioiHan.Phai) / 2.0f;
	float lDuongChiaNgang = (mGioiHan.Tren + mGioiHan.Duoi) / 2.0f;

	if (in_DoiTuong.Tren > mGioiHan.Tren && 
		in_DoiTuong.Duoi < lDuongChiaNgang)
	{
		if (in_DoiTuong.Trai > mGioiHan.Trai &&
			in_DoiTuong.Phai < lDuongChiaDoc)
		{
			return 0;
		}
		else if (in_DoiTuong.Trai > lDuongChiaDoc &&
			in_DoiTuong.Phai < mGioiHan.Phai)
		{
			return 1;
		}
	}
	else if (in_DoiTuong.Tren > lDuongChiaNgang &&
		in_DoiTuong.Duoi < mGioiHan.Duoi)
	{
		if (in_DoiTuong.Trai > mGioiHan.Trai &&
			in_DoiTuong.Phai < lDuongChiaDoc)
		{
			return 2;
		}
		else if (in_DoiTuong.Trai > lDuongChiaDoc &&
			in_DoiTuong.Phai < mGioiHan.Phai)
		{
			return 3;
		}
	}	

	return -1;
}

void QuadTree::ChiaNhanh()
{
	mBonNhanh = new QuadTree * [4];

	int lChieuRongNhanh = (mGioiHan.Phai - mGioiHan.Trai) / 2;
	int lChieuCaoNhanh = (mGioiHan.Duoi - mGioiHan.Tren) / 2;

	mBonNhanh[0] = new QuadTree(mCapDo + 1,HCN(
		mGioiHan.Trai,
		mGioiHan.Trai + lChieuRongNhanh,
		mGioiHan.Tren,
		mGioiHan.Tren + lChieuCaoNhanh));

	mBonNhanh[1] = new QuadTree(mCapDo + 1, HCN(
		mGioiHan.Trai + lChieuRongNhanh,
		mGioiHan.Trai + 2 * lChieuRongNhanh,
		mGioiHan.Tren, 
		mGioiHan.Tren + lChieuCaoNhanh));

	mBonNhanh[2] = new QuadTree(mCapDo + 1, HCN(
		mGioiHan.Trai,
		mGioiHan.Trai + lChieuRongNhanh, 
		mGioiHan.Tren + lChieuCaoNhanh,
		mGioiHan.Tren + 2 * lChieuCaoNhanh));

	mBonNhanh[3] = new QuadTree(mCapDo + 1, HCN(
		mGioiHan.Trai + lChieuRongNhanh,
		mGioiHan.Trai + 2 * lChieuRongNhanh,
		mGioiHan.Tren + lChieuCaoNhanh,
		mGioiHan.Tren + 2 * lChieuCaoNhanh));
}

bool QuadTree::get_CoChua(const DoiTuong * in_DoiTuong)
{
	HCN lHCN = in_DoiTuong->get_HCNGioiHan();

	if (lHCN.Trai >= mGioiHan.Trai &&
		lHCN.Phai <= mGioiHan.Phai &&
		lHCN.Tren >= mGioiHan.Tren &&
		lHCN.Duoi <= mGioiHan.Duoi)
	{
		return true;
	}

	return false;
}
