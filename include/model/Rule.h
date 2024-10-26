//
// Created by JYY on 24-10-26.
//

#ifndef RULE_H
#define RULE_H

#include <QDate>
#include "NBTSerializable.h"
#include "OpenRange.h"

struct ScheduleItem {
    QDateTime time;
    QString info;
    QString toString() const {
        return time.toString("yyyy-MM-dd hh:mm") + "  " + info;
    }
};

class AbstractRule : public NBTSerializable {
protected:
    int id;
    QString name;
public:
    explicit AbstractRule(int ruleId);
    virtual void getSchedules(QVector<ScheduleItem>& list, const QDate& date) = 0;
    NBT * toNbt() override;
    void fromNbt(NBT *nbt) override;
};

class WeeklyRule final : public AbstractRule {
public:
    struct Item {
        int weekDay;
        QTime time;
    };
private:
    QDate startDate;
    OpenRange range;
    QVector<Item> items;
public:
    WeeklyRule();
    void getSchedules(QVector<ScheduleItem>& list, const QDate& date) override;
    NBT * toNbt() override;
    void fromNbt(NBT *nbt) override;
};

class SingleRule final : public AbstractRule {
private:
    QDateTime time;
public:
    SingleRule();
    void getSchedules(QVector<ScheduleItem>& list, const QDate& date) override;
    NBT * toNbt() override;
    void fromNbt(NBT *nbt) override;
};

#endif //RULE_H
