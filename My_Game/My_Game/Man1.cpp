#include "Man1.h"
#include "Camera.h"
#include "KieuDuLieu.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"

#include "TrucXoay.h"
#include "MayBay.h"

#include "Sound.h"
#include "HieuUngMap.h"
#include <vector>


Man1::Man1()
{
	Sound::getInstance()->loadSound("Resources/Sound/Nhac_Nen.wav", "Nhac_Nen");
	Sound::getInstance()->play("Nhac_Nen", true, 0);

	Sound::getInstance()->loadSound("Resources/Sound/Ban_Dan_Lv1.wav", "Ban_Dan_Lv1");
	Sound::getInstance()->loadSound("Resources/Sound/Ban_Dan_Lv2.wav", "Ban_Dan_Lv2");
	Sound::getInstance()->loadSound("Resources/Sound/Ban_Dan_Lv3.wav", "Ban_Dan_Lv3");
	Sound::getInstance()->loadSound("Resources/Sound/Diet_Xong_Boss.wav", "Diet_Xong_Boss");
	Sound::getInstance()->loadSound("Resources/Sound/Ech_Ban_Dan.wav", "Ech_Ban_Dan");
	Sound::getInstance()->loadSound("Resources/Sound/Gong_Suc.wav", "Gong_Suc");
	Sound::getInstance()->loadSound("Resources/Sound/Gong_Suc_Keo_Dai.wav", "Gong_Suc_Keo_Dai");
	Sound::getInstance()->loadSound("Resources/Sound/Hieu_Ung_No.wav", "Hieu_Ung_No");
	Sound::getInstance()->loadSound("Resources/Sound/Nhac_Danh_Boss.wav", "Nhac_Danh_Boss");
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Bi_Thuong.wav", "XMan_Bi_Thuong");
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Chet.wav", "XMan_Chet");
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Hoi_Mau.wav", "XMan_Hoi_Mau");
	/*Sound::getInstance()->setVolume(800.0f, "XMan_Hoi_Mau");*/
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Hoi_Sinh.wav", "XMan_Hoi_Sinh");
	//Sound::getInstance()->play("XMan_Hoi_Sinh", false, 1);
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Luot.wav", "XMan_Luot");
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Nhay.wav", "XMan_Nhay");
	Sound::getInstance()->loadSound("Resources/Sound/XMan_Tiep_Dat.wav", "XMan_Tiep_Dat");

	TaiDuLieu();

	//QuadTree_HieuUngMap = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));
	LoadHieuUngMap();

	for (int i = 0; i < ManGame::mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			const Vec2 lToaDoDoiTuong(
				lObject->GetX() + lObject->GetWidth() / 2.0f,
				lObject->GetY() + lObject->GetHeight() / 2.0f);

			if (lNhomObject->GetName() == "HieuUngMap1")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy
				HieuUngMap *lHieuUngMap = new HieuUngMap(lToaDoDoiTuong, mChieuRong, mChieuCao, HieuUngMap1, 1);
				DS_HieuUngMap1.push_back(lHieuUngMap);
		/*		QuadTree_HieuUngMap->ThemDoiTuong(lHieuUngMap);*/
			}
			else if (lNhomObject->GetName() == "HieuUngMap2")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy
				HieuUngMap *lHieuUngMap = new HieuUngMap(lToaDoDoiTuong, mChieuRong, mChieuCao, HieuUngMap2, 2);
				DS_HieuUngMap2.push_back(lHieuUngMap);
			}
		}
	}


}


Man1::~Man1()
{
	delete mXMan;
	delete mBanDoMap1;
}

