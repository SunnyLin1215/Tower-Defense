#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"
#include"Turret.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
	float hp;
	int money;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	float reload = 0;
	float coolDown;
	std::list<Enemy*>::iterator lockedEnemyIterator;
	virtual void CreateBullet() = 0;
public:
       bool Enabled = true;
       int time;
       Turret* Target = nullptr;
       int type;
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, int type, float x, float y, float radius, float speed, float hp, int money, float coolDown );
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
