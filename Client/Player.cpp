#include "framework.h"
#include "Mouse.h"
#include "Player.h"
#include "Entity.h"
#include "ResourceOre.h"
#include "TransportBelt.h"
#include "UI.h"
#include "InventoryUI.h"
#include "QuickSlotUI.h"
#include "ProgressBar.h"
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
    info.position.x = FLOAT(GRIDCX * (GRIDX >> 1));
    info.position.y = FLOAT(GRIDCY * (GRIDY >> 1));
    CObj* tempUi = CAbstractFactory<CInventoryUI>::Create(WINCX >> 2, WINCY >> 1);
    CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
    inventoryUI = dynamic_cast<CUI*>(tempUi);

    tempUi = CAbstractFactory<CQuickSlotUI>::Create(WINCX >> 1, WINCY - 48);
    tempUi->SetVisible(true);
    QuickSlotUI = dynamic_cast<CUI*>(tempUi);
    CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);

    tempUi = CAbstractFactory<CProgressBar>::Create(WINCX >> 1, WINCY - 108);
    tempUi->SetVisible(false);
    ProgressBarUI = dynamic_cast<CUI*>(tempUi);
    CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);

    playerMouse = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front());
    info.iCX = 64;
    info.iCY = 64;
    info.CCX = 92;
    info.CCY = 116;
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
    if (g_hWnd == GetForegroundWindow()) {

        Move();

        if(ProgressBarUI != nullptr) ProgressBarUI->SetVisible(false);
        miningState.mining = false;

        if (CKeyManager::GetInstance()->OnPress(KEY::Inventory))
            inventoryUI->SetVisible(!inventoryUI->GetVisible());
                
        if (CKeyManager::GetInstance()->Press(KEY::PrimaryAction) && selectedUI == nullptr) PlaceEntity();

        if (CKeyManager::GetInstance()->Press(KEY::SecondaryAction) && selectedUI == nullptr) SecondaryAction();
        else if (ProgressBarUI != nullptr) dynamic_cast<CProgressBar*>(ProgressBarUI)->ResetProgress();

        if (CKeyManager::GetInstance()->OnPress(KEY::Rotate) && selectedUI == nullptr) {
            if (selectedActor) RotateEntity();
            else               RotateCursor();
        }
    }
    return STATE_NO_EVENT;
}

void CPlayer::LateUpdate_Object() {
}

