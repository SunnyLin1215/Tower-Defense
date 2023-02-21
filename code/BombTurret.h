#ifndef BOMBTURRET_H_INCLUDED
#define BOMBTURRET_H_INCLUDED


class BombTurret: public Turret {
public:
	static const int Price;
    BombTurret(float x, float y);
	void CreateBullet() override;
};



#endif // BOMBTURRET_H_INCLUDED
