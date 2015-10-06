#pragma once

#include <GL\glaux.h>
#include "../SlotMachine/SlotMachine.h"
#include "TextureObjectManager.h"
#include "../Common.h"
#include <list>
/*
Основное полотно. Содержит необходимые текстуры и класс SlotMachine
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

	// Устанавливаем новые размеры полотна
	void setSize(int width, int height); 
	// Возвращаем текущие размеры полотна
	void getSize(int &width, int &height) const; 
	// Возвращает текущее состояние игрового автомата
	bool inProcess();
	// Вызывается из Main при нажатии ЛКМ, передаёт текущие координаты указателя
	void mouseClicked(int x, int y);
	// Апдейт в лупе из мейна. Вызывает апдейт всех текущих объектов
	void Update();
	TextureMap *getTextureMap() ; // Возвращаем указатель на список структур

private:
	int currentWidth; // Текущие размеры сцены
	int currentHeight;
	void createTextureMap(TypeObjectsMap* objectsMap);
	// Сам автомат
	SlotMachine *slotMachine;
	// Лист всех текстур, содержащихся в полотне.
	// Вызывается в Main'е. 
	TextureMap textureMap;
	//Текущее состояние, в работе или в ожидании нажатия кнопки
	int state;

};

