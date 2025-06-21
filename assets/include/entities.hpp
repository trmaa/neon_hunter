#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <vector>
#include "player.hpp"
#include "json.hpp"

extern eng::json g_json_read(std::string path);

extern Player g_player;
extern std::vector<eng::Entity*> g_entities;
extern std::vector<eng::LightSpot> g_lightspots;

extern void g_lightspots_push(eng::LightSpot lightspot);
extern void g_summon_entities();

#endif
