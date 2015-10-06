#pragma once

#include "Object.h"
#include <ctime>

/*
Cass Wheel ���������� �� Object
*/

// ���������/��� ��������
enum WheelRole {
	WR_LEFT,
	WR_CENTER,
	WR_RIGHT
};

// ��������� ��������
enum WheelState {
	_stopped,
	_running
};

class Wheel: public Object
{
public:
	Wheel(ObjectType _type, ObjectRole _role, WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
	~Wheel();
	// ��������� �������� ��������
	void Start();
	virtual void Update();
	unsigned int getPosition();
private:
	// ��������� ��������.
	TextureObjectManager *wheel;
	// ����� ������� ������ �������� ��������
	std::time_t lastTime;
	// ������� �����
	std::time_t currentTime;
	// �����, ������� ������� ���� ���������
	double rotatingTime;
	// ������� "�������� ��������"
	double rotatingSpeed;
	// ��� ���� �� ������� ��� ��������� ��������
	double currentAnngle;
	// ������ ��������
	double brake;
	// �������, �� ������� � ������ ������ ��������� �������
	// ���������� ��� �������� �����������
	unsigned int position;
	// ���� ��������
	double adjustmenAngle;
	// ������� �������� ��������
	int currentAdjustmentCount;
	// ������������ �������� ��������
	const static int AdjustmentCount = 50;
};

