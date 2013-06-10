#include "player.h"
#include "back.h"
#include "enemy.h"
#include "pch.h"

class CONTROL{
private:
	PLAYER *player;
	BACK *back;
	ENEMY *enemy[ ENEMY_NUM ];

public:
	CONTROL();
	~CONTROL();
	void All();
};

