#include "Player.h"
#include "KeyManager.h"
CPlayer::CPlayer() : CActor() {
    objectType = OBJ::PLAYER;
}

CPlayer::CPlayer(FLOAT _positionX, FLOAT _positionY) : CActor(_positionX, _positionY) {
    objectType = OBJ::PLAYER;
}

CPlayer::~CPlayer() {
    Release_Object();
}

void CPlayer::Ready_Object() {
    info.position.x = 200.f;
    info.position.y = 700.f;
    info.iCX = 60;
    info.iCY = 100;
    speed = 7.f;
    info.force.x = 0.f;
    info.force.y = 0.f;
	MaxHP = 200;
    HP = MaxHP;
}

int CPlayer::Update_Object() {
    //m_tInfo.position.y += m_fSpeed * forceY;
    info.position += (info.force * speed);
    CObj::Update_Rect_Object();
    Move();
    return STATE_NO_EVENT;
}

void CPlayer::LateUpdate_Object() {
}

void CPlayer::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
		COLORREF bColor = RGB(250, 128, 64);	// 브러쉬 색
		HBRUSH hBrush = CreateSolidBrush(bColor);
		HBRUSH  oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		
        Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

    }

}

void CPlayer::Release_Object() {

}

void CPlayer::OnCollision(CObj* _TargetObj) {

}

void CPlayer::Move() {
    CKeyManager* keyMgr = CKeyManager::GetInstance();
    keyMgr->UpdateKeyManager();
    FORCE moveForce = FORCE(0.f, 0.f);

    if (keyMgr->KeyDown(KEY::MoveLeft))
        moveForce += FORCE(-1.f, 0.f);
    if (keyMgr->KeyDown(KEY::MoveRight))
        moveForce += FORCE(1.f, 0.f);
    if (keyMgr->KeyDown(KEY::MoveUp))
        moveForce += FORCE(0.f, -1.f);
    if (keyMgr->KeyDown(KEY::MoveDown))
        moveForce += FORCE( 0.f,  1.f);
    
    FLOAT nomalizer = sqrtf(((fabsf(moveForce.x) * fabsf(moveForce.x)) + (fabsf(moveForce.y) * fabsf(moveForce.y))));
    if (nomalizer) moveForce /= nomalizer;

    info.force = moveForce;
}
