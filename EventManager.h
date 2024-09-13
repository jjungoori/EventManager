#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <functional>
#include <vector>

#define MAX_EVENTS 20  // 정적 배열의 최대 크기를 정의합니다

struct Event {
    std::function<void()> func;
    unsigned int hash;
    unsigned int delay;
    int loopCount;
    unsigned int last;
};

template<bool UseStatic>
class EventManagerBase {
  public:
    EventManagerBase();
    int makeEvent(int delay, std::function<void()> func, int loopCount = 1);
    void manageEvents();
    void removeEvent(int index);

  private:
    unsigned int world_time;
    unsigned int world_hash;
    unsigned long previousMillis;
    unsigned long getCurrentTime();

    typename std::conditional<UseStatic, 
        Event[MAX_EVENTS],
        std::vector<Event>
    >::type events;
    
    size_t eventCount;  // 정적 배열에서 현재 이벤트 수를 추적
};

using EventManagerDynamic = EventManagerBase<false>;
using EventManagerStatic = EventManagerBase<true>;

#endif // EVENTMANAGER_H