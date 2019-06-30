#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "VaChamGame.h"
#include "Camera.h"
#include "DoiTuong.h"
#include "KieuDuLieu.h"

class QuadTree
{
public:
	QuadTree(int in_CapDo, const HCN& in_HCN);
	~QuadTree();

// FUNCTION
	void DonDep();
	void ThemDoiTuong(DoiTuong *in_DoiTuong);
	void get_CacDoiTuongCoTheVaCham(std::vector<DoiTuong*> &out_CacDoiTuong, const DoiTuong *in_DoiTuong);
	void get_CacDoiTuongCoTheVaCham(std::vector<DoiTuong*> &out_CacDoiTuong, const HCN& in_HCN);
	void get_TatCaDoiTuong(std::vector<DoiTuong*> &out_CacDoiTuong);
	int get_TongDoiTuong();

	QuadTree** get_Nodes()
	{
		return mBonNhanh;
	}
	
	RECT get_RECT() const
	{
		RECT a;
		a.left = mGioiHan.Trai;
		a.right = mGioiHan.Phai;
		a.top = mGioiHan.Tren;
		a.bottom = mGioiHan.Duoi;
		return a;
	}

// INFORMATION
private:
	int mCapDo;
	HCN mGioiHan;
	QuadTree **mBonNhanh;
	std::vector<DoiTuong*> mDSDoiTuong;

// SUB-FUNCTION
private:
	int get_ViTri(const HCN& in_DoiTuong);
	void ChiaNhanh();
	bool get_CoChua(const DoiTuong *in_DoiTuong);
};

