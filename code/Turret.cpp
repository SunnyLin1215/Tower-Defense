#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <random>
#include <string>
#include <vector>

#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include"Bullet.hpp"
#include "BadBullet.h"
#include"ExplosionEffect.hpp"
#include"DirtyEffect.hpp"
#include"AudioHelper.hpp"
#include"LOG.hpp"
#include"Collider.hpp"
class PlayScene;

PlayScene* Turret::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Turret::OnExplode() {

       if( type == 5) {
              for (auto& it : getPlayScene()->TowerGroup->GetObjects()) {
			Turret* turret = dynamic_cast<Turret*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius + 5, turret->Position, turret->CollisionRadius))
				turret->Hit(INFINITY);
              }
       }

       if(type == 4) {
		 for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* enemy = dynamic_cast<Enemy*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius + 400, enemy->Position, enemy->CollisionRadius))
				enemy->Hit(INFINITY);
              }
       }
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
Turret::Turret(std::string imgTurret, float x, float y,float radius, int price, float coolDown, float hp) :
	Sprite(imgTurret, x, y), price(price), coolDown(coolDown) {
       this->hp = hp;
	CollisionRadius = radius;
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}

void Turret::Update(float deltaTime) {

        if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp);
		getPlayScene()->Hit(0);
		//reachEndTime = 0;
		return;
	}

	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	if (Target) {
		if (Target->Position.x < Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;

			if( Target->Position.x <= 1580) CreateBullet();
			//CreateBullet();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x > Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}
}


void Turret::Update_remove(float deltaTime) {
       OnExplode();
}


void Turret::Hit(float damage) {

	hp -= damage;

	if (hp <= 0) {
		OnExplode();
		getPlayScene()->change_mapstate(Position.x,  Position.y);
		//PlayScene :: mapState[ Position.y / PlayScene::BlockSize][  Position.x / PlayScene::BlockSize] = TILE_FLOOR;
		// Remove all turret's reference to target.
		for (auto& it: lockedEnemies)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->TowerGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}

}

void Turret::Draw() const {
       //std::cout << type << std::endl;
	if (Preview  && type == 4 ) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius + 400, al_map_rgba(0, 255, 0, 50));
	}

	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}
}
int Turret::GetPrice() const {
	return price;
}
