#include "your_ai.h"

std::string get_name() {
    return "Default Name";
}

bool has_built = false;

OrderMessage get_next_move(GameStateDto game_state, int player_id) {
    if (has_built) {
        return {};
    }
    auto player = game_state.players[std::to_string(player_id)];
    int xCoord = player.baseX + 1;
    int yCoord = player.baseY + 1;
    OrderMessage order_message = OrderMessage();

    BuildOrder buildOrder = create_build_order(xCoord, yCoord, FOOTMAN);
    vector<UnitDto> units = get_my_units(game_state, player_id);

    buildOrder.x += 5;
    order_message.addOrder(buildOrder);
    has_built = true;
    return order_message;
}
