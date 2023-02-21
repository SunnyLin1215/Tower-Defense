#ifndef BADBULLET_H_INCLUDED
#define BADBULLET_H_INCLUDED

#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;

namespace Engine {
struct Point;
}  // namespace Engine

class BadBullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Enemy* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Turret* turret);
public:
	Turret* Target = nullptr;
	explicit BadBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void Update(float deltaTime) override;
	//friend class Enemy;
};

#endif // BADBULLET_H_INCLUDED
