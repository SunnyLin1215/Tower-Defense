#include <string>

#include "NormalEnemy.hpp"

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include"EnemyBullet.h"

NormalEnemy::NormalEnemy(int x, int y) : Enemy("play/enemy-1.png", 1,  x, y, 10, 60, 50, 15, 0.5) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
void NormalEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new EnemyBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
