#include "HinhAnh.h"
#include "ToanCauGame.h"

HinhAnh::HinhAnh(const char * in_DuongDan, const D3DCOLOR &in_Color)
{
	D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
	mToaDo = Vec2(0.0f, 0.0f);
	mChieuRong = mThongTinHinhAnh.Width;
	mChieuCao = mThongTinHinhAnh.Height;
	mHCN = HCN(0, mChieuRong, 0, mChieuCao);
	mTiLe = Vec2(1.0f, 1.0f);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mGocXoayHinh = 0.0f;
	mDoDoi = Vec2(0.0f, 0.0f);

	//mXuLyHinhAnh->GetDevice(&lThietBi);
	D3DXCreateTextureFromFileExA(
		ToanCauGame::mThietBi,
		in_DuongDan,
		mThongTinHinhAnh.Width,
		mThongTinHinhAnh.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		in_Color, // màu nền màu trắng sẽ bị mất hết
		&mThongTinHinhAnh,
		NULL,
		&mKetCauHinhAnh);
}

HinhAnh::~HinhAnh()
{
	if (mKetCauHinhAnh != NULL)
	{
		mKetCauHinhAnh->Release();
	}
}

void HinhAnh::Ve(const D3DCOLOR& in_SubColor)
{
	D3DXVECTOR2 lTrungTamTiLe = D3DXVECTOR2(float((int)mToaDo.x), float((int)mToaDo.y));
	D3DXVECTOR2 lTrungTamXoayHinh = D3DXVECTOR2(float((int)mToaDo.x), float((int)mToaDo.y));
	D3DXVECTOR2 lTiLe = D3DXVECTOR2(mTiLe.x, mTiLe.y);
	D3DXVECTOR2 lDoDoi = D3DXVECTOR2(float((int)mDoDoi.x), float((int)mDoDoi.y));

	D3DXMatrixTransformation2D(
		&mMaTran,
		&lTrungTamTiLe, 
		0, 
		&lTiLe,
		&lTrungTamXoayHinh, 
		float(mGocXoayHinh),
		&lDoDoi);
	D3DXMATRIX lMaTranCu;

	ToanCauGame::mXuLyHinhAnh->GetTransform(&lMaTranCu);
	ToanCauGame::mXuLyHinhAnh->SetTransform(&mMaTran);

	RECT lHCN;
	lHCN.left = long(mHCN.Trai);
	lHCN.right = long(mHCN.Phai);
	lHCN.top = long(mHCN.Tren);
	lHCN.bottom = long(mHCN.Duoi);
	D3DXVECTOR3 lTrungTam = D3DXVECTOR3(float(mChieuRong) / 2.0f, float(mChieuCao) / 2.0f, float(0));
	D3DXVECTOR3 lToaDo = D3DXVECTOR3(float((int)mToaDo.x), float((int)mToaDo.y), 0.0f);

	ToanCauGame::mXuLyHinhAnh->Draw(
		mKetCauHinhAnh,
		&lHCN,
		&lTrungTam,
		&lToaDo,
		in_SubColor); // những pixel nào có màu trắng		
											// thì sẽ tô màu này lên

	ToanCauGame::mXuLyHinhAnh->SetTransform(&lMaTranCu); // thiết lập lại Ma Trận Cũ để Xử Lý Hình Ảnh chỉ áp dụng Transform với class này
}










/////////////////////////////
/*  Các thủ tục SET - GET  */
void HinhAnh::set_LatTheoChieuDoc(bool in_Co)
{
	if (mLatTheoChieuDoc != in_Co)
	{
		mLatTheoChieuDoc = in_Co;
		mTiLe.y = -mTiLe.y;
	}
}

void HinhAnh::set_LatTheoChieuNgang(bool in_Co)
{
	if (mLatTheoChieuNgang != in_Co)
	{
		mLatTheoChieuNgang = in_Co;
		mTiLe.x = -mTiLe.x;
	}
}

Vec2 HinhAnh::get_ToaDo() const
{
	return mToaDo;
}

void HinhAnh::set_ToaDo(const Vec2& in_ToaDo)
{
	mToaDo = in_ToaDo;
}

void HinhAnh::set_ChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

int HinhAnh::get_ChieuRong() const
{
	return mChieuRong;
}

void HinhAnh::set_ChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

int HinhAnh::get_ChieuCao() const
{
	return mChieuCao;
}

void HinhAnh::set_HCN(const HCN& in_HCN)
{
	mHCN = in_HCN;
}

void HinhAnh::set_TiLe(const Vec2& in_TiLe)
{
	mTiLe = in_TiLe;
}

Vec2 HinhAnh::get_TiLe() const
{
	return mTiLe;
}

bool HinhAnh::get_LatTheoChieuNgang() const
{
	return mLatTheoChieuNgang;
}

bool HinhAnh::get_LatTheoChieuDoc() const
{
	return mLatTheoChieuDoc;
}

void HinhAnh::set_GocXoayHinh(float in_GocXoay)
{
	mGocXoayHinh = in_GocXoay;
}

float HinhAnh::get_GocXoayHinh() const
{
	return mGocXoayHinh;
}

void HinhAnh::set_DoDoi(const Vec2& in_DoDoi)
{
	mDoDoi = in_DoDoi;
}

Vec2 HinhAnh::get_DoDoi() const
{
	return mDoDoi;
}

