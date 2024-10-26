//
// Created by JYY on 24-10-27.
//

#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <Namespaces.h>
#include <TickHandler.h>
#include "Rule.h"

class RuleManager;

BEGIN_NAMESPACE(lr::schedule)

class ScheduleManager final : public ITickListener {
private:
    QDate today;
    QVector<ScheduleItem> items;
    RuleManager* ruleManager;
public:
    explicit ScheduleManager(RuleManager* ruleManager);
    void update(const QDateTime &now) override;
};

END_NAMESPACE

#endif //SCHEDULEMANAGER_H
