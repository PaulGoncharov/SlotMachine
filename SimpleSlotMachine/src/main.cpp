#include <windows.h>
#include "Canvas\Canvas.h"
#include "Common.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>
#include <GL\glut.h>
#include <string>
// �������
Canvas *canvas;

// ������� ��� ���
std::time_t current_time, base_time;
int fps, fps_count;

// ���������� fps
void DrawFps(){
	glColor3d(0, 0, 0);
	std::string s = "Current fps " + std::to_string(fps);
	int length = s.size();
	const char *s_fps = s.c_str(); 
	glRasterPos2i(10, 10); // raster position in 2D
	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s_fps[i]); // generation of characters in our text with 9 by 15 GLU font
	}

}

// ������� ����������� �����
void _stdcall  Redisplay(void)
{
	// ��������� ��������� �������
	canvas->Update();

	// ������� fps
	current_time = std::time(nullptr);
	int elapse = current_time - base_time;

	if (elapse > 1) {
		base_time = current_time;
		fps = fps_count;
		fps_count = 0;
	}
	else{
		fps_count++;
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1, 1, 1);

	// �������� ��� ��������� �������
	TextureMap *TexManList = canvas->getTextureMap();
	TextureMap::iterator it;
	double offset_x = 0, offset_y = 0;
	int windowsWight, windowsHeigth;
	double textureWight = 0, textureHeigth = 0;
	canvas->getSize(windowsWight, windowsHeigth);
	for (it = TexManList->begin(); it != TexManList->end(); it++) {
		Texture *texture = it->second;
		if (texture->ena) { // ���������� �� �������
			Position pos = texture->pos;
			switch (texture->group) {	// ��������� �������� ��������� � ����������� ��������
				// � ����������� �� ���� ������� � �������� ��� ���������
			case TextureGroup::_backgrounds:	// ���
				textureWight = windowsWight;
				textureHeigth = windowsHeigth;
				break;
			case TextureGroup::_buttons:	// ������
			case TextureGroup::_wheels:		// ��������
			case TextureGroup::_customTextures:
				// ����� �� x � y
				offset_x = pos.lb_xrf * windowsWight;
				offset_y = pos.lb_yrf * windowsHeigth;
				// ������ � ������ �������� ��� ������ ������� �������
				textureWight = pos.rt_xrf * windowsWight - offset_x;
				textureHeigth = pos.rt_yrf * windowsHeigth - offset_y;
				break;
			} //switch (id->role)

			// ��� ���� � ������ ��������� ������
			if (((texture->group) == TextureGroup::_backgrounds) || ((texture->group) == TextureGroup::_buttons)) {
				// ��������� � ���������� ��������
				glBindTexture(GL_TEXTURE_2D, texture->id);
				glBegin(GL_QUADS);
				glTexCoord2d(0, 0); glVertex3d(offset_x, offset_y, -0.1);
				glTexCoord2d(0, 1); glVertex3d(offset_x, offset_y + ((double)textureHeigth), -0.1);
				glTexCoord2d(1, 1); glVertex3d(offset_x + ((double)textureWight), offset_y + ((double)textureHeigth), -0.1);
				glTexCoord2d(1, 0); glVertex3d(offset_x + ((double)textureWight), offset_y, -0.1);
				glEnd();

			}	// ��� ���������
			else if ((texture->group) == TextureGroup::_wheels) {
				// ��������� �������� � ���������
				glBindTexture(GL_TEXTURE_2D, texture->id);

				GLUquadricObj *quadObj;
				quadObj = gluNewQuadric();
				gluQuadricTexture(quadObj, GL_TRUE);
				gluQuadricDrawStyle(quadObj, GLU_FILL);
				glColor3d(1, 1, 1);

				glPushMatrix();
				// ���� ��� ������ ���������
				glTranslated(offset_x + textureWight, offset_y + textureHeigth / 2, 0);
				// ������� ����� � �������
				glRotated(-90, 0.0, 1.0, 0.0);
				// ������� ����� 
				glRotated(WHEEL_ROTATE_OFFSET, 0.0, 0.0, 1.0);
				// ��������
				GLfloat RotateAngle = (GLfloat)texture->rotatingAngle;
				glRotated(-RotateAngle, 0, 0, 1);
				// �������
				gluCylinder(quadObj, textureHeigth / 2, textureHeigth / 2, textureWight, 100, 100);
				glPopMatrix();

				gluDeleteQuadric(quadObj);
			}
			else { // ��������� ��������� ������� 
				switch (it->first) {
						case TextureRole::_selectLines:{ // ������ ����� ��� ������ Select
							glColor3d(1, 0, 0);
							glLineWidth(10);
							glBegin(GL_LINES);
							glVertex2d(offset_x, offset_y);									// �����  "/"
							glVertex2d(offset_x + textureWight, offset_y + textureHeigth);
							glVertex2d(offset_x, offset_y + textureHeigth / 2);				// �����  "--"
							glVertex2d(offset_x + textureWight, offset_y + textureHeigth / 2);
							glVertex2d(offset_x + textureWight, offset_y);					// ����� "\"
							glVertex2d(offset_x, offset_y + textureHeigth);
							glEnd();
							break;
						case TextureRole::_w_slash:
							glColor3d(1, 0, 0);
							glLineWidth(10);
							glBegin(GL_LINES);
							glVertex2d(offset_x, offset_y);									// �����  "/"
							glVertex2d(offset_x + textureWight, offset_y + textureHeigth);
							glEnd();
							break;
						case TextureRole::_w_center:
							glColor3d(1, 0, 0);
							glLineWidth(10);
							glBegin(GL_LINES);
							glVertex2d(offset_x, offset_y + textureHeigth / 2);				// �����  "--"
							glVertex2d(offset_x + textureWight, offset_y + textureHeigth / 2);
							glEnd();
							break;
						case TextureRole::_w_backslash:
							glColor3d(1, 0, 0);
							glLineWidth(10);
							glBegin(GL_LINES);
							glVertex2d(offset_x + textureWight, offset_y);					// ����� "\"
							glVertex2d(offset_x, offset_y + textureHeigth);
							glEnd();
							break;

					}
				}

			}
		}

		textureWight = 0, textureHeigth = 0;
		offset_x = 0, offset_y = 0;

	}
	glDisable(GL_TEXTURE_2D);

	// ������� fps
	DrawFps();
	auxSwapBuffers();

}

