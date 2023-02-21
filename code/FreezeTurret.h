#ifndef FREEZETURRET_H_INCLUDED
#define FREEZETURRET_H_INCLUDED

class FreezeTurret: public Turret {
public:
	static const int Price;
    FreezeTurret(float x, float y);
	void CreateBullet() override;
};

#endif // FREEZETURRET_H_INCLUDED
