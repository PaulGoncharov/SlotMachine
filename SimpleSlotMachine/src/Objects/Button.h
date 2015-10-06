#pragma once
#include "Object.h"
#include <list>

/*
Cass Button. Наслеуется от Object 
*/

enum ButtonState {
	_enabled,
	_disabled
};

class Button: public Object
{
public:
	Button(ObjectType _type, ObjectRole _role, ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
	~Button();
	virtual void Update();
private:
	// Связанные текстуры. Отображают состояние кнопки,
	// кога она выключена или включена
	TextureObjectManager *textureEna;
	TextureObjectManager *textureDis;
};

