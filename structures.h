#include <string>
#include <vector>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>
#include <memory>
#include <variant>

namespace thewar {
    namespace basic {
        struct Armor {
            enum ArmorType {
                Light,
                Normal,
                Heavy
            };
            int armorAmount;
            ArmorType armorType;
        };

        struct Attack {
            enum AttackType {
                Normal,
                Sharp,
                Fire
            };
            int attackPower;
            int attackRange;
            int attackCooldown;
            AttackType attackType;
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(Attack::AttackType, {
            { Attack::AttackType::Normal, "Normal" },
            { Attack::AttackType::Sharp, "Sharp" },
            { Attack::AttackType::Fire, "Fire" }
        })

        NLOHMANN_JSON_SERIALIZE_ENUM(Armor::ArmorType, {
            { Armor::ArmorType::Light, "Light" },
            { Armor::ArmorType::Normal, "Normal" },
            { Armor::ArmorType::Heavy, "Heavy" }
        })

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Armor, armorAmount, armorType)

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Attack, attackPower, attackRange, attackCooldown, attackType)
    }
    namespace enums {
        enum GameStatus {
            IN_PROGRESS,
            END
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(GameStatus, {
            { IN_PROGRESS, "IN_PROGRESS" },
            { END, "END" }
        })

        enum UnitType {
            FOOTMAN,
            ARCHER,
            ALCHEMIST,
            ASSASSIN,
            CAVALRY
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(UnitType, {
            { FOOTMAN, "FOOTMAN" },
            { ARCHER, "ARCHER" },
            { ALCHEMIST, "ALCHEMIST" },
            { ASSASSIN, "ASSASSIN" },
            { CAVALRY, "CAVALRY" },
        })

        enum Behaviour {
            DEFAULT,
            BATTLE_EXPECTED,
            BATTLE
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(Behaviour, {
            { DEFAULT, "DEFAULT" },
            { BATTLE_EXPECTED, "BATTLE_EXPECTED" },
            { BATTLE, "BATTLE" }
        })

        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
            { UP, "UP" },
            { DOWN, "DOWN" },
            { LEFT, "LEFT" },
            { RIGHT, "RIGHT" }
        })
    }
    namespace actions {
        struct AttackAction {
            int performerId;
            int attackedId;
        };
        struct MoveAction {
            int performerId;
            int startX;
            int startY;
            int toX;
            int toY;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AttackAction, performerId, attackedId)

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MoveAction, performerId, startX, startY, toX, toY)
    }
    namespace dto {
        struct PlayerDto {
            int id;
            int money;
            std::string name;
            int baseX;
            int baseY;
        };

        inline void to_json(nlohmann::json &nlohmann_json_j, const PlayerDto &nlohmann_json_t) {
            nlohmann_json_j["id"] = nlohmann_json_t.id;
            nlohmann_json_j["money"] = nlohmann_json_t.money;
            nlohmann_json_j["name"] = nlohmann_json_t.name;
            nlohmann_json_j["baseX"] = nlohmann_json_t.baseX;
            nlohmann_json_j["baseY"] = nlohmann_json_t.baseY;
        }

        inline void from_json(const nlohmann::json &nlohmann_json_j, PlayerDto &nlohmann_json_t) {
            if (nlohmann_json_j.is_null()) {
                nlohmann_json_t.id = -1;
                return;
            }
            nlohmann_json_j.at("id").get_to(nlohmann_json_t.id);
            nlohmann_json_j.at("money").get_to(nlohmann_json_t.money);
            nlohmann_json_j.at("name").get_to(nlohmann_json_t.name);
            nlohmann_json_j.at("baseX").get_to(nlohmann_json_t.baseX);
            nlohmann_json_j.at("baseY").get_to(nlohmann_json_t.baseY);
        }

        struct BarrackDto {
            int id;
            int x;
            int y;
            int spawnX;
            int spawnY;
            int playerId;
            enums::UnitType unitType;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BarrackDto, id, x, y, spawnX, spawnY, playerId, unitType)

        struct UnitDto {
            int id;
            int x;
            int y;
            double healthPoints;
            double totalHealthPoints;
            int moneyWorth;
            int speed;
            basic::Attack attack;
            basic::Armor armor;
            enums::Behaviour currentBehaviour;
            int behaviourTriggerUnitId;
            enums::UnitType unitType;
            int playerId;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UnitDto, id, x, y, healthPoints, totalHealthPoints, moneyWorth, speed,
                                           attack, armor, currentBehaviour, behaviourTriggerUnitId,
                                           unitType, playerId)
    }
    namespace orders {
        struct SkillActivator {
            int x;
            int y;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SkillActivator, x, y)

        class BuildOrder {
        public:
            int senderId;
            int x;
            int y;
            enums::UnitType unitType;
            std::string type = "BuildOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BuildOrder, senderId, x, y, unitType, type)

        class DestroyOrder {
        public:
            int senderId;
            int barrackId;
            std::string type = "DestroyOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DestroyOrder, senderId, barrackId, type)

        class AttackOrder {
        public:
            int senderId;
            int unitId;
            int attackedId;
            std::string type = "AttackOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AttackOrder, unitId, senderId, attackedId, type)

        class MoveOrder {
        public:
            int senderId;
            int unitId;
            enums::Direction direction;
            std::string type = "MoveOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MoveOrder, unitId, senderId, direction, type)

        class SkillOrder {
        public:
            int senderId;
            int unitId;
            SkillActivator skillActivator;
            std::string type = "SkillOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SkillOrder, unitId, senderId, skillActivator, type)

        class StayStillOrder {
        public:
            int senderId;
            int unitId;
            std::string type = "StayStillOrder";
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StayStillOrder, unitId, senderId, type)

    }
    using namespace dto;
    using namespace orders;
    using namespace std;
    struct GameStateDto {
        map<string, BarrackDto> barracks;
        map<string, UnitDto> units;
        map<string, PlayerDto> players;
        vector<actions::AttackAction> attackActions;
        vector<actions::MoveAction> moveActions;
        vector<vector<int>> field;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameStateDto, barracks, units, players, attackActions, moveActions, field)

    struct GameStatusMessage {
        GameStateDto gameState;
        enums::GameStatus gameStatus;
        PlayerDto gameWinner;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameStatusMessage, gameState, gameStatus, gameWinner)

    class OrderMessage {
    public:
        vector<variant<BuildOrder, AttackOrder, MoveOrder, SkillOrder, DestroyOrder, StayStillOrder>> orders;

        void addOrder(BuildOrder order) {
            this->orders.emplace_back(order);
        }

        void addOrder(AttackOrder order) {
            this->orders.emplace_back(order);
        }

        void addOrder(MoveOrder order) {
            this->orders.emplace_back(order);
        }

        void addOrder(SkillOrder order) {
            this->orders.emplace_back(order);
        }

        void addOrder(DestroyOrder order) {
            this->orders.emplace_back(order);
        }

        void addOrder(StayStillOrder order) {
            this->orders.emplace_back(order);
        }

    };

    inline void to_json(nlohmann::json &nlohmann_json_j, const OrderMessage &nlohmann_json_t) {
        auto json_array = nlohmann::json::array();
        for (const auto &item: nlohmann_json_t.orders) {
            std::string value;
            if (const auto p = std::get_if<orders::BuildOrder>(&item)) {
                json_array.push_back(*p);
            } else if (const auto p1 = std::get_if<orders::AttackOrder>(&item)) {
                json_array.push_back(*p1);
            } else if (const auto p2 = std::get_if<orders::MoveOrder>(&item)) {
                json_array.push_back(*p2);
            } else if (const auto p3 = std::get_if<orders::SkillOrder>(&item)) {
                json_array.push_back(*p3);
            } else if (const auto p4 = std::get_if<orders::StayStillOrder>(&item)) {
                json_array.push_back(*p4);
            } else if (const auto p5 = std::get_if<orders::DestroyOrder>(&item)) {
                json_array.push_back(*p5);
            }
        }
        nlohmann_json_j["orders"] = json_array;
    }

    inline void from_json(const nlohmann::json &nlohmann_json_j, OrderMessage &nlohmann_json_t) {
        // never going to happen lulw
    }

}