export module PlayerEffect;

import Player;

export class PlayerEffect {
    protected:
        int owner; // 0 or 1

    public:
        PlayerEffect(int p);
        int getOwner();
        virtual void apply(Player &p1, Player &p2) = 0;
};

export class BlindEffect : public PlayerEffect {
    public:
        BlindEffect(int p);
        void apply(Player &p1, Player &p2);
};

//new
export class HeavyEffect : public PlayerEffect {
    bool dropped = false;
    public:
        HeavyEffect(int p);
        bool getDropped();
        void setDropped(bool d);
        void apply(Player &p1, Player &p2);
};

export class ForceEffect : public PlayerEffect {
    char forcedType;
    public:
        ForceEffect(int p, char f);
        void apply(Player &p1, Player &p2);
};