// ���������� ��������� �������� ����
void _stdcall Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ((double)width), 0, ((double)height), 0.0, 300.0);
	gluLookAt(0, 0, 290, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	// ���������� ����� ������� � �������
	canvas->setSize(width, height);
}

// ���������� ������� ���
void _stdcall Mouse_left(AUX_EVENTREC *event)
{
	int x, y;
	auxGetMouseLoc(&x, &y);

	if (!canvas->inProcess()) {
		canvas->mouseClicked(x, y);
	}
}


// �������� ������� � ������, ���������� �� �������
void loadTextures() {

	TextureMap *TexManList = canvas->getTextureMap();
	TextureMap::iterator it;

	for (it = TexManList->begin(); it != TexManList->end(); it++) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		Texture *texture = it->second;
		switch (it->first) {
		case TextureRole::_backgound:
			texture->data = auxDIBImageLoad(TEXT("Textures/background.bmp"));
			break;
		case TextureRole::_startEna:
			texture->data = auxDIBImageLoad(TEXT("Textures/startEna.bmp"));
			break;
		case TextureRole::_startDis:
			texture->data = auxDIBImageLoad(TEXT("Textures/startDis.bmp"));
			break;
		case TextureRole::_selectEna:
			texture->data = auxDIBImageLoad(TEXT("Textures/selectEna.bmp"));
			break;
		case TextureRole::_selectDis:
			texture->data = auxDIBImageLoad(TEXT("Textures/selectDis.bmp"));
			break;
		case TextureRole::_wheel:
			texture->data = auxDIBImageLoad(TEXT("Textures/Wheel_9.bmp"));
			break;
		default:
			continue;
			break;
		}

		// ��������� � ���������� ��������
		glGenTextures(1, &texture->id);
		glBindTexture(GL_TEXTURE_2D, texture->id);
		// ��������� �������� ��� ����������� �������� ������� � �������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			texture->data->sizeX,
			texture->data->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE,
			texture->data->data);
	}
}


void main()
{
	canvas = new Canvas(WINDOW_WIDTH, WINDOW_HEIGHT);
	current_time = base_time = std::time(nullptr);
	auxInitPosition(50, 50, 600, 400);
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);
	// ������� ���� �� ������
	auxInitWindow(NULL);
	// �������� ��� �������� 
	auxIdleFunc(Redisplay);
	// ��������� �������� ����
	auxReshapeFunc(Resize);
	// ���������� ������� ���
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, Mouse_left);
	// ��������� �������
	loadTextures();
	// �������� ����
	auxMainLoop(Redisplay);
	return;
}
