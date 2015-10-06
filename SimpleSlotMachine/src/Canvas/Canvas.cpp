#include "Canvas.h"
void _stdcall Redisplay(void);
void _stdcall Resize(int width, int height);

Canvas::Canvas(int width, int heigth) :
currentWidth(width),
currentHeight(heigth),
state(_waiting)
{
	// Основная задача, собрать указатели на все использующиеся текстуры
	// Фон создаём прямо здесь. Остальные создаются с помощью SlotMachine

	Position customPos;
	Texture *background = new Texture(TextureGroup::_backgrounds, customPos, true);
	textureMap.insert(TexturePair(TextureRole::_backgound, background));

	// Заполняем карту указателей на текстуры из объектов, содержащихся в SlotMachine,
	// которая была создана во время инициализации программы.
	// Типы объектов кнопки и барабаны.
	slotMachine = SlotMachine::GetInstance();

	// Добавляем в карту текстуры кнопок
	createTextureMap(slotMachine->getButtonsMap());
	// Текстуры барабанов
	createTextureMap(slotMachine->getWheelsMap());

	// Добавляем псевдотекстуры, которые будет служить для отображения линий
	// по нажатию на кнопку Select и отображения результатов при выйгрыше
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

	// Игровой автомат занят, игорируем нажатие ЛКМ
	if (slotMachine->getState() != SlotMachineState::sl_waiting) {
		return;
	}

	// Переводим координаты мыши в относительные координаты полотна
	double x_ref, y_ref;
	x_ref = (double)x/currentWidth;
	y_ref = 1 - (double)y/currentHeight; //Отчёт пикселей идёт свеху

	TypeObjectsMap *buttonsMap = slotMachine->getButtonsMap();
	TypeObjectsMap::iterator bit;

	// Проверяем, соответствуют ли координаты положения мыши
	// координатам какого либо из объектов (кнопки)
	for (bit = buttonsMap->begin(); bit != buttonsMap->end(); bit++) {
		if (bit->second->checkPos(x_ref, y_ref)) {
			// Обновляем состояник кнопки
			bit->second->Update();

			// Итератор на кастомную текстуру кнопки Select
			TextureMap::iterator select_it = textureMap.find(TextureRole::_selectLines);
			if (select_it != textureMap.end()) {
				select_it->second->ena = false;
			}
			
			switch (bit->first) {
				// Была нажата кнопка Start
			case ObjectRole::_start:
					{
						slotMachine->Start();
						// Включаем отображение линий, отображающих возможные комбинации
						select_it->second->ena = false;
						break;
					}
					// Была нажата кнопка Select
				case ObjectRole::_select:
					{
						// Включаем/выключаем отображение линий, отображающих возможные комбинации
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