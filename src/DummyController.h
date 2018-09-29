//
// Created by hataketsu on 9/29/18.
//

#ifndef SERVERESP_DUMMYCONTROLLER_H
#define SERVERESP_DUMMYCONTROLLER_H

static const int DATA_SIZE = 100;

#include "Arduino.h"

class DummyController {
public:
    String &getName() const;

    void setName(const String &name);

    byte *getData() const;

private:
    byte data[DATA_SIZE];
    String name;
public:
    DummyController();

};


#endif //SERVERESP_DUMMYCONTROLLER_H
