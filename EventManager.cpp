#include "EventManager.h"
#include <Arduino.h> // for millis()

template<bool UseStatic>
EventManagerBase<UseStatic>::EventManagerBase() : world_time(0), world_hash(0), previousMillis(0), eventCount(0) {}

template<bool UseStatic>
int EventManagerBase<UseStatic>::makeEvent(int _delay, std::function<void()> _func, int _loopCount) {
    Event event;
    event.delay = _delay;
    event.func = _func;
    event.loopCount = _loopCount;
    event.hash = world_hash++;
    event.last = world_time;

    if constexpr (UseStatic) {
        if (eventCount < MAX_EVENTS) {
            events[eventCount] = event;
            return eventCount++;
        }
        return -1;  // 이벤트 추가 실패
    } else {
        events.push_back(event);
        return events.size() - 1;
    }
}

template<bool UseStatic>
void EventManagerBase<UseStatic>::manageEvents() {
    unsigned long currentMillis = getCurrentTime();
    
    if (currentMillis != previousMillis) {
        previousMillis = currentMillis;
        world_time++;

        size_t size = UseStatic ? eventCount : events.size();
        for (size_t i = 0; i < size; i++) {
            if (events[i].delay <= world_time - events[i].last) {
                events[i].func();
                events[i].last = world_time;
                if (--events[i].loopCount < 1) {
                    removeEvent(i);
                    i--;
                    size--;
                }
            }
        }
    }
}

template<bool UseStatic>
void EventManagerBase<UseStatic>::removeEvent(int index) {
    if constexpr (UseStatic) {
        if (index >= 0 && index < static_cast<int>(eventCount)) {
            for (size_t i = index; i < eventCount - 1; i++) {
                events[i] = events[i + 1];
            }
            eventCount--;
        }
    } else {
        if (index >= 0 && index < static_cast<int>(events.size())) {
            events.erase(events.begin() + index);
        }
    }
}

template<bool UseStatic>
unsigned long EventManagerBase<UseStatic>::getCurrentTime() {
    return millis();
}

// 명시적 템플릿 인스턴스화
template class EventManagerBase<true>;
template class EventManagerBase<false>;