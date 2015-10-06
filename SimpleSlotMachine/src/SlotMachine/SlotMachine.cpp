#include "SlotMachine.h"
#include "../Canvas/Canvas.h"


SlotMachine::SlotMachine()
{
	// Начальное состоние - ожидание
	state = SlotMachineState::sl_waiting;

	// Создаём все элементы игрового автомата и помещаем в соответствующие контейнеры указатели на них
	Button *Start = new Button(ObjectType::ot_button, ObjectRole::_start, ButtonState::_disabled,
								START_BUTTON_LB_X_REFP, START_BUTTON_LB_Y_REFP,
								START_BUTTON_RT_X_REFP, START_BUTTON_RT_Y_REFP);
	buttonsMap.insert(ObjectPair(ObjectRole::_start, Start));

	Button *Select = new Button(ObjectType::ot_button, ObjectRole::_select, ButtonState::_disabled,
								SELECT_BUTTON_LB_X_REFP, SELECT_BUTTON_LB_Y_REFP,
								SELECT_BUTTON_RT_X_REFP, SELECT_BUTTON_RT_Y_REFP);
	buttonsMap.insert(ObjectPair(ObjectRole::_select, Select));

	Wheel *LeftWheel = new Wheel(ObjectType::ot_wheel, ObjectRole::_leftWheel, WheelState::_stopped,
								LEFT_WHELL_LB_X_REFP, LEFT_WHELL_LB_Y_REFP,
								LEFT_WHELL_RT_X_REFP, LEFT_WHELL_RT_Y_REFP);
	wheelsMap.insert(ObjectPair(ObjectRole::_leftWheel, LeftWheel));

	Wheel *CenterWheel = new Wheel(ObjectType::ot_wheel, ObjectRole::_centerWheel, WheelState::_stopped,
								CENTER_WHELL_LB_X_REFP, CENTER_WHELL_LB_Y_REFP,
								CENTER_WHELL_RT_X_REFP, CENTER_WHELL_RT_Y_REFP);
	wheelsMap.insert(ObjectPair(ObjectRole::_centerWheel, CenterWheel));

	Wheel *RightWheel = new Wheel(ObjectType::ot_wheel, ObjectRole::_rightWheel, WheelState::_stopped,
								RIGHT_WHELL_LB_X_REFP, RIGHT_WHELL_LB_Y_REFP,
								RIGHT_WHELL_RT_X_REFP, RIGHT_WHELL_RT_Y_REFP);
	wheelsMap.insert(ObjectPair(ObjectRole::_rightWheel, RightWheel));
	
	result = 0;
}


SlotMachine::~SlotMachine()
{
}

SlotMachine* SlotMachine::GetInstance(void) {
	static SlotMachine slotMachine;
	return &slotMachine;
}

int SlotMachine::getState() {
	return state;
}

void SlotMachine::Start() {

	// Изменяем текущее состояние автомата
	state = SlotMachineState::sl_inProcess;

	// Обнуляем результат
	result = 0;

	TypeObjectsMap::iterator bit;

	// Проверяем состояние кнопки Select. Выключаем её, если она включена
	bit = buttonsMap.find(ObjectRole::_select);
	if (bit != buttonsMap.end()) {
		Object *select = bit->second;
		if (select->getState() == ButtonState::_enabled) {
			select->Update();
		}
	}

	// Запускаем вращение барабанов
	TypeObjectsMap::iterator wit;

	for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
		if (Wheel* w = dynamic_cast<Wheel*>(wit->second)) {
			w->Start();
		}
	}
}

