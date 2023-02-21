#include <string>

#include "StrongEnemy.hpp"

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include"EnemyBullet.h"

StrongEnemy::StrongEnemy(int x, int y) : Enemy("play/enemy-3.png",3,  x, y, 20, 20, 150, 40, 0.5) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
void StrongEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new EnemyBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
