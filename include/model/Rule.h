//
// Created by JYY on 24-10-26.
//

#ifndef RULE_H
#define RULE_H

#include <Namespaces.h>
#include <QDate>
#include "NBTSerializable.h"
#include "OpenRange.h"

BEGIN_NAMESPACE(lr::schedule)

struct ScheduleItem : public NBTSerializable {
    QDateTime time;
    QString info;
    ScheduleItem(QDateTime time, QString info);
    NBT * toNbt() override;
    void fromNbt(NBT *nbt) override;
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

END_NAMESPACE

#endif //RULE_H
