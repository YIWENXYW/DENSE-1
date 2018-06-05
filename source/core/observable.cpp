#include "observable.hpp"

void Observable::addObserver(Observer * observer) {
  if (observer == nullptr) return;
  observers_.emplace_back(*observer);
}

void Observable::notify(ContextBase& start) {
  for (Observer & observer : observers_) {
    observer.try_update(t, start);
  }
}

void Observable::finalize() {
  for (Observer & observer : observers_) {
    observer.finalize();
  }
}

Observer :: Observer(Observable *oAble, int mn, int mx,
                       RATETYPE startT, RATETYPE endT) :
    min(mn), max(mx), start_time(startT), end_time(endT), subject(oAble) {

    subject->addObserver(this);
}

bool Observer::accepts_updates_at_time(double t) const {
    return t >= start_time && t < end_time;
}

int Observer::getMin() const {
  return min;
}

void Observer::try_update(double t, ContextBase & begin) {
  if (!accepts_updates_at_time(t)) return;
  begin.set(getMin());
  update(begin);
}
