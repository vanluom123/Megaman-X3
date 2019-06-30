#pragma once

#include <Windows.h>

class ThoiGianGame
{
public:
	static ThoiGianGame* get_TruongHop(); // Kiểu dữ liệu là 1 lớp, ko cần ghi kiểu dữ liệu phía trước hàm
	void BatDauDem();
	float get_ThoiGianDemDuoc();

private:
	static ThoiGianGame *mTruongHop;
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
};
