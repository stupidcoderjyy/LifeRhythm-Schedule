//
// Created by JYY on 24-10-28.
//

#ifndef SYNCHANDLER_H
#define SYNCHANDLER_H

#include <MessageHandler.h>
#include <Namespaces.h>
#include <QVector>
#include "Rule.h"

BEGIN_NAMESPACE(lr::schedule)

class Sync {
public:
    static void onScheduleItemsUpdated(QVector<ScheduleItem>* items);
};

class MsgScheduleItemsUpdate final : public Message {
private:
    QVector<ScheduleItem>* items;
public:
    explicit MsgScheduleItemsUpdate(QVector<ScheduleItem>* items);
    NBT * buildData() override;
};

END_NAMESPACE

#endif //SYNCHANDLER_H
