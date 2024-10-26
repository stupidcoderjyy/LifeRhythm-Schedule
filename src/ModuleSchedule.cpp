//
// Created by JYY on 24-10-15.
//

#include "ModuleSchedule.h"

#include <IOManager.h>
#include <LifeRhythm.h>

USING_NAMESPACE(lr::schedule)

ModuleSchedule::ModuleSchedule(): Module("schedule") {
}

void ModuleSchedule::preInit() {
    auto lr = LifeRhythm::get();
    lr->getIOManager().registerSerializable(LOC("schedule:rules"), &ruleManager);
}
