#ifndef NEWENEMY_H_INCLUDED
#define NEWENEMY_H_INCLUDED
#include "Enemy.hpp"

class NewEnemy : public Enemy {
public:
	NewEnemy(int x, int y);
	void CreateBullet() override;
};


#endif // NEWENEMY_H_INCLUDED
