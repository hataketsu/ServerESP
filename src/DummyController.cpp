//
// Created by hataketsu on 9/29/18.
//

#include "DummyController.h"

 String &DummyController::getName() const {
    return name;
}

void DummyController::setName(const String &name) {
    DummyController::name = name;
}

 byte *DummyController::getData() const {
    return data;
}

DummyController::DummyController() {
    name = "abc";
    for (unsigned char &i : data) {
        i = 0;
    }
}
