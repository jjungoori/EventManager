Markdown
---
layout: page
title: EventManager Library
---

# EventManager Library

EventManager는 Arduino 프로젝트를 위한 간단하고 효율적인 이벤트 관리 라이브러리입니다. 이 라이브러리는 정해진 간격으로 함수를 실행하거나, 비동기 작업을 쉽게 관리할 수 있게 해줍니다.

## 특징

- 간단한 API로 이벤트 생성 및 관리
- 동적 메모리 할당과 정적 메모리 할당 옵션 제공
- 반복 실행 이벤트 지원
- 이벤트 제거 기능

## 설치

1. 이 저장소를 클론하거나 ZIP 파일로 다운로드합니다.
2. Arduino IDE의 스케치 > 라이브러리 포함하기 > .ZIP 라이브러리 추가에서 다운로드한 파일을 선택합니다.

## 사용법

### 1. 라이브러리 포함

```cpp
#include "EventManager.h"
```

### 2. EventManager 객체 생성

동적 메모리 할당 버전:
```cpp
EventManagerDynamic eventManager;
```

정적 메모리 할당 버전:
```cpp
EventManagerStatic eventManager;
```

### 3. 이벤트 생성

```cpp
eventManager.makeEvent(1000, []() {
    // 1초마다 실행될 코드
}, 5);  // 5번 반복
```

### 4. 이벤트 관리

`loop()` 함수에서 `manageEvents()`를 호출합니다:

```cpp
void loop() {
    eventManager.manageEvents();
}
```

## 동적 vs 정적 메모리 할당

- **동적 메모리 할당** (`EventManagerDynamic`): 
  - 장점: 유연성, 이벤트 수에 제한 없음
  - 단점: 메모리 단편화 가능성, 실행 시간 예측 어려움

- **정적 메모리 할당** (`EventManagerStatic`):
  - 장점: 예측 가능한 메모리 사용, 일정한 실행 시간
  - 단점: 최대 이벤트 수 제한 (기본값: 20, `EventManager.h`에서 `MAX_EVENTS` 변경 가능)

임베디드 시스템에서는 일반적으로 정적 메모리 할당이 권장됩니다.

## 예제

라이브러리와 함께 제공되는 예제 파일을 참조하세요:
- `examples/DynamicAllocationExample/DynamicAllocationExample.ino`
- `examples/StaticAllocationExample/StaticAllocationExample.ino`

## 기여

버그 리포트, 기능 요청, 풀 리퀘스트를 환영합니다.

## 라이센스

이 프로젝트는 MIT 라이센스 하에 배포됩니다. 자세한 내용은 `LICENSE` 파일을 참조하세요.#   E v e n t M a n a g e r 
