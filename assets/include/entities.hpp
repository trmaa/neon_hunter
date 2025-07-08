#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <vector>
#include "player.hpp"

extern Player g_player;
extern std::vector<eng::Entity*> g_entities;
extern std::vector<eng::LightSpot> g_lightspots;

extern void g_lightspots_push(eng::LightSpot lightspot);
extern void g_summon_entities();

#endif
