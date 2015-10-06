#include "TextureObjectManager.h"
#include "../Objects/Object.h"

Texture::Texture(TextureGroup _group, Position _pos, bool _ena) {
	group = _group;
	pos = _pos;
	ena = _ena;
	rotatingAngle = 0;
	data = nullptr;
}

Texture::~Texture() {
	data = nullptr;///////////////////////////////////////////
}

TextureObjectManager::TextureObjectManager(TextureGroup _texGroup, bool _ena, Object *_object) :
object(_object)
{
	texture = new Texture(_texGroup, object->getPos(), _ena);
	setEna(_ena);

}

TextureObjectManager::~TextureObjectManager() {
	delete texture;
	texture = nullptr;
}

void TextureObjectManager::setEna(bool state) {
	texture->ena = state;
}

void TextureObjectManager::setPos(Position _pos) {
	texture->pos = _pos;
}

Texture *TextureObjectManager::getTexture() {
	return texture;
}