void Man1::TaiDuLieu()
{
#pragma region HOAN THANH
	mGameDebugDraw = new GameDebugDraw();
	mGameDebugDraw->setLineSize(2.0f);

	ManGame::mMauNen = D3DCOLOR_XRGB(24, 40, 40);

#pragma region TAO BAN DO VA CAMERA
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("Map1.tmx");
	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();
	// TAO_CAMERA
	Camera::set_KichThuoc(ToanCauGame::mChieuRong, ToanCauGame::mChieuCao);
	Camera::CheckPoint = -1;
	//Camera::CheckPoint = 6;
	//Camera::CheckPoint = 10;
	//Camera::CheckPoint = 14;
	//Camera::CheckPoint = 16;
	Camera::set_ToaDo(Vec2(ToanCauGame::mChieuRong / 2.0f, 750.0f));
	//Camera::set_ToaDo(Vec2(7510.0f, 1750.0f)); // TEST
#pragma endregion

	// lấy hình ảnh bản đồ map
	// Chiếm 61.3MB RAM
	mBanDoMap1 = new HinhAnh("Map1.png");
	mBanDoMap1->set_ToaDo(Vec2(3968.0f, 1024.0f));

	// tạo cây quad tree
	mQuadTree_Tinh = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));
	mQuadTree_Dong = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));

	// tạo 1 XMan
	mXMan = new XMan(/*Vec2(7808.0f, 1750.0f)*//*Vec2(7510.0f, 1750.0f)*/Vec2(100.0f, 730.0f));

	// đưa đạn của XMan vào danh sách con trỏ
	mXMan->get_DS_Dan(mDS_DanLv);

	// tạo thanh máu XMan
	mThanhMauXMan = new ThanhMau(Vec2(15.0f, 90.0f));
	mThanhMauBoss = new ThanhMau(Vec2(239.0f, 90.0f), true);
	mItem = new Item();

#pragma region DONE
	// tạo DS Đạn Nổ để đưa cho các Quái sử dụng
	for (int i = 0; i < 6; i++)
	{
		DanNo1 *lD = new DanNo1();
		mDS_DanNo1_Quai.push_back(lD);
	}

	// tạo DS Bụi cho quái xài
	for (int i = 0; i < 2; i++)
	{
		Bui* lB = new Bui(Vec2(), Vec2());
		mDS_Bui_Quai.push_back(lB);
	}

	// tạo DS Tên Lửa cho quái xài
	for (int i = 0; i < 4; i++)
	{
		TenLua* lTL = new TenLua();
		mDS_TenLua_Quai.push_back(lTL);
	}


	// tạo 3 Cửa đánh boss
	DS_CuaDanhBoss[0] = new CuaDanhBoss(Vec2(2312.0f, 1176.0f));
	DS_CuaDanhBoss[1] = new CuaDanhBoss(Vec2(2552.0f, 1176.0f));
	DS_CuaDanhBoss[2] = new CuaDanhBoss(Vec2(5641.0f, 1176.0f));
	DS_CuaDanhBoss[3] = new CuaDanhBoss(Vec2(5879.0f, 1176.0f));
	DS_CuaDanhBoss[4] = new CuaDanhBoss(Vec2(7400.0f, 1944.0f), true);
	DS_CuaDanhBoss[5] = new CuaDanhBoss(Vec2(7688.0f, 1944.0f), true);
	mBOSS1 = new BOSS1(Vec2(2517.0f, 1155.0f + 23.0f), DS_CuaDanhBoss[1]);
	mBOSS2 = new BOSS2();
	mBOSS = new BOSS(Vec2(7872.0f, 1750.0f));

