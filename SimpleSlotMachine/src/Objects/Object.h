#pragma once

#include "../Common.h"
class TextureObjectManager;

/*
������� ����� ��� ��������
�������� ����� ��� �������� ��������, �������, ���� �������, ���
� ��������� � ��� ��������
*/

// ���� �������. ���������� ��� �������� �������� ��������
enum ObjectRole{
	_start,
	_select,
	_leftWheel,
	_centerWheel,
	_rightWheel,
};

// ��� �������. ��������� � �������� ����� ��� �������������
enum ObjectType{
	ot_button,
	ot_wheel
};

// ������������� ������� ������� �� ������. ����� ����� � ��������� �� 0-1 
struct Position {
	Position();
	double lb_xrf;
	double lb_yrf;
	double rt_xrf;
	double rt_yrf;
};

class Object
{
public:
	Object(ObjectType _type ,ObjectRole _role, int _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yrf);
	virtual ~Object();

	// ����������� ����� ��� ���������� �������� ��������� �������
	virtual void Update();
	// ������������� ��������� ��� �������. 
	void setState(int _state);
	// �������� ������� ���������
	int getState() const;
	// ��������� ������� �������
	void setPos(double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yrf);
	void setPos(Position _pos);
	// ���������� ������� ��������� �������
	void getPos(double &_lb_xrf, double &_lb_yrf, double &_rt_xrf, double &_rt_yrf) const;
	Position getPos() const;
	// ������� ���������� ������������� ���������� x � y � ���������
	// ��������� �� ��� � ������������� ����������� �������. ����������� ��� 
	// ��������, ���� �� ������ ��� �� ��������������� �������
	bool checkPos(double x, double y);

	// ���������� ������ �������, ��������� � ���� ��������
	TextureMap *getTextureMap();
	// ���������� ���� ������� 
	ObjectRole getObjectRole() const;
	// ���������� ��� ������� 
	ObjectType getObjectType() const;
	
private:
	// ��������� �������. ������ ��� ������ ��������� �������.
	// ��� ������ �������� ��� Enabled~Disabled, ��� �������� Waiting~Running
	int state;
	// ���� ������� (����� ������ ������ ��� �������)
	ObjectRole role;
	// ���������� ��� ������� (������ ��� �������)
	ObjectType type;
	// ������� ������� � ������������� ����������
	Position pos;
	// ������ ��������� � �������� �������
	TextureMap textureMap;
	
};

