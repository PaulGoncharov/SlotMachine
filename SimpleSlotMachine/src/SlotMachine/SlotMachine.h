#pragma once

#include "../Objects/Object.h"
#include "../Objects/Button.h"
#include "../Objects/Wheel.h"
#include "../Common.h"
#include <list>
#include <map>

/*
����� ���������� ��������. ����� ������������ �������������.
������ ������ �������� (������, ��������). ���������� ��������� �� ������ ������
��������.
*/

class Canvas;

enum SlotMachineState {
	sl_waiting,
	sl_inProcess,
	sl_show_result
};

enum Result {
	r_nothing,
	r_slash,
	r_center,
	r_backslah
};


typedef std::map<ObjectRole, Object*> TypeObjectsMap;
typedef std::pair<ObjectRole, Object*> ObjectPair;

class SlotMachine
{
public:
	// ���������� ��������� �� ����������� ������������� ����
	static SlotMachine* SlotMachine::GetInstance(void);
	~SlotMachine();
	// ���������� ��������� �� ������ ��������
	int getState();
	TypeObjectsMap *getButtonsMap();
	TypeObjectsMap *getWheelsMap();
	// ��������� �������� ���������
	void Start();
	// ��������� ���������
	void Update(Canvas *canvas);
	// ��������� ��������� ������ ��������
	int CalcResult();

private:
	SlotMachine();
	// ������ �������� (������, ��������)
	TypeObjectsMap buttonsMap;
	TypeObjectsMap wheelsMap;
	// ��������� �������� ��. SlotMachineState
	SlotMachineState state;
	// ��������� �������(���������)/��������
	unsigned int result;
	// ��������������� �������� ��� ����������� ����������
	std::time_t showResultStartTime, currentTime;
	// ��������������� �������� ��� ������ ����������
	Texture *resultTexture;

};

