module Abstract;

void Subject::attach(Observer *o) {
    observers.push_back(o);
}

void Subject::detach(Observer *o) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), o),
        observers.end()
    );
}

void Subject::notify() {
    for (auto *o : observers) {
        if (o) o->update(*this);
    }
}
