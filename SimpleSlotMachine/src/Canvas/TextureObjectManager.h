#pragma once

#include <GL\glaux.h>
#include "../Objects/Object.h"

/*
�������� ������� ��� ��������. 
*/

enum TextureRole{
	_backgound,
	_startEna,
	_startDis,
	_selectEna,
	_selectDis,
	_wheel,
	_selectLines, // ��������� �����
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
��������. ������� ����� ���������� �������, � ����� ��������������� ����
���������� ��� ����������
*/
struct Texture{
	Texture(TextureGroup _group, Position _pos, bool _ena);
	~Texture();
	// ������������� � ���������� ������ (������, �������, ���)
	TextureGroup group;
	// �������������� ���� ������ �������
	ObjectRole objRole;
	// ������� � ������������� ����������
	Position pos;
	// ������������ ��������. ��������������� ��������� OpenGl
	unsigned int id;
	// ������ ��������������� ��������� OpenGl
	AUX_RGBImageRec* data;
	// ���� ��������, ���� ������� ���������
	double rotatingAngle;
	bool ena;
};

// ������ ��� ��������
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
