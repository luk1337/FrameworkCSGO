#ifndef SDK_RAYTRACE_DEFINITONS_MASKFLAGS
#define SDK_RAYTRACE_DEFINITONS_MASKFLAGS

#include "ContentFlags.hpp"

#define MASK_ALL (0xFFFFFFFF)
#define MASK_SOLID (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE)
#define MASK_PLAYERSOLID (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE)
#define MASK_NPCSOLID (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE)
#define MASK_NPCFLUID (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER)
#define MASK_WATER (CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME)
#define MASK_OPAQUE (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS (MASK_OPAQUE | CONTENTS_MONSTER)
#define MASK_BLOCKLOS (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS (MASK_BLOCKLOS | CONTENTS_MONSTER)
#define MASK_VISIBLE (MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS (MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX)
#define MASK_FLOORTRACE (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_DEBRIS)
#define MASK_WEAPONCLIPPING (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS)
#define MASK_SHOT_BRUSHONLY (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_DEBRIS)
#define MASK_SHOT_HULL (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE)
#define MASK_SHOT_PORTAL (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC_FLUID (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP)
#define MASK_SPLITAREAPORTAL (CONTENTS_WATER | CONTENTS_SLIME)

#define MASK_DEADSOLID (CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE)

#endif
