#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include"BadBullet.h"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.h"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include"IObject.hpp"
#include"Point.hpp"
#include "Resources.hpp"


PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, int t, float x, float y, float radius, float speed, float hp, int money, float cool) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money) {
       type = t;
       coolDown = cool;
	CollisionRadius = radius;
	reachEndTime = 0;
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;

	if(type == 2) {
              Velocity.x -= 2;
              if(Velocity.x <= 1) Velocity.x = 1;
       }
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}

void Enemy::Update(float deltaTime) {
	float remainSpeed = speed * deltaTime;

	PlayScene* scene = getPlayScene();

	if( type == 4) {
              if(time != 150) time++;
              else {
                     Position.x -= 2.3* Velocity.x;
                     bmp = Engine::Resources::GetInstance().GetBitmap("play/kangi-3.png");
                     Size.x = GetBitmapWidth()+17;
                     Size.y = GetBitmapHeight()+17;
                     time = 0;
                     type = 5;
              }
	}else if(type == 5) {
              if(time != 160) time++;
              else {
                     Position.x -= 2.5* Velocity.x;
                     bmp = Engine::Resources::GetInstance().GetBitmap("play/kangi-1.png");
                     Size.x = GetBitmapWidth()+18;
                     Size.y = GetBitmapHeight()+18;
                     time = 0;
                     type = 6;
              }
	}else if(type == 6) {
              if(time != 180) time++;
              else {
                     Position.x -= 2.6* Velocity.x;
                     bmp = Engine::Resources::GetInstance().GetBitmap("play/kangi-4.png");
                     Size.x = GetBitmapWidth()+17;
                     Size.y = GetBitmapHeight()+17;
                     time = 0;
                     type = 7;
              }
	}else if(type == 7) {
              if(time != 200) time++;
              else {
                     Position.x -= 2.8* Velocity.x;
                     bmp = Engine::Resources::GetInstance().GetBitmap("play/kangi-2.png");
                     Size.x = GetBitmapWidth();
                     Size.y = GetBitmapHeight();
                     time = 0;
                     type = 8;
              }
	}else if(type == 8) {
              if(time != 200) time++;
              else {
                     Position.x -= 3* Velocity.x;
                     bmp = Engine::Resources::GetInstance().GetBitmap("play/kangi-5.png");
                     Size.x = GetBitmapWidth()+17;
                     Size.y = GetBitmapHeight()+17;
                     time = 0;
                     type = 8;
              }
	}else Position.x -= Velocity.x * deltaTime;

       if(Target && Position.x <= Target->Position.x + 100) {
              Position.x = Target->Position.x + 100;
       }

       //Position.y += Velocity.y * deltaTime;

	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp);
		if(type >= 4 && type <= 8) getPlayScene()->Hit(15);
		else getPlayScene()->Hit(0);
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;

	//Sprite::Update(deltaTime);

	//PlayScene* scene = getPlayScene();

	if (!Enabled)
		return;

	if (Target) {
		if (Target->Position.x > Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
			Target->lockedEnemies.erase(lockedEnemyIterator);
			Target = nullptr;
			lockedEnemyIterator = std::list<Enemy*>::iterator();
		}
		// Shoot reload.
		reload -= 0.5*deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreateBullet();
		}
	}

	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->TowerGroup->GetObjects()) {
                   if (it->Position.x < Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
                                   Target = dynamic_cast<Turret*>(it);
                                   Target->lockedEnemies.push_back(this);
                                   lockedEnemyIterator = std::prev(Target->lockedEnemies.end());
                                   break;
                     }
		}
	}

}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
