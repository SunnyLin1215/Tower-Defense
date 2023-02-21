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
#include"RemoveTurret.h"

const int RemoveTurret::Price = 0;
RemoveTurret::RemoveTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/bomb.png", x, y, 15, Price, 1, 0) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
	//Preview = true;
	type = 5;
}

void RemoveTurret::CreateBullet() {
	//Engine::Point diff = Engine::Point(1,0);
	//float rotation = ALLEGRO_PI / 2;
	//getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position , diff, rotation, this));
	//AudioHelper::PlayAudio("gun.wav");
}
