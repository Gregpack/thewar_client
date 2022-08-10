#include "your_ai.h"

std::string get_name() {
    return "Default Name";
}

bool has_built = false;
int counter = 0;

OrderMessage get_next_move(GameStateDto game_state, int player_id) {
    if (has_built) {
        return {};
    }
    auto player = game_state.players[std::to_string(player_id)];
    int xCoord = player.baseX + 1;
    int yCoord = player.baseY + 1;
    OrderMessage order_message = OrderMessage();
    BuildOrder buildOrder = BuildOrder();
    buildOrder.senderId = player_id;
    buildOrder.x = xCoord;
    buildOrder.y = yCoord;
    buildOrder.unitType = FOOTMAN;
    order_message.addOrder(buildOrder);
    has_built = true;
    return order_message;
}
