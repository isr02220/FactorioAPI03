#include "framework.h"
#include "Player.h"
#include "Entity.h"
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
    info.position.x = FLOAT(WINCX >> 1);
    info.position.y = FLOAT(WINCY >> 1);
    info.iCX = 92;
    info.iCY = 116;
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

    if (CKeyManager::GetInstance()->Press(KEY::Inventory)) {
        list<CObj*>* listEntity = CObjManager::GetInstance()->GetList(OBJ::ENTITY);
        for (auto entity : *listEntity) {
            dynamic_cast<CEntity*>(entity)->SetSpriteIndexX(0);
        }
    }
    return STATE_NO_EVENT;
}

void CPlayer::LateUpdate_Object() {
}

void CPlayer::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
        INT spriteFrameDelay = 4;
        HDC hMemDC;
        if (walkingState.walking) {
            info.iCX = 88;
            info.iCY = 132;
            spriteFrameDelay = 2;
            hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_running");

            //TCHAR szBuffer[64];
            //wsprintf(szBuffer, L"Player 위치 : %d, %d", info.position.x, info.position.y);
            //MessageBox(g_hWnd, szBuffer, L" ", MB_OK);
            //wsprintf(szBuffer, L"스크롤 위치 : %d, %d", CScrollManager::GetInstance()->GetScrollX(), CScrollManager::GetInstance()->GetScrollY());
            //MessageBox(g_hWnd, szBuffer, L" ", MB_OK);
        }
        else {
            info.iCX = 92;
            info.iCY = 116;
            spriteFrameDelay = 4;
            hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_idle");
        }

        if (++spriteIndexX >= 22 * spriteFrameDelay) spriteIndexX = 0;

        if (nullptr == hMemDC)
            return;
        INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
        INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();
        GdiTransparentBlt(hDC,
            rect.left + iScrollX,
            rect.top  + iScrollY,
            info.iCX,
            info.iCY,
            hMemDC,
            spriteIndexX / spriteFrameDelay * info.iCX,
            spriteIndexY * info.iCY,
            info.iCX,
            info.iCY,
            RGB(255, 0, 255));

        //HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
        //HBRUSH hBrush = CreateSolidBrush(fillColor);

        //HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
        //HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

        //Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

        //SelectObject(hDC, oldPen);
        //SelectObject(hDC, oldBrush);
        //DeleteObject(hPen);
        //DeleteObject(hBrush);
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

    if (keyMgr->Press(KEY::MoveLeft))
        moveForce += FORCE(-1.f, 0.f);
    if (keyMgr->Press(KEY::MoveRight))
        moveForce += FORCE(1.f, 0.f);
    if (keyMgr->Press(KEY::MoveUp))
        moveForce += FORCE(0.f, -1.f);
    if (keyMgr->Press(KEY::MoveDown))
        moveForce += FORCE( 0.f,  1.f);
    
    FLOAT nomalizer = sqrtf(((fabsf(moveForce.x) * fabsf(moveForce.x)) + (fabsf(moveForce.y) * fabsf(moveForce.y))));
    if (nomalizer) moveForce /= nomalizer;

    if (moveForce.x == 0.f && moveForce.y == 0.f) {
        walkingState.walking = false;
    }
    else {
        walkingState.walking = true;
        if (moveForce.x >= 1.f)
            walkingState.direction = DIRECTION::DIR::EAST;
        else if (moveForce.x <= -1.f)
            walkingState.direction = DIRECTION::DIR::WEST;
        else if (moveForce.y >= 1.f)
            walkingState.direction = DIRECTION::DIR::SOUTH;
        else if (moveForce.y <= -1.f)
            walkingState.direction = DIRECTION::DIR::NORTH;
        else if (moveForce.x > 0.f && moveForce.y > 0.f)
            walkingState.direction = DIRECTION::DIR::SOUTHEAST;
        else if (moveForce.x > 0.f && moveForce.y < 0.f)
            walkingState.direction = DIRECTION::DIR::NORTHEAST;
        else if (moveForce.x < 0.f && moveForce.y > 0.f)
            walkingState.direction = DIRECTION::DIR::SOUTHWEST;
        else if (moveForce.x < 0.f && moveForce.y < 0.f)
            walkingState.direction = DIRECTION::DIR::NORTHWEST;
        spriteIndexY = (INT)walkingState.direction;
    }
    //CScrollManager::GetInstance()->SetScroll(moveForce * speed * -1.f);
    CScrollManager::GetInstance()->SetScroll((info.position * -1.f) + POSITION(WINCX >> 1, WINCY >> 1));
    info.force = moveForce;
}