#pragma region TAO DS QUAI
	for (int i = 0; i < ManGame::mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			const Vec2 lToaDoDoiTuong(
				lObject->GetX() + lObject->GetWidth() / 2.0f,
				lObject->GetY() + lObject->GetHeight() / 2.0f);
			
			if (lNhomObject->GetName() == "Box1")
			{

				Box *lB = new Box(lToaDoDoiTuong, Vec2(), 1);

				mQuadTree_Tinh->ThemDoiTuong(lB);
			}
			else if (lNhomObject->GetName() == "Box2")
			{

				Box *lB = new Box(lToaDoDoiTuong, Vec2(), 2);

				mQuadTree_Dong->ThemDoiTuong(lB);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh4")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 4);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh2")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh2 = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 2);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh2);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh3")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh3 = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 3);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh3);
			}
			else if (lNhomObject->GetName() == "Gai")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -1);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh);
			}	
			else if (lNhomObject->GetName() == "Ech")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai, mItem,
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree_Dong->ThemDoiTuong(lEch);
			}	
			else if (lNhomObject->GetName() == "EchKhongNhay")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai, mItem, 
					lObject->GetWidth(), lObject->GetHeight(), true);

				mQuadTree_Dong->ThemDoiTuong(lEch);
			}	
			else if (lNhomObject->GetName() == "LoCot")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				LoCot *lLoCot = new LoCot(lToaDoDoiTuong, mDS_DanNo1_Quai, 
					mDS_TenLua_Quai, mDS_Bui_Quai, mItem);

				mQuadTree_Tinh->ThemDoiTuong(lLoCot);
			}
			else if (lNhomObject->GetName() == "ThangMay")
			{
				ThangMay *lThangMay =  new ThangMay(lToaDoDoiTuong);

				mQuadTree_Dong->ThemDoiTuong(lThangMay);
			}
			else if (lNhomObject->GetName() == "TrucXoay1")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 1);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay2")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 2);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay3")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 3);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay4")
			{
			TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
				lObject->GetWidth(), lObject->GetHeight(), 4);

			mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay5")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 5);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay6")
			{
			TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
				lObject->GetWidth(), lObject->GetHeight(), 6);

			mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay7")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 7);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay8")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 8);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay_1")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -1);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay_2")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -2);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "MayBay")
			{
				MayBay* lMayBay = new MayBay(lToaDoDoiTuong, mDS_TenLua_Quai, 
					mDS_Bui_Quai, mItem);

				mQuadTree_Dong->ThemDoiTuong(lMayBay);
			}
		}
	}
#pragma endregion



// TEST INFO
	font = NULL;
	D3DXCreateFont(ToanCauGame::mThietBi, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"Arial", &font);

	SetRect(&fRectangle, 0, 0, Camera::get_ChieuRong(), Camera::get_ChieuCao());

#pragma endregion

#pragma endregion
}


void Man1::CapNhat(float in_tg)
{
#pragma region HOAN THANH
	// khi trắng màn hình thì reset lại XMan
	if (Color == 255)
	{
	// CHECK_1
		if (Camera::CheckPoint < 6)
		{
		//	//set Camera trước khi set XMan
			Camera::CheckPoint = -1;
			Camera::set_ToaDo(Vec2(100.0f, 730.0f));
			mXMan->XuatHien(Vec2(100.0f, 730.0f));
			mBOSS1->BienMat();
			mBOSS2->BienMat();
		}
	// CHECK_2
		else if (Camera::CheckPoint >= 6 &&
			Camera::CheckPoint < 10)
		{
			//set Camera trước khi set XMan
			Camera::CheckPoint = 6;
			Camera::set_ToaDo(Vec2(2960.0f, 1000.0f));
			mXMan->XuatHien(Vec2(2960.0f, 1000.0f));
			mBOSS1->BienMat();
			mBOSS2->BienMat();
		}
		else if (Camera::CheckPoint >= 10 &&
			Camera::CheckPoint < 14)
		{
			Camera::CheckPoint = 9;
			Camera::set_ToaDo(Vec2(5275.0f, 1000.0f));
			mXMan->XuatHien(Vec2(5275.0f, 1000.0f));
			mBOSS1->BienMat();
			mBOSS2->BienMat();
		}
		else if (Camera::CheckPoint >= 14 &&
			Camera::CheckPoint < 16)
		{
			Camera::CheckPoint = 14;
			Camera::set_ToaDo(Vec2(6325.0f, 1775.0f));
			mXMan->XuatHien(Vec2(6325.0f, 1775.0f));
			mBOSS1->BienMat();
			mBOSS2->BienMat();
		}
		else if (Camera::CheckPoint >= 16 &&
			Camera::CheckPoint <= 18)
		{
			Camera::CheckPoint = 16;
			Camera::set_ToaDo(Vec2(7515.0f, 1750.0f));
			mXMan->XuatHien(Vec2(7515.0f, 1750.0f));
			mBOSS1->BienMat();
			mBOSS2->BienMat();
			mBOSS->BienMat();
			Sound::getInstance()->stop("Nhac_Danh_Boss");
			Sound::getInstance()->play("Nhac_Nen", true, 0);
		}
		//else if (Camera::CheckPoint >= 18)
		//{
		//	Camera::CheckPoint = 18;
		//	Camera::set_ToaDo(Vec2(7808.0f, 1750.0f));
		//	mXMan->XuatHien(Vec2(7808.0f, 1750.0f));
		//	mBOSS1->BienMat();
		//	mBOSS2->BienMat();
		//}
	}

	mDS_DoiTuong_Tinh.clear();
	mQuadTree_Tinh->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong_Tinh, Camera::get_HCNGioiHan());

	mDS_DoiTuong_Dong.clear();
	mQuadTree_Dong->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong_Dong, Camera::get_HCNGioiHan_MoRong());