void SlotMachine::Update(Canvas *_canvas) {
	Canvas *canvas = _canvas;
	if (state == SlotMachineState::sl_inProcess) {
		// Все ли барабаны остановлены
		bool allStoped = true;

		// Обновляем и проверяем состояние барабанов
		TypeObjectsMap::iterator wit; // Итератор для карты с барабанами

		// Проверяем состояние барабанов
		for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
			if (wit->second->getState() == WheelState::_running) {
				wit->second->Update();
				allStoped = false;
			}
		}

		TypeObjectsMap::iterator bit; // Итератор для карты с кнопками

		// Все барабаны прекратили вращение
		if (allStoped) {
			bit = buttonsMap.find(ObjectRole::_start);
			if (bit != buttonsMap.end()) {
				Object *start = bit->second;
				if (start->getState() == ButtonState::_enabled) {
					// Закончили вращение. Возвращаемся в исходное состояние и проверяем результат
					if (result = CalcResult()) {
						showResultStartTime = currentTime = std::time(nullptr);
						state = SlotMachineState::sl_show_result;
						TextureMap * textureMap = canvas->getTextureMap();
						TextureMap::iterator it;
						resultTexture = nullptr;
						// Обработка результатов костыль
						switch (result) {
							case r_slash:
								it = textureMap->find(TextureRole::_w_slash);
								resultTexture = it->second;
								break;
							case r_center:
								it = textureMap->find(TextureRole::_w_center);
								resultTexture = it->second;
								break;
							case r_backslah:
								it = textureMap->find(TextureRole::_w_backslash);
								resultTexture = it->second;
								break;
						}

						resultTexture->ena = true;
					}
					else {
						state = SlotMachineState::sl_waiting;
						start->Update();
					}
				}
			}

		}
	}
	else if (state == SlotMachineState::sl_show_result) {
		currentTime = std::time(nullptr);
		int elapse = currentTime - showResultStartTime;

		if (elapse < SHOW_RESULT_DURATION) {
			//resultTexture->ena = true;
		}
		else {
			resultTexture->ena = false;
			state = SlotMachineState::sl_waiting;
			TypeObjectsMap::iterator bit;
			bit = buttonsMap.find(ObjectRole::_start);
			bit->second->Update();
		}
	}
}

// Примитивнейшая обработка результатов
int SlotMachine::CalcResult() {
	TypeObjectsMap::iterator wit;
	unsigned int wheelsPositions[3];
	unsigned int tmpLeft, tmpRight;
	int count = 0;
	for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
		if (Wheel* w = dynamic_cast<Wheel*>(wit->second)) {
			wheelsPositions[count] = w->getPosition();
			count++;
		}
	}
	if (count != 3) {
		// Error
		return Result::r_nothing;
	}

	int qwe = 0;

	if ((wheelsPositions[0] == wheelsPositions[1]) &&
		(wheelsPositions[0] == wheelsPositions[2])) {
		return Result::r_center;
	}

	tmpLeft =  wheelsPositions[0] + 1;
	if (tmpLeft == WHEEL_ELEMENTS_COUNT) {
		tmpLeft = 0;
	}

	tmpRight = wheelsPositions[2] - 1;
	if (tmpRight > WHEEL_ELEMENTS_COUNT) {
		tmpRight = WHEEL_ELEMENTS_COUNT - 1;
	}


	if ((tmpLeft == wheelsPositions[1]) &&
		(tmpRight == wheelsPositions[2])) {
		return Result::r_slash;
	}

	tmpLeft = wheelsPositions[0] - 1;
	if (tmpLeft > WHEEL_ELEMENTS_COUNT) {
		tmpLeft = WHEEL_ELEMENTS_COUNT - 1;
	}

	tmpRight = wheelsPositions[2] + 1;
	if (tmpRight == WHEEL_ELEMENTS_COUNT) {
		tmpRight = 0;
	}


	if ((tmpLeft == wheelsPositions[1]) &&
		(tmpRight == wheelsPositions[2])) {
		return Result::r_backslah;
	}

	return Result::r_nothing;
}

TypeObjectsMap *SlotMachine::getButtonsMap() {
	return &buttonsMap;
}

TypeObjectsMap *SlotMachine::getWheelsMap() {
	return &wheelsMap;
}