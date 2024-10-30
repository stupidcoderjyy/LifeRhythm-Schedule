//
// Created by JYY on 24-10-26.
//

#include "Rule.h"
#include <utility>

USING_NAMESPACE(lr::schedule)

ScheduleItem::ScheduleItem(QDateTime time, QString info) : time(std::move(time)), info(std::move(info)) {}

NBT * ScheduleItem::toNbt() {
    auto nbt = new NBT;
    nbt->putString("info")->setVal(info);
    nbt->putLong("time")->setVal(time.toTime_t());
    return nbt;
}

void ScheduleItem::fromNbt(NBT *nbt) {
    info = nbt->getString("info");
    time = QDateTime::fromTime_t(nbt->getLong("time"));
}

AbstractRule::AbstractRule(int ruleId): id(ruleId) {
}

NBT * AbstractRule::toNbt() {
    auto nbt = new NBT();
    nbt->putInt("id")->setVal(id);
    nbt->putString("name")->setVal(name);
    return nbt;
}

void AbstractRule::fromNbt(NBT *nbt) {
    id = nbt->getInt("id");
    name = nbt->getString("name");
}

WeeklyRule::WeeklyRule(): AbstractRule(0) {
}

void WeeklyRule::getSchedules(QVector<ScheduleItem> &list, const QDate &date) {
    qint64 days = startDate.daysTo(date);
    int period = static_cast<int>(days / 7);
    if (!range.contains(period)) {
        return;
    }
    QDate weekBegin = startDate.addDays(period * 7);
    for (const auto&[weekDay, time] : items) {
        QDate target = weekBegin.addDays(weekDay);
        if (date == target) {
            list.append({{target, time}, name});
        }
    }
}

#define DATE_2_INT(d) (d.year() << 12 | d.month() << 8 | d.day())
#define INT_2_DATE(i) QDate(i >> 12, (i >> 8) & 0xf, i & 0xff)

NBT * WeeklyRule::toNbt() {
    auto nbt = AbstractRule::toNbt();
    nbt->putString("range")->setVal(range.toString());
    nbt->putInt("start")->setVal(DATE_2_INT(startDate));
    auto arr = nbt->putArray("items");
    for (const auto&[weekDay, time] : items) {
        auto child = new NBT;
        child->putInt("weekday")->setVal(weekDay);
        child->putInt("time")->setVal(time.msecsSinceStartOfDay());
        arr->add(child);
    }
    return nbt;
}

void WeeklyRule::fromNbt(NBT *nbt) {
    AbstractRule::fromNbt(nbt);
    range = OpenRange::fromString(nbt->getString("range"));
    startDate = INT_2_DATE(nbt->getInt("start"));
    auto arr = nbt->getArr("items");
    for (auto d : *arr) {
        auto child = d->asCompound();
        Item ri;
        ri.weekDay = child->getInt("weekday");
        ri.time = QTime::fromMSecsSinceStartOfDay(child->getInt("time"));
        items << ri;
    }
}

SingleRule::SingleRule(): AbstractRule(1) {
}

void SingleRule::getSchedules(QVector<ScheduleItem> &list, const QDate &date) {
    if (date == time.date()) {
        list.append({time, name});
    }
}

NBT * SingleRule::toNbt() {
    auto nbt = AbstractRule::toNbt();
    nbt->putLong("time")->setVal(time.toTime_t());
    return nbt;
}

void SingleRule::fromNbt(NBT *nbt) {
    AbstractRule::fromNbt(nbt);
    time = QDateTime::fromTime_t(nbt->getLong("time"));
}
