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

void CActor::Release_Object() {

}

void CActor::OnCollision(CObj* _TargetObj) {

}

void CActor::UpdateSelected() {

}
