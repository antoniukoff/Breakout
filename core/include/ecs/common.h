#pragma once
#include <unordered_map>
#include <assert.h>
#include <bitset>
#include <vector>

using entity_id = std::size_t;
using component_instance = std::size_t;

constexpr size_t g_max_entities = 5000;
constexpr size_t g_container_size = g_max_entities + 1;

