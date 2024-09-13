#include "EventManager.h"

EventManagerStatic eventManager;

// 전역 변수
unsigned int counter = 0;
bool toggle = false;

void setup() {
    Serial.begin(115200);

    // 1000ms 간격으로 "Hello, World!" 메시지 출력, 총 5번 실행
    eventManager.makeEvent(1000, []() {
        Serial.println("Hello, World!");
    }, 5);

    // 2000ms 간격으로 카운터 값 증가, 총 10번 실행
    eventManager.makeEvent(2000, []() {
        counter++;
        Serial.print("Counter: ");
        Serial.println(counter);
    }, 10);

    // 500ms 간격으로 LED 상태 토글 (여기서는 가상의 LED 상태를 시뮬레이션), 총 20번 실행
    eventManager.makeEvent(500, []() {
        toggle = !toggle;
        if (toggle) {
            Serial.println("LED ON");
        } else {
            Serial.println("LED OFF");
        }
    }, 20);
}

void loop() {
    eventManager.manageEvents();
}
