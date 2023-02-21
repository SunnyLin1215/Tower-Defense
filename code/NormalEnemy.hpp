#ifndef NORMALENEMY_HPP
#define NORMALENEMY_HPP
#include "Enemy.hpp"

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

class NormalEnemy : public Enemy {
public:
	NormalEnemy(int x, int y);
	void CreateBullet() override;
};
#endif // NORMALENEMY_HPP
