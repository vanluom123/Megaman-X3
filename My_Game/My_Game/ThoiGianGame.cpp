#include "ThoiGianGame.h"

ThoiGianGame* ThoiGianGame::mTruongHop = NULL;

ThoiGianGame * ThoiGianGame::get_TruongHop()
{
	if (!mTruongHop)
	{
		mTruongHop = new ThoiGianGame();
	}
	return mTruongHop;
}

void ThoiGianGame::BatDauDem()
{
	if (!QueryPerformanceFrequency(&mTyLeThoiGian))
	{
		return;
	}

	QueryPerformanceCounter(&mBatDau);
}

float ThoiGianGame::get_ThoiGianDemDuoc()
{
	QueryPerformanceCounter(&mKetThuc);
	LARGE_INTEGER mDelta;
	mDelta.QuadPart = mKetThuc.QuadPart - mBatDau.QuadPart;

	return ((float)mDelta.QuadPart / mTyLeThoiGian.QuadPart);
}
