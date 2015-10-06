#pragma once

#include "Object.h"
#include <ctime>

/*
Cass Wheel наслеуется от Object
*/

// Положение/Тип барабана
enum WheelRole {
	WR_LEFT,
	WR_CENTER,
	WR_RIGHT
};

// Состояние барабана
enum WheelState {
	_stopped,
	_running
};

class Wheel: public Object
{
public:
	Wheel(ObjectType _type, ObjectRole _role, WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
	~Wheel();
	// Запускает вращение барабана
	void Start();
	virtual void Update();
	unsigned int getPosition();
private:
	// Связанные текстуры.
	TextureObjectManager *wheel;
	// Время момента начала вращения барабана
	std::time_t lastTime;
	// Текущее время
	std::time_t currentTime;
	// Время, которое барабан бует вращаться
	double rotatingTime;
	// Текущая "скорость вращения"
	double rotatingSpeed;
	// Доп угол ля оворота при остановке барабана
	double currentAnngle;
	// Тормоз вращения
	double brake;
	// Позиция, на которой в данный момент находится барабан
	// необходима для подсчёта результатов
	unsigned int position;
	// Угол доворота
	double adjustmenAngle;
	// Счётчик итераций доворота
	int currentAdjustmentCount;
	// Максимальное значение счётчика
	const static int AdjustmentCount = 50;
};

