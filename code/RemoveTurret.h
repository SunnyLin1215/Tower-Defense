#ifndef REMOVETURRET_H_INCLUDED
#define REMOVETURRET_H_INCLUDED


class RemoveTurret: public Turret {
public:
	static const int Price;
    RemoveTurret(float x, float y);
	void CreateBullet() override;
};



#endif // REMOVETURRET_H_INCLUDED