#pragma region CAP NHAT
	DS_CuaDanhBoss[0]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[1]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[2]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[3]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[4]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[5]->CapNhat(in_tg, mXMan);
	mBOSS1->CapNhat(in_tg, mXMan);
	mBOSS2->CapNhat(in_tg, mXMan);
	mItem->CapNhat(in_tg, mXMan);

	mXMan->CapNhat(in_tg);
	mBOSS->CapNhat(in_tg, mXMan);
	mBOSS->get_OngCon0()->CapNhat(in_tg, mXMan);
	mBOSS->get_OngCon1()->CapNhat(in_tg, mXMan);
	mBOSS->get_OngCon2()->CapNhat(in_tg, mXMan);
	mBOSS->get_OngCon3()->CapNhat(in_tg, mXMan);
	mBOSS->get_OngCon4()->CapNhat(in_tg, mXMan);
	mBOSS->get_HongTam()->CapNhat(in_tg, mXMan);

	for (auto DanLv : mDS_DanLv)
	{
		DanLv->CapNhat(in_tg);
	}


	for (auto DanNo : mDS_DanNo1_Quai)
	{
		DanNo->CapNhat(in_tg);
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		TenLua->CapNhat(in_tg, mXMan);
	}

	for (auto Bui : mDS_Bui_Quai)
	{
		Bui->CapNhat(in_tg);
	}

	for (auto DT1 : mDS_DoiTuong_Tinh)
	{
		DT1->CapNhat(in_tg, mXMan);
	}

	for (auto DT2 : mDS_DoiTuong_Dong)
	{
		DT2->CapNhat(in_tg, mXMan);
	}



#pragma endregion

