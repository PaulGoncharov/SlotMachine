#include "Wheel.h"
#include "../Canvas/TextureObjectManager.h"

Wheel::Wheel(ObjectType _type, ObjectRole _role, WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Object(_type, _role, _state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
	// Инициализируем тестуры (не загружаем их) посреством TextureObjectManager
	// куда передаётся информация о назначении барабана
	wheel = nullptr;
	wheel = new TextureObjectManager(TextureGroup::_wheels, true, this);

	TextureMap *textureMap = this->getTextureMap();
	textureMap->insert(TexturePair(TextureRole::_wheel, wheel->getTexture()));

	// Инициализируем позицию
	position = 0;
}

Wheel::~Wheel()
{

}

void Wheel::Start() {

	// Обнуляем часы
	currentTime = lastTime = std::time(nullptr);
	this->setState(WheelState::_running);

	// Время вращения устанавливается от 5 до 6 с
	std::srand(std::time(0)); //use current time as seed for random generator
	int random_variable = rand() % 30;
	rotatingTime = WHEEL_MIN_TIME + (double)random_variable/10;

	// Отсчёт угла начинаем заново
	currentAnngle = 0;

	// Устанавливаем нулевую скорость
	rotatingSpeed = 0;

	// Тормоз
	brake = BRAKE_START_COEF;

	adjustmenAngle = 0;
	currentAdjustmentCount = 0;

	position = 0;
}

void Wheel::Update() {
	switch (this->getState()) {
			case WheelState::_stopped:
				// Ничего не делаем
			break;
		case WheelState::_running:
			currentTime = std::time(nullptr);
			// Время с момента начала вращения
			std::time_t elapse = currentTime - lastTime;

			if ((elapse >= 0) && ((elapse < ACCELERATION_TIME))) { // Разгон колеса
				int randomValue = rand() % 25 + START_CMOOTH_COEF;
				rotatingSpeed += randomValue; // Увеличиваем скорость 
				currentAnngle += randomValue;
			}
			else if (elapse < rotatingTime) { //Торможение колеса
				int randomValue = rand() % 10 + BRAKE_SMOOTH_COEF;
				rotatingSpeed += randomValue / brake; // Используем тормоз
				currentAnngle += 10 + randomValue / brake;
				brake += BRAKE_ADDING_COEF;
			}
			else if (elapse > rotatingTime) { // Останавливаем колесо
				// Используем плавный доворот
				if (currentAdjustmentCount == 0) {
					adjustmenAngle = WHEEL_ANGLE_STEP - std::fmod(currentAnngle, WHEEL_ANGLE_STEP);
					// Обновляем текущую позицию барабана
					// Количество элементов, на которое повернулся барабан
					double denominator = WHEEL_ANGLE_STEP;
					int count = ceil((adjustmenAngle + currentAnngle) / denominator);
					// Текущая позиция
					position = std::fmod(position + count, WHEEL_ELEMENTS_COUNT);
				}
				else if (currentAdjustmentCount == AdjustmentCount + 1) {
					this->setState(WheelState::_stopped);
				}
				else {
					rotatingSpeed += adjustmenAngle / AdjustmentCount;
				}
				currentAdjustmentCount++;

			}

			wheel->getTexture()->rotatingAngle = rotatingSpeed;

			break;
	}
}

unsigned int Wheel::getPosition() {
	return position;
}