void CPlayer::Render_Object(HDC hDC) {
    if (isVisible) {
        spriteFrameDelay = 4;
        HDC hMemDC;
        if (miningState.mining) {
            info.CCX = 196;
            info.CCY = 194;
            spriteFrameDelay = 1;
            hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_mining_tool");
        }
        else if (walkingState.walking) {
            info.CCX = 88;
            info.CCY = 132;
            spriteFrameDelay = 2;
            hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_running");
        }
        else {
            info.CCX = 92;
            info.CCY = 116;
            spriteFrameDelay = 4;
            hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_idle");
        }
        CObj::Update_Rect_Object();
        spriteIndexY = (INT)walkingState.direction;

        if (nullptr == hMemDC)
            return;
        INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
        INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();
        GdiTransparentBlt(hDC,
            cRect.left + iScrollX,
            cRect.top  + iScrollY,
            info.CCX,
            info.CCY,
            hMemDC,
            (spriteIndexX / spriteFrameDelay) * info.CCX,
            spriteIndexY * info.CCY,
            info.CCX,
            info.CCY,
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
    }
    //CScrollManager::GetInstance()->SetScroll(moveForce * speed * -1.f);
    if (++spriteIndexX >= 22 * spriteFrameDelay) spriteIndexX = 0;

    CScrollManager::GetInstance()->SetScroll((info.position * -1.f) + POSITION(WINCX >> 1, WINCY >> 1));
    info.force = moveForce;
}

void CPlayer::SecondaryAction() {
    if (selectedActor) {

        switch (selectedActor->GetObjectType()) {
        case OBJ::RESOURCEORE:
            GatherResource();
            break;
        case OBJ::BELT:
            UnPlaceEntity();
            break;
        case OBJ::BELTEND:
            break;
        case OBJ::ENTITY:
            UnPlaceEntity();
            break;
        case OBJ::PLAYER:
            break;
        case OBJ::ITEM:
            break;
        case OBJ::MONSTER:
            break;
        case OBJ::UI:
            break;
        case OBJ::MOUSE:
            break;
        case OBJ::END:
            break;
        default:
            break;
        }
    }
}

void CPlayer::PlaceEntity() { 
    if (selectedActor == nullptr || selectedActor->GetObjectType() != OBJ::BELT || !lstrcmp(selectedActor->GetName(), L"TransportBelt") && selectedActor->GetWalkingState().direction != playerMouse->cursorDir) {
        POSITION tPos = playerMouse->GetPosition();
        CObj* tempObj = CAbstractFactory<CTransportBelt>::Create(ToGridPos(tPos, 64));
        dynamic_cast<CEntity*>(tempObj)->SetWalkingState(playerMouse->cursorDir);
        CObjManager::GetInstance()->InsertObject(tempObj, OBJ::BELT);
    }
}

void CPlayer::UnPlaceEntity() {
    ProgressBarUI->SetVisible(true);
    if (dynamic_cast<CProgressBar*>(ProgressBarUI)->IncreaseProgress(0.05f)) {
        selectedActor->SetDead();
    }
    
}

void CPlayer::GatherResource() {
    ProgressBarUI->SetVisible(true);
    miningState.mining = true;
    FLOAT dx = selectedActor->GetPosition().x - info.position.x;
    FLOAT dy = selectedActor->GetPosition().y - info.position.y;
    FLOAT rad = atan2f(dy, dx);
    if (rad < 0) rad += 2.f * pi;

    if (rad > 0 && rad <= pi / 8.f) 
        walkingState.direction = DIRECTION::DIR::EAST;
    else if (rad > pi / 8.f && rad <= pi / 8.f * 3.f)
        walkingState.direction = DIRECTION::DIR::SOUTHEAST;
    else if (rad > pi / 8.f * 3.f && rad <= pi / 8.f * 5.f)
        walkingState.direction = DIRECTION::DIR::SOUTH;
    else if (rad > pi / 8.f * 5.f && rad <= pi / 8.f * 7.f)
        walkingState.direction = DIRECTION::DIR::SOUTHWEST;
    else if (rad > pi / 8.f * 7.f && rad <= pi / 8.f * 9.f)
        walkingState.direction = DIRECTION::DIR::WEST;
    else if (rad > pi / 8.f * 9.f && rad <= pi / 8.f * 11.f)
        walkingState.direction = DIRECTION::DIR::NORTHWEST;
    else if (rad > pi / 8.f * 11.f && rad <= pi / 8.f * 13.f)
        walkingState.direction = DIRECTION::DIR::NORTH;
    else if (rad > pi / 8.f * 13.f && rad <= pi / 8.f * 15.f)
        walkingState.direction = DIRECTION::DIR::NORTHEAST;
    else
        walkingState.direction = DIRECTION::DIR::EAST;

    if (dynamic_cast<CProgressBar*>(ProgressBarUI)->IncreaseProgress(1.f / 110.f )) {
        miningState.mining = false;
        dynamic_cast<CResourceOre*>(selectedActor)->Gather();
        spriteIndexX = 0;
    }
}

void CPlayer::RotateEntity() {
    WALKINGSTATE tWalkingStat = selectedActor->GetWalkingState();
    switch (tWalkingStat.direction) {
    case DIRECTION::DIR::NORTH:
        tWalkingStat.direction = DIRECTION::DIR::EAST;
        break;
    case DIRECTION::DIR::EAST:
        tWalkingStat.direction = DIRECTION::DIR::SOUTH;
        break;
    case DIRECTION::DIR::SOUTH:
        tWalkingStat.direction = DIRECTION::DIR::WEST;
        break;
    case DIRECTION::DIR::WEST:
        tWalkingStat.direction = DIRECTION::DIR::NORTH;
        break;
    default:
        tWalkingStat.direction = DIRECTION::DIR::NORTH;
        break;
    }
    selectedActor->SetWalkingState(tWalkingStat);
}

void CPlayer::RotateCursor() {
    switch (playerMouse->cursorDir) {
    case DIRECTION::DIR::NORTH:
        playerMouse->cursorDir = DIRECTION::DIR::EAST;
        break;
    case DIRECTION::DIR::EAST:
        playerMouse->cursorDir = DIRECTION::DIR::SOUTH;
        break;
    case DIRECTION::DIR::SOUTH:
        playerMouse->cursorDir = DIRECTION::DIR::WEST;
        break;
    case DIRECTION::DIR::WEST:
        playerMouse->cursorDir = DIRECTION::DIR::NORTH;
        break;
    default:
        playerMouse->cursorDir = DIRECTION::DIR::NORTH;
        break;
    }
}

void CPlayer::UpdateSelectedUI(CUI* _targetUI) {
        selectedUI = _targetUI;
}