#pragma region VA CHAM
	DS_CuaDanhBoss[0]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[1]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[2]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[3]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[4]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[5]->XuLyVaCham(mXMan);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[0]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[1]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[2]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[3]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[4]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[5]);
	mXMan->XuLyVaCham(mBOSS1);
	mXMan->XuLyVaCham(mItem);
	mItem->XuLyVaCham(mXMan);
	mXMan->XuLyVaCham(mBOSS);
	mBOSS->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon0()->XuLyVaCham(mXMan);
	mBOSS->get_OngCon1()->XuLyVaCham(mXMan);
	mBOSS->get_OngCon2()->XuLyVaCham(mXMan);
	mBOSS->get_OngCon3()->XuLyVaCham(mXMan);
	mBOSS->get_OngCon4()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon0()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon1()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon2()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon3()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mBOSS->get_OngCon4()->XuLyVaCham(DS_CuaDanhBoss[5]);
	mXMan->XuLyVaCham(mBOSS->get_OngCon0());
	mXMan->XuLyVaCham(mBOSS->get_OngCon1());
	mXMan->XuLyVaCham(mBOSS->get_OngCon2());
	mXMan->XuLyVaCham(mBOSS->get_OngCon3());
	mXMan->XuLyVaCham(mBOSS->get_OngCon4());
	mBOSS->get_HongTam()->XuLyVaCham(mXMan);

	if (mBOSS2->get_TrangThai() == eTT_BOSS2_BocVac)
	{
		mXMan->XuLyVaCham(mBOSS2->get_Box0());
		mXMan->XuLyVaCham(mBOSS2->get_Box1());
		mXMan->XuLyVaCham(mBOSS2->get_DanSang());
	}

	for (auto DanLv : mDS_DanLv)
	{
		mBOSS->XuLyVaCham(DanLv);
		DanLv->XuLyVaCham(mBOSS);

		mBOSS->get_OngCon0()->XuLyVaCham(DanLv);
		mBOSS->get_OngCon1()->XuLyVaCham(DanLv);
		mBOSS->get_OngCon2()->XuLyVaCham(DanLv);
		mBOSS->get_OngCon3()->XuLyVaCham(DanLv);
		mBOSS->get_OngCon4()->XuLyVaCham(DanLv);
		DanLv->XuLyVaCham(mBOSS->get_OngCon0());
		DanLv->XuLyVaCham(mBOSS->get_OngCon1());
		DanLv->XuLyVaCham(mBOSS->get_OngCon2());
		DanLv->XuLyVaCham(mBOSS->get_OngCon3());
		DanLv->XuLyVaCham(mBOSS->get_OngCon4());

		mBOSS1->XuLyVaCham(DanLv);
		DanLv->XuLyVaCham(mBOSS1);

		if (mBOSS2->get_TrangThai() == eTT_BOSS2_BocVac)
		{
			mBOSS2->get_Box0()->XuLyVaCham(DanLv);
			mBOSS2->get_Box1()->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(mBOSS2->get_Box0());
			DanLv->XuLyVaCham(mBOSS2->get_Box1());
			DanLv->XuLyVaCham(mBOSS2->get_Pet2());
		}
	}

	for (auto DanNo : mDS_DanNo1_Quai)
	{
		if (DanNo->get_TrangThai() != eTT_DanNo1_BienMat)
		{
			mXMan->XuLyVaCham(DanNo);
		}
		DanNo->XuLyVaCham(mXMan);

		for (auto DanLv : mDS_DanLv)
		{
			DanNo->XuLyVaCham(DanLv);
		}
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		mXMan->XuLyVaCham(TenLua);
		TenLua->XuLyVaCham(mXMan);

		for (auto DanLv : mDS_DanLv)
		{
			TenLua->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(TenLua);
		}
	}

	for (auto DT : mDS_DoiTuong_Tinh)
	{
		mItem->XuLyVaCham(DT);
		mXMan->XuLyVaCham(DT);
		mBOSS->XuLyVaCham(DT);
		mBOSS->get_OngCon0()->XuLyVaCham(DT);
		mBOSS->get_OngCon1()->XuLyVaCham(DT);
		mBOSS->get_OngCon2()->XuLyVaCham(DT);
		mBOSS->get_OngCon3()->XuLyVaCham(DT);
		mBOSS->get_OngCon4()->XuLyVaCham(DT);

		for (auto DT2 : mDS_DoiTuong_Dong)
		{
			DT2->XuLyVaCham(DT);
		}

		for (auto DanLv : mDS_DanLv)
		{
			DT->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(DT);
		}

		for (auto DanNo : mDS_DanNo1_Quai)
		{
			DanNo->XuLyVaCham(DT);
		}

		for (auto TenLua : mDS_TenLua_Quai)
		{
			TenLua->XuLyVaCham(DT);
		}
	}

	for (auto DT : mDS_DoiTuong_Dong)
	{
		mXMan->XuLyVaCham(DT);

		for (auto DanLv : mDS_DanLv)
		{
			DT->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(DT);
		}
	}
