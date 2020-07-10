#pragma once
namespace OBJ {
	enum ID{
		FLOOR,
		BULLET,
		SUBBULLET,
		BOMB,
		MONSTERBULLET,
		MONSTER,
		PLAYER,
		MOUSE,
		ITEM,
		END
	};
}
namespace BOSSPATTERN {
	enum ID {
		FIRST,
		SECOND,
		LAST,
		END
	};
	enum MOVEMENT {
		FIRST_MOVE01,
		FIRST_MOVE02,
		FIRST_MOVE03,
	};
}
namespace MONSTER {
	enum ID {
		NUT,
		BIRD,
		HRING,
		VRING,
		BONG,
		REDGIRL,
		BOSS,
		SOLDIER,
		TANK,
		HELICOPTER,
		END
	};
}
namespace ITEM {
	enum ID {
		HEAVYMACHINEGUN,
		SHOTGUN,
		BOMBITEM,
		NORMAL,
		END
	};
}