#pragma once
namespace OBJ {
	enum TYPE{
		BULLET,
		MONSTER,
		PLAYER,
		MOUSE,
		ITEM,
		END
	};
}
namespace DIRECTION {
	enum class DIR {
		NORTH,
		NORTHEAST,
		EAST,
		SOUTHEAST,
		SOUTH,
		SOUTHWEST,
		WEST,
		NORTHWEST
	};
}