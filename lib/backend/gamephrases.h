#ifndef GAMEPHRASES_H
#define GAMEPHRASES_H

#include <string>

enum Phrases {
    FIREBALL_ACTIVATED_PHRASE,
    DESTAURA_ACTIVATED_PHRASE,
    LEVEL_UP_PHRASE,
    SKILL_COOLDOWN_PHRASE,
    NEW_ENEMY_PHRASE
};

struct GamePhrases {
    static std::string gameEventPhrases[];
};

std::string GamePhrases::gameEventPhrases[] = {
    std::string("FIREBALL ACTIVATED!"), // When the user presses the useFireballButton
    std::string("DESTRUCTION AURA ACTIVATED"), // When the user presses the useDestructionAuraButton
    std::string("YOU LEVELED UP!"), // When Liesel levels up
    std::string("SKILL IS ON COOLDOWN"), // Whem the user tries to use a skill that is on cooldown
    std::string("A NEW ENEMY APPEARS!")
};

#endif // GAMEPHRASES_H
