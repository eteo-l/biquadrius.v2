export module Abstract;

import <vector>;
import <algorithm>;

// Forward declarations inside the SAME module.
export class Subject;
export class Observer;

// Observer interface
export class Observer {
public:
    virtual void update(Subject &whoNotified) = 0;
    virtual ~Observer() = default;
};

// Subject base
export class Subject {
    std::vector<Observer*> observers; // non-owning
public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notify();
    virtual ~Subject() = default;
};
