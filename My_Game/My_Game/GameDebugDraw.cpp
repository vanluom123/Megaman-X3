#include "GameDebugDraw.h"
#include "ToanCauGame.h"

GameDebugDraw::GameDebugDraw()
{
	mSpriteHandler = ToanCauGame::mXuLyHinhAnh;
	mSpriteHandler->GetDevice(&mddv);
	D3DXCreateLine(mddv, &LineDraw);

	//set size cho line
	LineDraw->SetWidth(5);

	//set mau cho line
	mColor = D3DCOLOR_XRGB(255, 0, 0);

}

GameDebugDraw::~GameDebugDraw()
{

}

void GameDebugDraw::Draw()
{

}

void GameDebugDraw::setLineSize(float width)
{
	LineDraw->SetWidth(width);
}

void GameDebugDraw::DrawLine(D3DXVECTOR2 lines[], int count)
{
	LineDraw->Begin();
	LineDraw->Draw(lines, count, mColor);
	LineDraw->End();
}

void GameDebugDraw::DrawRect(RECT rect)
{

	D3DXVECTOR3 trans = D3DXVECTOR3(0, 0, 0);

	trans = D3DXVECTOR3(ToanCauGame::mChieuRong / 2.0f, ToanCauGame::mChieuCao / 2.0f, 0) -D3DXVECTOR3(Camera::get_ToaDo().x, Camera::get_ToaDo().y, 0.0f);

	D3DXVECTOR2 lines[] = { D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y) };

	DrawLine(lines, 5);
}

void GameDebugDraw::setColor(D3DCOLOR color)
{
	mColor = color;
}