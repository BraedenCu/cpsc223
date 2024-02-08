#pragma once
#include <stdbool.h>
#include <stdlib.h>

bool isAlive(int field[], size_t i, size_t size);

bool shouldDie(int field[], size_t i, size_t size);

void activate_cell(int field[], size_t i, size_t size);

void kill_cell(int field[], size_t i, size_t size);
