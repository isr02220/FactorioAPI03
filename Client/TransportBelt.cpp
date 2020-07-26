#include "TransportBelt.h"
#include "ItemTransportBelt.h"
#include "Item.h"
#include "Entity.h"
INT CTransportBelt::beltSpriteIndexX = 0;
INT CTransportBelt::beltSpriteFrameDelay = 1;

CTransportBelt::CTransportBelt() : CEntity() {
    objectType = OBJ::BELT;
	SetName(L"TransportBelt");
}

CTransportBelt::~CTransportBelt() {
    Release_Object();
}

void CTransportBelt::Ready_Object() {
    info.iCX = 64;
    info.iCY = 64;
    info.CCX = 72;
    info.CCY = 74;
    speed = 3.f;
    MaxHP = 10;
    HP = MaxHP;
}

INT CTransportBelt::Update_Object() {
    info.position += (info.force * speed);

    CObj::Update_Rect_Object();
    if (dead) {
        return STATE_DEAD;
    }
	GetBeltConnect();
	TransportItem();
    return STATE_NO_EVENT;
}

void CTransportBelt::LateUpdate_Object() {

}

void CTransportBelt::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
        HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt");
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
            beltSpriteIndexX / beltSpriteFrameDelay * info.CCX,
            spriteIndexY * info.CCY,
            info.CCX,
            info.CCY,
            RGB(255, 0, 255));

        if (tailBelt == nullptr) {
            GdiTransparentBlt(hDC,
                cRect.left + iScrollX - HeadTailDistX,
                cRect.top + iScrollY - HeadTailDistY,
                info.CCX,
                info.CCY,
                hMemDC,
                beltSpriteIndexX / beltSpriteFrameDelay * info.CCX,
                tailSpriteIndex * info.CCY,
                info.CCX,
                info.CCY,
                RGB(255, 0, 255));
        }
    }

}

void CTransportBelt::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if(placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt-unplacable");
		if (nullptr == hMemDC)
			return;
		switch (walkingState.direction) {
		case DIRECTION::DIR::NORTH:
			tailSpriteIndex = 12;
			headSpriteIndex = 17;
			HeadTailDistX = 0;
			HeadTailDistY = -64;
			spriteIndexY = 2;
			break;
		case DIRECTION::DIR::EAST:
			tailSpriteIndex = 14;
			headSpriteIndex = 19;
			HeadTailDistX = 64;
			HeadTailDistY = 0;
			spriteIndexY = 0;
			break;
		case DIRECTION::DIR::SOUTH:
			tailSpriteIndex = 16;
			headSpriteIndex = 13;
			HeadTailDistX = 0;
			HeadTailDistY = 64;
			spriteIndexY = 3;
			break;
		case DIRECTION::DIR::WEST:
			tailSpriteIndex = 18;
			headSpriteIndex = 15;
			HeadTailDistX = -64;
			HeadTailDistY = 0;
			spriteIndexY = 1;
			break;
		default:
			tailSpriteIndex = 12;
			headSpriteIndex = 17;
			HeadTailDistX = 0;
			HeadTailDistY = -64;
			spriteIndexY = 2;
			break;
		}
		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			beltSpriteIndexX / beltSpriteFrameDelay * info.CCX,
			spriteIndexY * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX + HeadTailDistX,
			cRect.top + iScrollY + HeadTailDistY,
			info.CCX,
			info.CCY,
			hMemDC,
			beltSpriteIndexX / beltSpriteFrameDelay * info.CCX,
			headSpriteIndex * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX - HeadTailDistX,
			cRect.top + iScrollY - HeadTailDistY,
			info.CCX,
			info.CCY,
			hMemDC,
			beltSpriteIndexX / beltSpriteFrameDelay * info.CCX,
			tailSpriteIndex * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
		
	}
}

void CTransportBelt::Release_Object() {

}

void CTransportBelt::OnCollision(CObj* _TargetObj) {

}

void CTransportBelt::SetIndexY() {
    GetBeltConnect();
}

