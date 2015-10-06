#pragma once

#include "../Common.h"
class TextureObjectManager;

/*
Базовый класс для объектов
Содержит общие для объектов сущности, позицию, роль объекта, тип
и связанные с ним текстуры
*/

// Роль объекта. Собственно все сущности игрового автомата
enum ObjectRole{
	_start,
	_select,
	_leftWheel,
	_centerWheel,
	_rightWheel,
};

// Тип объекта. Передаётся в дочерний класс для идентификации
enum ObjectType{
	ot_button,
	ot_wheel
};

// Относительная позиция объекта на экране. Числа лежат в диапазоне от 0-1 
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

	// Виртуальный метод для обновления текущего состояния объекта
	virtual void Update();
	// Устанавливает состояние для объекта. 
	void setState(int _state);
	// Получаем текущее состояние
	int getState() const;
	// Установка текущей позиции
	void setPos(double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yrf);
	void setPos(Position _pos);
	// возвращает текущие кооринаты объекта
	void getPos(double &_lb_xrf, double &_lb_yrf, double &_rt_xrf, double &_rt_yrf) const;
	Position getPos() const;
	// Фунцция приинимает относительные координаты x и y и проверяет
	// находятся ли они в относительных координатах объекта. Применяется для 
	// проверки, была ли нажата ЛКМ на соответствующем объекте
	bool checkPos(double x, double y);

	// Возвращает список текстур, связанных с этим объектом
	TextureMap *getTextureMap();
	// Возвращает роль объекта 
	ObjectRole getObjectRole() const;
	// Возвращает тип объекта 
	ObjectType getObjectType() const;
	
private:
	// состояние объекта. Разные для разных сущностей объекта.
	// Для кнопки например это Enabled~Disabled, для барабана Waiting~Running
	int state;
	// Роль объекта (какая именно кнопка или барабан)
	ObjectRole role;
	// Возвращает тип объекта (кнопка или барабан)
	ObjectType type;
	// Текущая позиция в относительных кооринатах
	Position pos;
	// Список связанных с объектом текстур
	TextureMap textureMap;
	
};

