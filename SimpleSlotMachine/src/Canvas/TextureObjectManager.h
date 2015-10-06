#pragma once

#include <GL\glaux.h>
#include "../Objects/Object.h"

/*
Менеджер текстур для объектов. 
*/

enum TextureRole{
	_backgound,
	_startEna,
	_startDis,
	_selectEna,
	_selectDis,
	_wheel,
	_selectLines, // Кастомные линии
	_w_slash,
	_w_center,
	_w_backslash
};

enum TextureGroup {
	_backgrounds,
	_buttons,
	_wheels,
	_customTextures,
};

/* 
Текстура. соержит данны загруженно тестуры, а также вспомогательные поля
необхоимые для управления
*/
struct Texture{
	Texture(TextureGroup _group, Position _pos, bool _ena);
	~Texture();
	// Приналежность к опреелённой группе (кнопка, барабан, фон)
	TextureGroup group;
	// Функциональная роль самого объекта
	ObjectRole objRole;
	// Позиция в относительных кооринатах
	Position pos;
	// Иентификатор текстуры. Устанавливается срествами OpenGl
	unsigned int id;
	// Данные Устанавливаются срествами OpenGl
	AUX_RGBImageRec* data;
	// Угол поворота, если тектура вращается
	double rotatingAngle;
	bool ena;
};

// Обёртка для Текстуры
class TextureObjectManager {
public:
	TextureObjectManager(TextureGroup _texGroup, bool _ena, Object *_obj);
	~TextureObjectManager();
	TextureRole textureRole;
	Position &getPos() const;
	void setPos(Position pos);
	Texture *getTexture();
	void setEna(bool state);
private:
	Object* object;
	Texture *texture;

};
