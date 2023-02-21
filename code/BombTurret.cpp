#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include"MiniNewTurret.h"
#include"FireBullet.h"
#include"BombTurret.h"

const int BombTurret::Price = 100;
BombTurret::BombTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-5.png", x, y, 15, Price, 0.5, 1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
	//Preview = true;
	type = 4;
}

void BombTurret::CreateBullet() {
	//Engine::Point diff = Engine::Point(1,0);
	//float rotation = ALLEGRO_PI / 2;
	//getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position , diff, rotation, this));
	//AudioHelper::PlayAudio("gun.wav");
}

