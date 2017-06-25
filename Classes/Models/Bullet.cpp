#include "Bullet.h"

USING_NS_CC;

Bullet* Bullet::create() {
	Bullet* bullet = new Bullet();
	if (!bullet) CC_ASSERT(false);
	return bullet;
}

bool Bullet::initialize() {
	return true;
}

void Bullet::makeShoot() {

}