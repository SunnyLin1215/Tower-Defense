#include <string>

#include "NewEnemy.h"

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include"EnemyBullet.h"

NewEnemy::NewEnemy(int x, int y) : Enemy("play/enemy-4.png", 2,x, y, 25, 100, 100, 25, 0.5) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
void NewEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new EnemyBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
