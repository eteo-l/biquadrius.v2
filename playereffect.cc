export module PlayerEffect;

import Player;

export class PlayerEffect {
    protected:
        int owner; // 0 or 1

    public:
        PlayerEffect(int p);
        virtual void apply(Player &p1, Player &p2) = 0;
};

export class BlindEffect : public PlayerEffect {
    public:
        BlindEffect(int p);
        void apply(Player &p1, Player &p2);
};

export class HeavyEffect : public PlayerEffect {
    public:
        HeavyEffect(int p);
        void apply(Player &p1, Player &p2);
};

export class ForceEffect : public PlayerEffect {
    char forcedType;
    public:
        ForceEffect(int p, char f);
        void apply(Player &p1, Player &p2);
};
