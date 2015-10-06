#pragma once

#include <GL\glaux.h>
#include "../SlotMachine/SlotMachine.h"
#include "TextureObjectManager.h"
#include "../Common.h"
#include <list>
/*
�������� �������. �������� ����������� �������� � ����� SlotMachine
*/

enum CanvasState {
	_waiting,
	_inProcess
};

class Canvas
{
public:
	Canvas(int width, int height);
	~Canvas();

	// ������������� ����� ������� �������
	void setSize(int width, int height); 
	// ���������� ������� ������� �������
	void getSize(int &width, int &height) const; 
	// ���������� ������� ��������� �������� ��������
	bool inProcess();
	// ���������� �� Main ��� ������� ���, ������� ������� ���������� ���������
	void mouseClicked(int x, int y);
	// ������ � ���� �� �����. �������� ������ ���� ������� ��������
	void Update();
	TextureMap *getTextureMap() ; // ���������� ��������� �� ������ ��������

private:
	int currentWidth; // ������� ������� �����
	int currentHeight;
	void createTextureMap(TypeObjectsMap* objectsMap);
	// ��� �������
	SlotMachine *slotMachine;
	// ���� ���� �������, ������������ � �������.
	// ���������� � Main'�. 
	TextureMap textureMap;
	//������� ���������, � ������ ��� � �������� ������� ������
	int state;

};

