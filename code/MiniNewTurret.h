#ifndef MININEWTURRET_H_INCLUDED
#define MININEWTURRET_H_INCLUDED

class MiniNewTurret: public Turret {
public:
	static const int Price;
    MiniNewTurret(float x, float y);
	void CreateBullet() override;
};


#endif // MININEWTURRET_H_INCLUDED
