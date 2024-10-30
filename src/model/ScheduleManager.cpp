//
// Created by JYY on 24-10-27.
//

#include "ScheduleManager.h"
#include "RuleManager.h"
#include "Sync.h"

USING_NAMESPACE(lr::schedule)

ScheduleManager::ScheduleManager(RuleManager *ruleManager): ruleManager(ruleManager) {
}

void ScheduleManager::update(const QDateTime &now) {
    if (now.date() != today) {
        items = {};
        today = now.date();
        ruleManager->getSchedules(items, today);
        Sync::onScheduleItemsUpdated(&items);
    }
}
