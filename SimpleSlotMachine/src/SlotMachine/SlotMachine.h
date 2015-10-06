#pragma once

#include "../Objects/Object.h"
#include "../Objects/Button.h"
#include "../Objects/Wheel.h"
#include "../Common.h"
#include <list>
#include <map>

/*
Класс игрального автомата. Имеет единственное представление.
Создаёт группу объектов (кнопки, барабаны). Возвращает указатель на список данных
объектов.
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
	// Возвращает указатель на единствонне рпедставление себя
	static SlotMachine* SlotMachine::GetInstance(void);
	~SlotMachine();
	// Возвращает указатель на список объектов
	int getState();
	TypeObjectsMap *getButtonsMap();
	TypeObjectsMap *getWheelsMap();
	// Запускаем вращение барабанов
	void Start();
	// Обновляем состояние
	void Update(Canvas *canvas);
	// Проверяем результат работы автомата
	int CalcResult();

private:
	SlotMachine();
	// список объектов (кнопки, барабаны)
	TypeObjectsMap buttonsMap;
	TypeObjectsMap wheelsMap;
	// Состояние автомата см. SlotMachineState
	SlotMachineState state;
	// Результат выйгрыш(несколько)/пройгрыш
	unsigned int result;
	// Вспомогательные счётчики для отображения результата
	std::time_t showResultStartTime, currentTime;
	// Вспомогательная текстура для показа результата
	Texture *resultTexture;

};