#pragma endregion

	Camera::set_ToaDo(mXMan->get_ToaDo());

	// nơi xử lý bàn phím
	mXMan->XuLyBanPhim(mKeys);
#pragma endregion

	HieuUngMap1->CapNhat(in_tg);
}

void Man1::Ve()
{
	// lấy độ dời từ Camera
	Vec2 lDoDoi(ToanCauGame::mChieuRong / 2 - Camera::get_ToaDo().x,
		ToanCauGame::mChieuCao / 2 - Camera::get_ToaDo().y);


	//DS_HieuUngMap.clear();
	//QuadTree_HieuUngMap->get_CacDoiTuongCoTheVaCham(DS_HieuUngMap, Camera::get_HCNGioiHan());

	//for (auto HU : DS_HieuUngMap)
	//{
	//	HU->Ve(lDoDoi);
	//}

	for (auto A : DS_HieuUngMap1)
	{
		A->Ve(lDoDoi);
	}
	for (auto A : DS_HieuUngMap2)
	{
		A->Ve(lDoDoi);
	}
	// vẽ hình ảnh bản đồ
	mBanDoMap1->set_DoDoi(lDoDoi);
	mBanDoMap1->Ve();



#pragma region HOAN THANH
	DS_CuaDanhBoss[0]->Ve(lDoDoi);
	DS_CuaDanhBoss[1]->Ve(lDoDoi);
	DS_CuaDanhBoss[2]->Ve(lDoDoi);
	DS_CuaDanhBoss[3]->Ve(lDoDoi);
	DS_CuaDanhBoss[4]->Ve(lDoDoi);
	DS_CuaDanhBoss[5]->Ve(lDoDoi);
	mBOSS1->Ve(lDoDoi);
	mBOSS2->Ve(lDoDoi);
	mItem->Ve(lDoDoi);

	mBOSS->Ve(lDoDoi);
	mBOSS->get_OngCon0()->Ve(lDoDoi);
	mBOSS->get_OngCon1()->Ve(lDoDoi);
	mBOSS->get_OngCon2()->Ve(lDoDoi);
	mBOSS->get_OngCon3()->Ve(lDoDoi);
	mBOSS->get_OngCon4()->Ve(lDoDoi);

	mXMan->Ve(lDoDoi);
	mBOSS->get_HongTam()->Ve(lDoDoi);



	for (auto DT : mDS_DoiTuong_Tinh)
	{
		DT->Ve(lDoDoi);
	}

	for (auto DT : mDS_DoiTuong_Dong)
	{
		DT->Ve(lDoDoi);
	}

	for (auto DanLv : mDS_DanLv)
	{
		DanLv->Ve(lDoDoi);
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		TenLua->Ve(lDoDoi);
	}




	for (auto D : mDS_DanNo1_Quai)
	{
		D->Ve(lDoDoi);
	}

	for (auto Bui : mDS_Bui_Quai)
	{
		Bui->Ve(lDoDoi);
	}

	mThanhMauXMan->Ve(mXMan->get_HP());
	if (mBOSS->get_TrangThai() != eTT_BOSS_BienMat)
	{
		mThanhMauBoss->Ve(mBOSS->get_HP());
	}
	// tô màu trắng trước khi Reset game
	if (mXMan->get_TrangThai() == eTT_XMan_PhatNo)
	{
		Color += 3;
		if (Color > 255)
		{
			Color = 255;
		}

	}
	else if (Color != 0)
	{
		Color -= 15;
		if (Color < 0)
		{
			Color = 0;
		}
	}
	DS_HinhAnh::get_TH()->Rong_png->set_ToaDo(Vec2(ToanCauGame::mChieuRong / 2.0f,
		ToanCauGame::mChieuCao / 2.0f));
	DS_HinhAnh::get_TH()->Rong_png->Ve(D3DCOLOR_ARGB(Color, 255, 255, 255));
#pragma endregion
}

