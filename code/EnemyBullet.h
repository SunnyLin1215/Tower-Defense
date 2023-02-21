#ifndef ENEMYBULLET_H_INCLUDED
#define ENEMYBULLET_H_INCLUDED

#include"EnemyBullet.h"
#include"BadBullet.h"
class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class EnemyBullet : public BadBullet {
public:
	explicit EnemyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode(Turret*  turret) override;
};



#endif // ENEMYBULLET_H_INCLUDED
