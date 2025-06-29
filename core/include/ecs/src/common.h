#pragma once
#include <unordered_map>
#include <assert.h>
#include <bitset>
#include <vector>
#include <queue>

using entity_id = uint32_t;
using component_instance = uint32_t;

namespace reflecs
{
	extern const uint32_t g_max_entities;
	inline const uint32_t g_container_size = g_max_entities + 1;
}


