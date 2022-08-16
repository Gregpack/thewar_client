
#ifndef JNI_CLIENT_YOUR_AI_H
#define JNI_CLIENT_YOUR_AI_H
#include "help_functions.h"

OrderMessage get_next_move(GameStateDto game_state, int player_id);
std::string get_name();

#endif //JNI_CLIENT_YOUR_AI_H
