#ifndef SPECIALENEMY_H_INCLUDED
#define SPECIALENEMY_H_INCLUDED

#include "Enemy.hpp"

class SpecialEnemy : public Enemy {
public:
	SpecialEnemy(int x, int y);
	void CreateBullet() override;
};


#endif // SPECIALENEMY_H_INCLUDED