void CTransportBelt::GetBeltConnect() {
    vector<CObj*>* beltVec = CObjManager::GetInstance()->GetVector(OBJ::BELT);
    INT thisIndex = ((INT)info.position.y / GRIDCY * GRIDX) + ((INT)info.position.x / GRIDCX);
	CTransportBelt* tempHeadBelt = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex - GRIDX]);
	CTransportBelt* tempTailBelt = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex + GRIDX]);
	CTransportBelt* tempPortBelt = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex - 1]);
	CTransportBelt* tempStarBelt = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex + 1]);
    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH:
		headBelt = tempHeadBelt;
		tailBelt = tempTailBelt;
		portBelt = tempPortBelt;
		starBelt = tempStarBelt;

		tailSpriteIndex = 12;
		headSpriteIndex = 17;
		HeadTailDistX = 0;
		HeadTailDistY = -64;

		if (tailBelt && tailBelt->walkingState.direction == walkingState.direction) {
			spriteIndexY = 2;
			break;
		}
		if (portBelt && starBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST &&
				starBelt->GetWalkingState().direction != DIRECTION::DIR::WEST) {
				spriteIndexY = 6;
				tailBelt = portBelt;
			}
			else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::EAST &&
				starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) {
				spriteIndexY = 4;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 2;
		}
		else if (portBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST) {
				spriteIndexY = 6;
				tailBelt = portBelt;
			}
			else
				spriteIndexY = 2;
		}
		else if (starBelt) {
			if (starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) {
				spriteIndexY = 4;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 2;
		}
		else {
			spriteIndexY = 2;
		}
		break;
	case DIRECTION::DIR::EAST:
		headBelt = tempStarBelt;
		tailBelt = tempPortBelt;
		portBelt = tempHeadBelt;
		starBelt = tempTailBelt;
		tailSpriteIndex = 14;
		headSpriteIndex = 19;
		HeadTailDistX = 64;
		HeadTailDistY = 0;
		if (tailBelt && tailBelt->walkingState.direction == walkingState.direction) {
			spriteIndexY = 0;
			break;
		}
		if (portBelt && starBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH &&
				starBelt->GetWalkingState().direction != DIRECTION::DIR::NORTH) {
				spriteIndexY = 5;
				tailBelt = portBelt;
			}
			else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::SOUTH &&
				starBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH) {
				spriteIndexY = 8;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 0;
		}
		else if (portBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH) {
				spriteIndexY = 5;
				tailBelt = portBelt;
			}
			else
				spriteIndexY = 0;
		}
		else if (starBelt) {
			if (starBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH) {
				spriteIndexY = 8;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 0;
		}
		else {
			spriteIndexY = 0;
		}
		break;
	case DIRECTION::DIR::SOUTH:
		headBelt = tempTailBelt;
		tailBelt = tempHeadBelt;
		portBelt = tempStarBelt;
		starBelt = tempPortBelt;
		tailSpriteIndex = 16;
		headSpriteIndex = 13;
		HeadTailDistX = 0;
		HeadTailDistY = 64;

		if (tailBelt && tailBelt->walkingState.direction == walkingState.direction) {
			spriteIndexY = 3;
			break;
		}
		if (portBelt && starBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::WEST &&
				starBelt->GetWalkingState().direction != DIRECTION::DIR::EAST) {
				spriteIndexY = 9;
				tailBelt = portBelt;
			}
			else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::WEST &&
				starBelt->GetWalkingState().direction == DIRECTION::DIR::EAST) {
				spriteIndexY = 11;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 3;
		}
		else if (portBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) {
				spriteIndexY = 9;
				tailBelt = portBelt;
			}
			else
				spriteIndexY = 3;
		}
		else if (starBelt) {
			if (starBelt->GetWalkingState().direction == DIRECTION::DIR::EAST) {
				spriteIndexY = 11;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 3;
		}
		else {
			spriteIndexY = 3;
		}
		break;
	case DIRECTION::DIR::WEST:
		headBelt = tempPortBelt;
		tailBelt = tempStarBelt;
		portBelt = tempTailBelt;
		starBelt = tempHeadBelt;
		tailSpriteIndex = 18;
		headSpriteIndex = 15;
		HeadTailDistX = -64;
		HeadTailDistY = 0;

		if (tailBelt && tailBelt->walkingState.direction == walkingState.direction) {
			spriteIndexY = 1;
			break;
		}
		if (portBelt && starBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH &&
				starBelt->GetWalkingState().direction != DIRECTION::DIR::SOUTH) {
				spriteIndexY = 10;
				tailBelt = portBelt;
			}
			else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::NORTH &&
				starBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH) {
				spriteIndexY = 7;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 1;
		}
		else if (portBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH) {
				spriteIndexY = 10;
				tailBelt = portBelt;
			}
			else
				spriteIndexY = 1;
		}
		else if (starBelt) {
			if (starBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH) {
				spriteIndexY = 7;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 1;
		}
		else {
			spriteIndexY = 1;
		}
		break;
	default:
		headBelt = tempHeadBelt;
		tailBelt = tempTailBelt;
		portBelt = tempPortBelt;
		starBelt = tempStarBelt;

		tailSpriteIndex = 12;
		headSpriteIndex = 17;
		HeadTailDistX = 0;
		HeadTailDistY = -64;

		if (tailBelt && tailBelt->walkingState.direction == walkingState.direction) {
			spriteIndexY = 2;
			break;
		}
		if (portBelt && starBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST &&
				starBelt->GetWalkingState().direction != DIRECTION::DIR::WEST) {
				spriteIndexY = 6;
				tailBelt = portBelt;
			}
			else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::EAST &&
				starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) {
				spriteIndexY = 4;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 2;
		}
		else if (portBelt) {
			if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST) {
				spriteIndexY = 6;
				tailBelt = portBelt;
			}
			else
				spriteIndexY = 2;
		}
		else if (starBelt) {
			if (starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) {
				spriteIndexY = 4;
				tailBelt = starBelt;
			}
			else
				spriteIndexY = 2;
		}
		else {
			spriteIndexY = 2;
		}
		break;
	}
}
void CTransportBelt::TransportItem() {
	DIRECTION::DIR beltDir;
	DIRECTION::DIR tailDir;
	beltDir = walkingState.direction;
	if (tailBelt)
		tailDir = tailBelt->GetWalkingState().direction;
	else
		tailDir = beltDir;

	FLOAT dX;
	FLOAT dY;
	FLOAT dist;
	FLOAT rad;
	for (auto item : listItemOnBelt) {
		BOOL  movable = true;
		for (auto item2 : listItemOnBelt) {
			if (item == item2)
				continue;
			switch (beltDir) {
			case DIRECTION::DIR::NORTH:
				switch (tailDir) {
				case DIRECTION::DIR::EAST:
					if (item->GetPosition().y > item2->GetPosition().y && item->GetPosition().y < item2->GetPosition().y + 16.f &&
						((item->GetPosition().x  - info.position.x < 0) && (item->GetPosition().y  - info.position.y < 0)) ==
						((item2->GetPosition().x - info.position.x < 0) && (item2->GetPosition().y - info.position.y < 0)))
						movable = false;
					break;
				case DIRECTION::DIR::WEST:
					if (item->GetPosition().y > item2->GetPosition().y && item->GetPosition().y < item2->GetPosition().y + 16.f &&
						((item->GetPosition().x  - info.position.x > 0) && (item->GetPosition().y  - info.position.y < 0)) ==
						((item2->GetPosition().x - info.position.x > 0) && (item2->GetPosition().y - info.position.y < 0)))
						movable = false;
					break;
				default:
					if (item->GetPosition().y > item2->GetPosition().y && item->GetPosition().y < item2->GetPosition().y + 16.f &&
						(item->GetPosition().x - info.position.x > 0) == (item2->GetPosition().x - info.position.x > 0))
						movable = false;
					break;
				}
				break;
			case DIRECTION::DIR::EAST:
				switch (tailDir) {
				case DIRECTION::DIR::SOUTH:
					if (item->GetPosition().x < item2->GetPosition().x && item->GetPosition().x > item2->GetPosition().x - 16.f &&
						((item->GetPosition().x - info.position.x > 0) && (item->GetPosition().y - info.position.y < 0)) ==
						((item2->GetPosition().x - info.position.x > 0) && (item2->GetPosition().y - info.position.y < 0)))
						movable = false;
					break;
				case DIRECTION::DIR::NORTH:
					if (item->GetPosition().x < item2->GetPosition().x && item->GetPosition().x > item2->GetPosition().x - 16.f &&
						((item->GetPosition().x - info.position.x > 0) && (item->GetPosition().y - info.position.y > 0)) ==
						((item2->GetPosition().x - info.position.x > 0) && (item2->GetPosition().y - info.position.y > 0)))
						movable = false;
					break;
				default:
					if (item->GetPosition().x < item2->GetPosition().x && item->GetPosition().x > item2->GetPosition().x - 16.f &&
						(item->GetPosition().y - info.position.y > 0) == (item2->GetPosition().y - info.position.y > 0))
						movable = false;
					break;
				}
				break;
			case DIRECTION::DIR::SOUTH:
				switch (tailDir) {
				case DIRECTION::DIR::WEST:
					if (item->GetPosition().y < item2->GetPosition().y && item->GetPosition().y > item2->GetPosition().y - 16.f &&
						((item->GetPosition().x - info.position.x > 0) && (item->GetPosition().y - info.position.y > 0)) ==
						((item2->GetPosition().x - info.position.x > 0) && (item2->GetPosition().y - info.position.y > 0)))
						movable = false;
					break;
				case DIRECTION::DIR::EAST:
					if (item->GetPosition().y < item2->GetPosition().y && item->GetPosition().y > item2->GetPosition().y - 16.f &&
						((item->GetPosition().x - info.position.x < 0) && (item->GetPosition().y - info.position.y > 0)) ==
						((item2->GetPosition().x - info.position.x < 0) && (item2->GetPosition().y - info.position.y > 0)))
						movable = false;
					break;
				default:
					if (item->GetPosition().y < item2->GetPosition().y && item->GetPosition().y > item2->GetPosition().y - 16.f &&
						(item->GetPosition().x - info.position.x > 0) == (item2->GetPosition().x - info.position.x > 0))
						movable = false;
					break;
				}
				break;
			case DIRECTION::DIR::WEST:
				switch (tailDir) {
				case DIRECTION::DIR::NORTH:
					if (item->GetPosition().x > item2->GetPosition().x && item->GetPosition().x < item2->GetPosition().x + 16.f &&
						((item->GetPosition().x - info.position.x < 0) && (item->GetPosition().y - info.position.y > 0)) ==
						((item2->GetPosition().x - info.position.x < 0) && (item2->GetPosition().y - info.position.y > 0)))
						movable = false;
					break;
				case DIRECTION::DIR::SOUTH:
					if (item->GetPosition().x > item2->GetPosition().x && item->GetPosition().x < item2->GetPosition().x + 16.f &&
						((item->GetPosition().x - info.position.x < 0) && (item->GetPosition().y - info.position.y < 0)) ==
						((item2->GetPosition().x - info.position.x < 0) && (item2->GetPosition().y - info.position.y < 0)))
						movable = false;
					break;
				default:
					if (item->GetPosition().x > item2->GetPosition().x && item->GetPosition().x < item2->GetPosition().x + 16.f &&
						(item->GetPosition().y - info.position.y > 0) == (item2->GetPosition().y - info.position.y > 0))
						movable = false;
					break;
				}
				break;
			default:
				break;
			}
		}
		if (headBelt) {
			for (auto item2 : headBelt->listItemOnBelt) {
				switch (beltDir) {
				case DIRECTION::DIR::NORTH:
					if (item->GetPosition().y > item2->GetPosition().y && item->GetPosition().y < item2->GetPosition().y + 16.f &&
						(item->GetPosition().x - headBelt->GetPosition().x > 0) == (item2->GetPosition().x - headBelt->GetPosition().x > 0))
						movable = false;
					break;
				case DIRECTION::DIR::EAST:
					if (item->GetPosition().x < item2->GetPosition().x && item->GetPosition().x > item2->GetPosition().x - 16.f &&
						(item->GetPosition().y - headBelt->GetPosition().y > 0) == (item2->GetPosition().y - headBelt->GetPosition().y > 0))
						movable = false;
					break;
				case DIRECTION::DIR::SOUTH:
					if (item->GetPosition().y < item2->GetPosition().y && item->GetPosition().y > item2->GetPosition().y - 16.f &&
						(item->GetPosition().x - headBelt->GetPosition().x > 0) == (item2->GetPosition().x - headBelt->GetPosition().x > 0))
						movable = false;
					break;
				case DIRECTION::DIR::WEST:
					if (item->GetPosition().x > item2->GetPosition().x && item->GetPosition().x < item2->GetPosition().x + 16.f &&
						(item->GetPosition().y - headBelt->GetPosition().y > 0) == (item2->GetPosition().y - headBelt->GetPosition().y > 0))
						movable = false;
					break;
				default:
					break;
				}
			}
		}
		else {
			switch (beltDir) {
			case DIRECTION::DIR::NORTH:
				if (item->GetPosition().y < info.position.y - 28.f)
					movable = false;
				break;
			case DIRECTION::DIR::EAST:
				if (item->GetPosition().x > info.position.x + 28.f)
					movable = false;
				break;
			case DIRECTION::DIR::SOUTH:
				if (item->GetPosition().y > info.position.y + 28.f)
					movable = false;
				break;
			case DIRECTION::DIR::WEST:
				if (item->GetPosition().x < info.position.x - 28.f)
					movable = false;
				break;
			default:
				break;
			}
		}
		if(movable)
			switch (beltDir) {
			case DIRECTION::DIR::NORTH:
				switch (tailDir) {
				case DIRECTION::DIR::EAST:
					dX = item->GetPosition().x - (FLOAT)rect.left + 20;
					dY = item->GetPosition().y - (FLOAT)rect.top + 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) - 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				case DIRECTION::DIR::WEST:
					dX = item->GetPosition().x - (FLOAT)rect.right - 20;
					dY = item->GetPosition().y - (FLOAT)rect.top + 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) + 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				default:
					item->SetPosition(item->GetPosition() + POSITION(0.f, -2.f));
					if (item->GetPosition().x > info.position.x)
						item->SetPosition(info.position.x + 16, item->GetPosition().y);
					else
						item->SetPosition(info.position.x - 16, item->GetPosition().y);
					break;
				}
				break;
			case DIRECTION::DIR::EAST:
				switch (tailDir) {
				case DIRECTION::DIR::SOUTH:
					dX = item->GetPosition().x - (FLOAT)rect.right - 20;
					dY = item->GetPosition().y - (FLOAT)rect.top + 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) - 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				case DIRECTION::DIR::NORTH:
					dX = item->GetPosition().x - (FLOAT)rect.right - 20;
					dY = item->GetPosition().y - (FLOAT)rect.bottom - 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) + 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				default:
					item->SetPosition(item->GetPosition() + POSITION(2.f, 0.f));
					if (item->GetPosition().y > info.position.y)
						item->SetPosition(item->GetPosition().x, info.position.y + 16);
					else
						item->SetPosition(item->GetPosition().x, info.position.y - 16);
					break;
				}
				break;
			case DIRECTION::DIR::SOUTH:
				switch (tailDir) {
				case DIRECTION::DIR::WEST:
					dX = item->GetPosition().x - (FLOAT)rect.right - 20;
					dY = item->GetPosition().y - (FLOAT)rect.bottom - 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) - 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				case DIRECTION::DIR::EAST:
					dX = item->GetPosition().x - (FLOAT)rect.left + 20;
					dY = item->GetPosition().y - (FLOAT)rect.bottom - 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) + 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				default:
					item->SetPosition(item->GetPosition() + POSITION(0.f, 2.f));
					if (item->GetPosition().x > info.position.x)
						item->SetPosition(info.position.x + 16, item->GetPosition().y);
					else
						item->SetPosition(info.position.x - 16, item->GetPosition().y);
					break;
				}
				break;
			case DIRECTION::DIR::WEST:
				switch (tailDir) {
				case DIRECTION::DIR::SOUTH:
					dX = item->GetPosition().x - (FLOAT)rect.left + 20;
					dY = item->GetPosition().y - (FLOAT)rect.top + 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) + 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				case DIRECTION::DIR::NORTH:
					dX = item->GetPosition().x - (FLOAT)rect.left + 20;
					dY = item->GetPosition().y - (FLOAT)rect.bottom - 20;
					dist = sqrtf(dX * dX + dY * dY);
					rad = atan2f(dY, dX) - 0.05f;
					item->SetPosition(item->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
					break;
				default:
					item->SetPosition(item->GetPosition() + POSITION(-2.f, 0.f));
					if (item->GetPosition().y > info.position.y)
						item->SetPosition(item->GetPosition().x, info.position.y + 16);
					else
						item->SetPosition(item->GetPosition().x, info.position.y - 16);
					break;
				}
				break;
			default:
				break;
			}
	}
}

CObj* CTransportBelt::GetNewActor() {
	CObj* tempObj = new CTransportBelt();
	tempObj->Ready_Object();
	return tempObj;
}

CItem* CTransportBelt::GetNewItem() {
	CItem* tempItem = new CItemTransportBelt();
	return tempItem;
}