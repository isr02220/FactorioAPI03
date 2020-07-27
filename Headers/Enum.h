#pragma once
namespace OBJ {
	enum TYPE{
		RESOURCEORE,
		BELT,
		BELTEND,
		ENTITY,
		ITEM,
		PLAYER,
		MONSTER,
		BULLET,
		MONSTERBULLET,
		UI,
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
	enum class SUBGROUP{
		LOGISTICS_Storage,
		LOGISTICS_BeltTransport,
		LOGISTICS_Inserter,
		LOGISTICS_EnergyPipe,
		LOGISTICS_Transport,
		LOGISTICS_LogisticNetwork,
		LOGISTICS_CircuitNetwork,
		LOGISTICS_Terrain,
		PRODUCTION_Tool,
		PRODUCTION_Electricity,
		PRODUCTION_ResourceExtraction,
		PRODUCTION_Furnace,
		PRODUCTION_Production,
		PRODUCTION_Module,
		INTERMEDIATE_ResourceFluid,
		INTERMEDIATE_Material,
		INTERMEDIATE_CraftingComponents,
		INTERMEDIATE_SciencePack,
		COMBAT_Weapon,
		COMBAT_Ammo,
		COMBAT_Capsule,
		COMBAT_Armor,
		COMBAT_ArmorModule,
		COMBAT_Defense
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