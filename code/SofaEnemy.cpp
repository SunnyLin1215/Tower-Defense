#include <string>

#include "SofaEnemy.hpp"

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include"EnemyBullet.h"

SofaEnemy::SofaEnemy(int x, int y) : Enemy("play/kangi-3.png",  4, x, y, 50, 100, 250, 30, 0.5) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
	time = 0;
}
void SofaEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new EnemyBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
