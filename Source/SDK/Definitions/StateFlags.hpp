#ifndef SDK_DEFINITION_STATEFLAGS
#define SDK_DEFINITION_STATEFLAGS

#define FL_ONGROUND (1 << 0)
#define FL_DUCKING (1 << 1)
#define FL_ANIMDUCKING (1 << 2)
#define FL_WATERJUMP (1 << 3)
#define FL_ONTRAIN (1 << 4)
#define FL_INRAIN (1 << 5)
#define FL_FROZEN (1 << 6)
#define FL_ATCONTROLS (1 << 7)
#define FL_CLIENT (1 << 8)
#define FL_FAKECLIENT (1 << 9)
#define FL_INWATER (1 << 10)

#define PLAYER_FLAG_BITS 11

#define FL_FLY (1 << 11)
#define FL_SWIM (1 << 12)
#define FL_CONVEYOR (1 << 13)
#define FL_NPC (1 << 14)
#define FL_GODMODE (1 << 15)
#define FL_NOTARGET (1 << 16)
#define FL_AIMTARGET (1 << 17)
#define FL_PARTIALGROUND (1 << 18)
#define FL_STATICPROP (1 << 19)
#define FL_GRAPHED (1 << 20)
#define FL_GRENADE (1 << 21)
#define FL_STEPMOVEMENT (1 << 22)
#define FL_DONTTOUCH (1 << 23)
#define FL_BASEVELOCITY (1 << 24)
#define FL_WORLDBRUSH (1 << 25)
#define FL_OBJECT (1 << 26)
#define FL_KILLME (1 << 27)
#define FL_ONFIRE (1 << 28)
#define FL_DISSOLVING (1 << 29)
#define FL_TRANSRAGDOLL (1 << 30)
#define FL_UNBLOCKABLE_BY_PLAYER (1 << 31)
#define FL_FREEZING (1 << 32)

#endif
