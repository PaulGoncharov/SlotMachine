#include "Canvas.h"
void _stdcall Redisplay(void);
void _stdcall Resize(int width, int height);

Canvas::Canvas(int width, int heigth) :
currentWidth(width),
currentHeight(heigth),
state(_waiting)
{
	// �������� ������, ������� ��������� �� ��� �������������� ��������
	// ��� ������ ����� �����. ��������� ��������� � ������� SlotMachine

	Position customPos;
	Texture *background = new Texture(TextureGroup::_backgrounds, customPos, true);
	textureMap.insert(TexturePair(TextureRole::_backgound, background));

	// ��������� ����� ���������� �� �������� �� ��������, ������������ � SlotMachine,
	// ������� ���� ������� �� ����� ������������� ���������.
	// ���� �������� ������ � ��������.
	slotMachine = SlotMachine::GetInstance();

	// ��������� � ����� �������� ������
	createTextureMap(slotMachine->getButtonsMap());
	// �������� ���������
	createTextureMap(slotMachine->getWheelsMap());

	// ��������� ��������������, ������� ����� ������� ��� ����������� �����
	// �� ������� �� ������ Select � ����������� ����������� ��� ��������
	customPos.lb_xrf = LEFT_WHELL_LB_X_REFP;
	customPos.lb_yrf = LEFT_WHELL_LB_Y_REFP;
	customPos.rt_xrf = RIGHT_WHELL_RT_X_REFP;
	customPos.rt_yrf = RIGHT_WHELL_RT_Y_REFP;
	Texture *selectLines = new Texture(TextureGroup::_customTextures, customPos, false);
	textureMap.insert(TexturePair(TextureRole::_selectLines, selectLines));
	Texture *slashLine = new Texture(TextureGroup::_customTextures, customPos, false);
	textureMap.insert(TexturePair(TextureRole::_w_slash, slashLine));
	Texture *center = new Texture(TextureGroup::_customTextures, customPos, false);
	textureMap.insert(TexturePair(TextureRole::_w_center, center));
	Texture *backSlashLine = new Texture(TextureGroup::_customTextures, customPos, false);
	textureMap.insert(TexturePair(TextureRole::_w_backslash, backSlashLine));
}

Canvas::~Canvas()
{

}


void Canvas::createTextureMap(TypeObjectsMap* objectsMap) {

	TypeObjectsMap::iterator oit;

	TextureMap *objectTextureMap;
	TextureMap::iterator tit;

	for (oit = objectsMap->begin(); oit != objectsMap->end(); oit++) {
		objectTextureMap = oit->second->getTextureMap();
		for (tit = objectTextureMap->begin(); tit != objectTextureMap->end(); tit++) {
			textureMap.insert(*tit);
		}
	}
}

void Canvas::setSize(int width, int height) {
	currentWidth = width;
	currentHeight = height;
}


void Canvas::getSize(int &width, int &height) const {
	width = currentWidth;
	height = currentHeight;
}

TextureMap *Canvas::getTextureMap() {
	return &textureMap;
}

bool Canvas::inProcess() {
	if (slotMachine->getState()) { 
		return true;
	}
	else {
		return false;
	}
}

void Canvas::mouseClicked(int x, int y) {

	// ������� ������� �����, ��������� ������� ���
	if (slotMachine->getState() != SlotMachineState::sl_waiting) {
		return;
	}

	// ��������� ���������� ���� � ������������� ���������� �������
	double x_ref, y_ref;
	x_ref = (double)x/currentWidth;
	y_ref = 1 - (double)y/currentHeight; //����� �������� ��� �����

	TypeObjectsMap *buttonsMap = slotMachine->getButtonsMap();
	TypeObjectsMap::iterator bit;

	// ���������, ������������� �� ���������� ��������� ����
	// ����������� ������ ���� �� �������� (������)
	for (bit = buttonsMap->begin(); bit != buttonsMap->end(); bit++) {
		if (bit->second->checkPos(x_ref, y_ref)) {
			// ��������� ��������� ������
			bit->second->Update();

			// �������� �� ��������� �������� ������ Select
			TextureMap::iterator select_it = textureMap.find(TextureRole::_selectLines);
			if (select_it != textureMap.end()) {
				select_it->second->ena = false;
			}
			
			switch (bit->first) {
				// ���� ������ ������ Start
			case ObjectRole::_start:
					{
						slotMachine->Start();
						// �������� ����������� �����, ������������ ��������� ����������
						select_it->second->ena = false;
						break;
					}
					// ���� ������ ������ Select
				case ObjectRole::_select:
					{
						// ��������/��������� ����������� �����, ������������ ��������� ����������
						if (bit->second->getState() == ButtonState::_enabled) {
							select_it->second->ena = true;
						}
						else {
							select_it->second->ena = false;
						}
						

						break;
					}
				} // switch
		}
	}
}
	


void Canvas::Update() {
	slotMachine->Update(this);
}