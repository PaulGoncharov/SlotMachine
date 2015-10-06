#include "Object.h"
#include "../Canvas/TextureObjectManager.h"
Position::Position() {
	lb_xrf = 0;
	lb_yrf = 0;
	rt_xrf = 0;
	rt_yrf = 0;
}

Object::Object(ObjectType _type, ObjectRole _role, int _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yrf) :
type(_type),
role(_role),
state(_state)
{
	setPos(_lb_xrf, _lb_yrf, _rt_xrf, _rt_yrf);
}

Object::~Object()
{
}

void Object::Update() {
	// Do nothing
}

void Object::setPos(double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yrf){
	pos.lb_xrf = _lb_xrf;
	pos.lb_yrf = _lb_yrf;
	pos.rt_xrf = _rt_xrf;
	pos.rt_yrf = _rt_yrf;
}
void Object::getPos(double &_lb_xrf, double &_lb_yrf, double &_rt_xrf, double &_rt_yrf) const {
	_lb_xrf = pos.lb_xrf;
	_lb_yrf = pos.lb_yrf;
	_rt_xrf = pos.rt_xrf;
	_rt_yrf = pos.rt_yrf;
}

void Object::setPos(Position _pos){
	pos.lb_xrf = _pos.lb_xrf;
	pos.lb_yrf = _pos.lb_yrf;
	pos.rt_xrf = _pos.rt_xrf;
	pos.rt_yrf = _pos.rt_yrf;
}
Position Object::getPos() const {
	return pos;
}

ObjectRole Object::getObjectRole() const{
	return role;
}

ObjectType Object::getObjectType() const {
	return type;
}

TextureMap *Object::getTextureMap() {
	return &textureMap;
}

bool Object::checkPos(double x, double y) {
	if ((x > pos.lb_xrf) && (x < pos.rt_xrf) && (y > pos.lb_yrf) && (y < pos.rt_yrf)) {
		return true;
	}
	else {
		return false;
	}
}

void Object::setState(int _state) {
	state = _state;
}

int Object::getState() const {
	return state;
}