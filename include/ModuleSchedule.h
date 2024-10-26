//
// Created by JYY on 24-10-15.
//

#ifndef MODULESCHEDULE_H
#define MODULESCHEDULE_H

#include "Module.h"
#include "Namespaces.h"
#include "RuleManager.h"

BEGIN_NAMESPACE(lr::schedule)

class ModuleSchedule final : public Module {
private:
    RuleManager ruleManager;
public:
    ModuleSchedule();
protected:
    void preInit() override;
};

END_NAMESPACE

#endif //MODULESCHEDULE_H
