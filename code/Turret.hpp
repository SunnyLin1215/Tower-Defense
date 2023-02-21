#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"
#include"PlayScene.hpp"

class Enemy;
class PlayScene;
class BadBullet;

class Turret: public Engine::Sprite {
protected:
       Engine::Point target;
    int price;
    float hp;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

public:
       int type;
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    std::list<Enemy*> lockedEnemies;
       std::list<BadBullet*> lockedBullets;    //感覺有問題

       float reachEndTime;
    Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,float radius, int price, float coolDown, float hp);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
	void Hit(float damage);
	void OnExplode();
	void Update_remove(float deltaTime);
};
#endif // TURRET_HPP
