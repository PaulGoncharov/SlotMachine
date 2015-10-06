#include <list> 
#include <map>
// Общие данные
#define WINDOW_WIDTH	604				// Ширина окна, пкс.
#define WINDOW_HEIGHT	466				// Высота окна, пкс
#define ACCELERATION_TIME 3.5			// Время разгона барабана
#define BRAKE_START_COEF	1.1			// Начальное значение коэффициента торможения
#define BRAKE_ADDING_COEF	0.1			// Постепенное торможение
#define BRAKE_SMOOTH_COEF	10			// Коэффициент для плавного торможения
#define START_CMOOTH_COEF	10			// Коэффициент для плавного разгона
#define WHEEL_MIN_TIME	5				// Минимальное время, которое крутиться барабан
#define WHEEL_ROTATE_OFFSET	5			// Угол, на который доворачивается барабан при инициализации,
										// чтобы картинка была по центру
#define WHEEL_ELEMENTS_COUNT	9		// Количество элементов на барабане
// Шаг барабана, гр. Угловое значение между двумя полями
#define WHEEL_ANGLE_STEP	360/WHEEL_ELEMENTS_COUNT			

#define SHOW_RESULT_DURATION	2		// Время, в течение которого будут показаны результаты вращения барабанов

#define SELECT_BUTTON_LB_X_REFP	0.2748013245033113	// Опорные точки для кнопки start и select	
#define SELECT_BUTTON_LB_Y_REFP	0.050793991416309	// Рассчитаны относительно дефолтного значения окна
#define SELECT_BUTTON_RT_X_REFP	0.4867880794701987	// Относительные значения
#define SELECT_BUTTON_RT_Y_REFP	0.1680901287553648
#define START_BUTTON_LB_X_REFP	0.5099006622516556
#define START_BUTTON_LB_Y_REFP	0.050793991416309
#define START_BUTTON_RT_X_REFP	0.721887417218543
#define START_BUTTON_RT_Y_REFP	0.1680901287553648

#define LEFT_WHELL_LB_X_REFP	0.2456556291390728 // То же самое для барабанов
#define LEFT_WHELL_LB_Y_REFP	0.229343347639485
#define LEFT_WHELL_RT_X_REFP	0.4070066225165563
#define LEFT_WHELL_RT_Y_REFP	0.7397596566523605

#define CENTER_WHELL_LB_X_REFP	0.413841059602649
#define CENTER_WHELL_LB_Y_REFP	0.229343347639485
#define CENTER_WHELL_RT_X_REFP	0.5762251655629139
#define CENTER_WHELL_RT_Y_REFP	0.7397596566523605

#define RIGHT_WHELL_LB_X_REFP	0.5827483443708609
#define RIGHT_WHELL_LB_Y_REFP	0.229343347639485
#define RIGHT_WHELL_RT_X_REFP	0.7467549668874172
#define RIGHT_WHELL_RT_Y_REFP	0.7397596566523605

struct Texture;
typedef  std::multimap<int ,Texture*> TextureMap;
typedef std::pair<int, Texture*> TexturePair;

