#include "Bullet.h"
#include "Player.h"
//#include "Monster.h"

CBullet::CBullet() : CObj(){
	objectType = OBJ::BULLET;
	info.iCX = 20;
	info.iCY = 20;
	info.CCX = 20;
	info.CCY = 20;
	speed = 10.f;
	timer = GetTickCount();
}

CBullet::CBullet(float _degree, float _speed, INT _damage, LONG _bulletSize)
	: CObj()
	, speed(_speed)
	, m_damage(_damage)
{
	objectType = OBJ::BULLET;
	info.iCX = 20;
	info.iCY = 20;
	info.CCX = 20;
	info.CCY = 20;
	info.force = FORCE(cosf(_degree / 180 * pi), sinf(_degree / 180 * pi));
	timer = GetTickCount();
}

CBullet::~CBullet() {

}

void CBullet::Ready_Object() {
}

int CBullet::Update_Object() {
	info.position += (info.force * speed);
	CObj::Update_Rect_Object();
	if (dead)
		return STATE_DEAD;

	if (timer + 1500 < GetTickCount())
		SetDead();

	return STATE_NO_EVENT;
}

void CBullet::LateUpdate_Object() {
}

void CBullet::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {

		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"bullet");

		if (nullptr == hMemDC)
			return;

		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			0,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}
}

void CBullet::Release_Object() {
}

void CBullet::OnCollision(CObj* _TargetObj) {
	SetDead();
}
