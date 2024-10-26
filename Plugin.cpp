//
// Created by JYY on 24-10-21.
//

#include "Plugin.h"
#include <LifeRhythm.h>
#include "ModuleSchedule.h"

PLUGIN_ENTRYPOINT {
    USING_NAMESPACE(lr)
    LifeRhythm::get()->registerModule(new schedule::ModuleSchedule);
}