#include "Button.h"
#include "../Canvas/TextureObjectManager.h"

Button::Button(ObjectType _type, ObjectRole _role, ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Object(_type, _role, _state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
	// �������������� ������� (�� ��������� ��) ���������� TextureObjectManager
	// ���� �������� ���������� � ���������� ������
	textureEna = nullptr;
	textureDis = nullptr;
	TextureRole enaRole, disRole;

	switch (_role) {
	case ObjectRole::_start:
		enaRole = TextureRole::_startEna; 
		disRole = _startDis;
		break;
	case ObjectRole::_select:
		enaRole = TextureRole::_selectEna; 
		disRole = _selectDis;
		break;
	}


	textureEna = new TextureObjectManager(TextureGroup::_buttons, false, this);
	textureDis = new TextureObjectManager(TextureGroup::_buttons, true, this);

	TextureMap *textureMap = this->getTextureMap();
	textureMap->insert(TexturePair(enaRole, textureEna->getTexture()));
	textureMap->insert(TexturePair(disRole, textureDis->getTexture()));

}

Button::~Button()
{
}


void Button::Update() {

	// ��������� �������� ����� ena ��� �������, ��������� � �������
	// ���� �������� ���������, ������ ��������, 
	// � ����������� �� ����������� ���������
	TextureMap *TextureMap = this->getTextureMap();
	TextureMap::iterator it;
	for (it = TextureMap->begin(); it != TextureMap->end(); it ++)
	{
		it->second->ena = !(it->second->ena);
	}

	// �������� ������� ��������� �� ���������������
	if (this->getState() == ButtonState::_disabled) {
		this->setState(ButtonState::_enabled);
	}
	else {
		this->setState(ButtonState::_disabled);
	}
	
}