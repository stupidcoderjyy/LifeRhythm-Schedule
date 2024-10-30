//
// Created by JYY on 24-10-28.
//

#include "Sync.h"
#include "LifeRhythm.h"
#include "Task.h"

USING_NAMESPACE(lr::schedule)

void Sync::onScheduleItemsUpdated(QVector<ScheduleItem>* items) {
    LifeRhythm::get()->getMessageHandler().sendMessage(new MsgScheduleItemsUpdate(items));
}

MsgScheduleItemsUpdate::MsgScheduleItemsUpdate(QVector<ScheduleItem>* items): Message(LOC("schedule:items_update")), items(items) {
}

NBT * MsgScheduleItemsUpdate::buildData() {
    auto nbt = new NBT;
    auto arr = nbt->putArray("items");
    for (auto item : *items) {
        arr->add(item.toNbt());
    }
    return nbt;
}
