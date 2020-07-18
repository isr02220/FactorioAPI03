#include "Actor.h"

CActor::CActor() : CObj(){

}

CActor::CActor(FLOAT _positionX, FLOAT _positionY) : CObj(_positionX, _positionY){

}

CActor::~CActor() {

}

void CActor::Ready_Object() {

}

INT CActor::Update_Object() {

	return 0;
}

void CActor::LateUpdate_Object() {

}

void CActor::Render_Object(HDC hDC) {

}

void CActor::Render_Placable(HDC hDC, BOOL placable) {

}

void CActor::Release_Object() {

}

void CActor::OnCollision(CObj* _TargetObj) {

}

CObj* CActor::GetNewActor() {
	CObj* tempObj = new CActor();
	tempObj->Ready_Object();
	return tempObj;
}

void CActor::UpdateSelected(CActor* _Target) {
	selectedActor = _Target;
}