void Man1::OnKeyDown(int in_KeyCode)
{
	mKeys[in_KeyCode] = true;
}

void Man1::OnKeyUp(int in_KeyCode)
{
	mKeys[in_KeyCode] = false;
}

void Man1::DrawQuadTree(QuadTree * in_QuadTree)
{
	//mGameDebugDraw->DrawRect(in_QuadTree->get_RECT());

	//if (in_QuadTree->get_Nodes())
	//{
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		DrawQuadTree(in_QuadTree->get_Nodes()[i]);
	//	}
	//}



	//if (in_QuadTree->get_Nodes())
	//{
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		mGameDebugDraw->DrawRect(in_QuadTree->get_Nodes()[i]->get_RECT());
	//	}
	//}
}

void Man1::DrawCollidable()
{
	//for (auto child : mDS_DoiTuong_Tinh)
	//{
	//	mGameDebugDraw->DrawRect(child->get_RECT());
	//}

	//for (auto child : mDS_DoiTuong_Dong)
	//{
	//	mGameDebugDraw->DrawRect(child->get_RECT());
	//}
	//mGameDebugDraw->DrawRect(mXMan->get_RECT());

	//for (int i = 0; i < (int)mDS_Ech.size(); i++)
	//{
	//	mGameDebugDraw->DrawRect(mDS_Ech[i]->get_RECT());
	//}

	//for (int i = 0; i < (int)mDS_DanLv.size(); i++)
	//{
	//	mGameDebugDraw->DrawRect(mDS_DanLv[i]->get_RECT());
	//}

	//mGameDebugDraw->DrawRect(mDanNo1->get_RECT());

	//mGameDebugDraw->DrawRect(mXacUop->get_RECT());
	//for (auto DoiTuong : mDS_DoiTuong)
	//{
	//	mGameDebugDraw->DrawRect(DoiTuong->get_RECT());
	//}
	//mGameDebugDraw->DrawRect(mBOSS->get_RECT());
	//RECT a; 
	//a.left = (int)mBOSS->get_ToaDo().x;
	//a.right = (int)mBOSS->get_ToaDo().x + 1;
	//a.top = (int)mBOSS->get_ToaDo().y;
	//a.bottom = (int)mBOSS->get_ToaDo().y + 1;
	//mGameDebugDraw->DrawRect(a);
	//mGameDebugDraw->DrawRect(mBOSS->get_OngCon0()->get_RECT());
	//mGameDebugDraw->DrawRect(mBOSS->get_OngCon1()->get_RECT());
	//mGameDebugDraw->DrawRect(mBOSS->get_OngCon2()->get_RECT());
	//mGameDebugDraw->DrawRect(mBOSS->get_OngCon3()->get_RECT());
	//mGameDebugDraw->DrawRect(mBOSS->get_OngCon4()->get_RECT());
}

void Man1::LoadHieuUngMap()
{
	std::vector <ThongTinFrame> lDSTTFrame;

	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 0, 256),             0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 258, 514),           0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 516, 772),           0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 774, 1030),          0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 1032, 1288),         0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 1290, 1546),         0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 1548, 1804),         0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(0, 512, 1806, 2062),         0.3f));
	lDSTTFrame.push_back(ThongTinFrame(512, 256, HCN(512, 512 + 512, 1806, 2062), 0.3f));
	HieuUngMap1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(512, 352, HCN(0, 512, 0, 352)));
	HieuUngMap2 = new HoatHinh(lDSTTFrame);
}
