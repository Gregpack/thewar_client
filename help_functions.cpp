//
// Created by Gregpack on 16.08.2022.
//

#include "help_functions.h"

#define EMPTY_CELL -1
vector<pair<int, int>> roundCoord = vector<pair<int, int>>{pair<int, int>(-1, 1), pair<int, int>(1, 1),
                                                           pair<int, int>(-1, -1), pair<int, int>(1, -1)};

vector<UnitDto> get_enemy_units(GameStateDto &gameStateDto, int player_id) {
    vector<UnitDto> units = vector<UnitDto>();
    for (const auto &item: gameStateDto.units) {
        UnitDto unit = item.second;
        if (unit.playerId != player_id) {
            units.push_back(unit);
        }
    }
    return units;
}

vector<UnitDto> get_my_units(GameStateDto &gameStateDto, int player_id) {
    vector<UnitDto> units = vector<UnitDto>();
    for (const auto &item: gameStateDto.units) {
        UnitDto unit = item.second;
        if (unit.playerId == player_id) {
            units.push_back(unit);
        }
    }
    return units;
}

vector<BarrackDto> get_my_barracks(GameStateDto &gameStateDto, int player_id) {
    vector<BarrackDto> barracks = vector<BarrackDto>();
    for (const auto &item: gameStateDto.barracks) {
        BarrackDto barrackDto = item.second;
        if (barrackDto.playerId == player_id) {
            barracks.push_back(barrackDto);
        }
    }
    return barracks;
}

vector<BarrackDto> get_enemy_barracks(GameStateDto &gameStateDto, int player_id) {
    vector<BarrackDto> barracks = vector<BarrackDto>();
    for (const auto &item: gameStateDto.barracks) {
        BarrackDto barrackDto = item.second;
        if (barrackDto.playerId != player_id) {
            barracks.push_back(barrackDto);
        }
    }
    return barracks;
}

PlayerDto get_player(GameStateDto &gameStateDto, int player_id) {
    return gameStateDto.players[std::to_string(player_id)];
}

UnitDto get_unit(vector<UnitDto> &units, int unit_id) {
    for (const auto &item: units) {
        if (item.id == unit_id) {
            return item;
        }
    }
    return {};
}

BarrackDto get_barrack(vector<BarrackDto> &barracks, int barrack_id) {
    for (const auto &item: barracks) {
        if (item.id == barrack_id) {
            return item;
        }
    }
    return {};
}

UnitDto get_unit(GameStateDto &gameStateDto, int unit_id) {
    return gameStateDto.units[std::to_string(unit_id)];
}


BarrackDto get_barrack(GameStateDto &gameStateDto, int barrack_id) {
    return gameStateDto.barracks[std::to_string(barrack_id)];
}

bool is_empty(GameStateDto &gameStateDto, int x, int y) {
    return gameStateDto.field[y][x] == EMPTY_CELL;
}

bool is_empty_for_barrack(GameStateDto &gameStateDto, int x, int y) {
    int xOffset = 0, yOffset = 0;
    for (; yOffset < 3; yOffset++) {
        for (; xOffset < 3; xOffset++) {
            if (gameStateDto.field[y + yOffset][x + xOffset] != EMPTY_CELL) {
                return false;
            }
        }
    }
    return true;
}


BuildOrder create_build_order(int x, int y, UnitType unit_type) {
    return {.x = x, .y = y, .unitType = unit_type};
}

AttackOrder create_attack_order(int attacker_id, int attacked_id) {
    return {.unitId = attacker_id, .attackedId = attacked_id};
}

MoveOrder create_move_order(int unit_id, Direction where) {
    return {.unitId = unit_id, .direction = where};
}

SkillOrder create_skill_order(int unit_id, int x, int y) {
    SkillActivator skillActivator = {.x = x, .y = y};
    return {.unitId = unit_id, .skillActivator = skillActivator};
}

DestroyOrder create_destroy_order(int barrack_id) {
    return {.barrackId = barrack_id};
}

StayStillOrder create_stay_order(int unit_id) {
    return {.unitId = unit_id};
}

vector<UnitDto> get_enemies_in_range(GameStateDto &gameStateDto, int unit_id) {
    vector<UnitDto> enemies = vector<UnitDto>();
    UnitDto unit = get_unit(gameStateDto, unit_id);
    int positionY = unit.y;
    int positionX = unit.x;
    auto &field = gameStateDto.field;
    for (int i = 1; i <= unit.attack.attackRange; i++) {
        int startX = positionX + i;
        int startY = positionY;
        for (const auto& coordinate: roundCoord) {
            for (int j = 0; j < i; j++) {
                if (startX >= 0 && startY >= 0 && startX < 90 && startY < 20 && field[startY][startX] != -1) {
                    UnitDto enemy = get_unit(gameStateDto, field[startY][startX]);
                    if (enemy.playerId != unit.playerId) {
                        enemies.push_back(enemy);
                    }
                }
                startX += coordinate.first;
                startY += coordinate.second;
            }
        }
    }
    return enemies;
}
