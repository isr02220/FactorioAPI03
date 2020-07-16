#pragma once
namespace OBJ {
	enum TYPE{
		ENTITY,
		PLAYER,
		ITEM,
		MONSTER,
		MOUSE,
		END
	};
}
namespace ITEM {
	enum class GROUP {
		LOGISTICS,
		PRODUCTION,
		INTERMEDIATE,
		COMBAT
	};
	enum class LOGISTICS{
		Storage,
		BeltTransport,
		Inserter,
		EnergyPipe,
		Transport,
		LogisticNetwork,
		CircuitNetwork,
		Terrain
	};
	enum class PRODUCTION{
		Tool,
		Electricity,
		ResourceExtraction,
		Furnace,
		Production,
		Module
	};
	enum class INTERMEDIATE{
		ResourceFluid,
		Material,
		CraftingComponents,
		SciencePack
	};
	enum class COMBAT{
		Weapon,
		Ammo,
		Capsule,
		Armor,
		ArmorModule,
		Defense
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