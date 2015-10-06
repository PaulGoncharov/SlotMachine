#include "Wheel.h"
#include "../Canvas/TextureObjectManager.h"

Wheel::Wheel(ObjectType _type, ObjectRole _role, WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Object(_type, _role, _state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
	// �������������� ������� (�� ��������� ��) ���������� TextureObjectManager
	// ���� ��������� ���������� � ���������� ��������
	wheel = nullptr;
	wheel = new TextureObjectManager(TextureGroup::_wheels, true, this);

	TextureMap *textureMap = this->getTextureMap();
	textureMap->insert(TexturePair(TextureRole::_wheel, wheel->getTexture()));

	// �������������� �������
	position = 0;
}

Wheel::~Wheel()
{

}

void Wheel::Start() {

	// �������� ����
	currentTime = lastTime = std::time(nullptr);
	this->setState(WheelState::_running);

	// ����� �������� ��������������� �� 5 �� 6 �
	std::srand(std::time(0)); //use current time as seed for random generator
	int random_variable = rand() % 30;
	rotatingTime = WHEEL_MIN_TIME + (double)random_variable/10;

	// ������ ���� �������� ������
	currentAnngle = 0;

	// ������������� ������� ��������
	rotatingSpeed = 0;

	// ������
	brake = BRAKE_START_COEF;

	adjustmenAngle = 0;
	currentAdjustmentCount = 0;

	position = 0;
}

void Wheel::Update() {
	switch (this->getState()) {
			case WheelState::_stopped:
				// ������ �� ������
			break;
		case WheelState::_running:
			currentTime = std::time(nullptr);
			// ����� � ������� ������ ��������
			std::time_t elapse = currentTime - lastTime;

			if ((elapse >= 0) && ((elapse < ACCELERATION_TIME))) { // ������ ������
				int randomValue = rand() % 25 + START_CMOOTH_COEF;
				rotatingSpeed += randomValue; // ����������� �������� 
				currentAnngle += randomValue;
			}
			else if (elapse < rotatingTime) { //���������� ������
				int randomValue = rand() % 10 + BRAKE_SMOOTH_COEF;
				rotatingSpeed += randomValue / brake; // ���������� ������
				currentAnngle += 10 + randomValue / brake;
				brake += BRAKE_ADDING_COEF;
			}
			else if (elapse > rotatingTime) { // ������������� ������
				// ���������� ������� �������
				if (currentAdjustmentCount == 0) {
					adjustmenAngle = WHEEL_ANGLE_STEP - std::fmod(currentAnngle, WHEEL_ANGLE_STEP);
					// ��������� ������� ������� ��������
					// ���������� ���������, �� ������� ���������� �������
					double denominator = WHEEL_ANGLE_STEP;
					int count = ceil((adjustmenAngle + currentAnngle) / denominator);
					// ������� �������
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
