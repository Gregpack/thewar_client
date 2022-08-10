
#ifndef JNI_CLIENT_YOUR_AI_H
#define JNI_CLIENT_YOUR_AI_H
#include "structures.h"

using namespace thewar;
using namespace thewar::basic;
using namespace thewar::enums;
using namespace thewar::dto;
using namespace thewar::actions;
using namespace thewar::orders;

OrderMessage get_next_move(GameStateDto& game_state, int player_id);
std::string get_name();

#endif //JNI_CLIENT_YOUR_AI_H
