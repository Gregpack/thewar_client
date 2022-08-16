//
// Created by Gregpack on 16.08.2022.
//

#ifndef JNI_CLIENT_HELP_FUNCTIONS_H
#define JNI_CLIENT_HELP_FUNCTIONS_H

#include "structures.h"

using namespace thewar;
using namespace thewar::basic;
using namespace thewar::enums;
using namespace thewar::dto;
using namespace thewar::actions;
using namespace thewar::orders;

vector<UnitDto> get_enemy_units(GameStateDto gameStateDto, int player_id);

vector<UnitDto> get_my_units(GameStateDto gameStateDto, int player_id);

PlayerDto get_player(GameStateDto gameStateDto, int player_id);

vector<BarrackDto> get_my_barracks(GameStateDto gameStateDto, int player_id);

vector<BarrackDto> get_enemy_barracks(GameStateDto gameStateDto, int player_id);

UnitDto get_unit(GameStateDto &gameStateDto, int unit_id);

BarrackDto get_barrack(GameStateDto &gameStateDto, int barrack_id);

BarrackDto get_barrack(vector<BarrackDto> &barracks, int barrack_id);

UnitDto get_unit(vector<UnitDto> &units, int unit_id);

bool is_empty(GameStateDto &gameStateDto, int x, int y);

bool is_empty_for_barrack(GameStateDto &gameStateDto, int x, int y);

BuildOrder create_build_order(int x, int y, UnitType unit_type);

AttackOrder create_attack_order(int attacker_id, int attacked_id);

MoveOrder create_move_order(int unit_id, Direction where);

SkillOrder create_skill_order(int unit_id, int x, int y);

DestroyOrder create_destroy_order(int barrack_id);

StayStillOrder create_stay_order(int unit_id);

vector<UnitDto> get_enemies_in_range(GameStateDto &gameStateDto, int unit_id);

#endif //JNI_CLIENT_HELP_FUNCTIONS_H
