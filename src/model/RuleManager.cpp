//
// Created by JYY on 24-10-26.
//

#include "RuleManager.h"
#include "MemUtil.h"

USING_NAMESPACE(lr::schedule)

RuleManager::RuleManager() {
    registerRuleBuilder(0, [] {
        return new WeeklyRule();
    });
    registerRuleBuilder(1, [] {
        return new SingleRule();
    });
}

void RuleManager::registerRuleBuilder(int type, const std::function<AbstractRule *()>& builder) {
    if (!builders.contains(type)) {
        builders.insert(type, builder);
    }
}

void RuleManager::getSchedules(QVector<ScheduleItem> &list, const QDate &date) {
    for (auto rule : rules) {
        rule->getSchedules(list, date);
    }
}

void RuleManager::load(IByteReader *in) {
    while (in->available()) {
        auto nbt = new NBT;
        nbt->deserialize(in);
        auto rule = builders.value(nbt->getInt("type"))();
        rule->fromNbt(nbt);
        rules << rule;
        delete nbt;
    }
}

void RuleManager::clear() {
    DELETE_LIST(rules)
}

void RuleManager::save(IByteWriter *out) {
    for (auto rule : rules) {
        auto nbt = rule->toNbt();
        nbt->serialize(out);
        delete nbt;
    }
}
