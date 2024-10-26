#include "LifeRhythm.h"
#include "ModuleSchedule.h"
#include <QDebug>

USING_NAMESPACE(lr)

int runLifeRhythm(int argc, char **argv) {
    LifeRhythm lr(argc, argv);
    lr.registerModule(new schedule::ModuleSchedule);
    return lr.launch();
}

int main(int argc, char* argv[]) {
    auto nbt = NBT::fromStringNbt("rules.txt");
    qDebug() << nbt->toString();
    auto rule = WeeklyRule();
    rule.fromNbt(nbt);
    qDebug() << rule.toNbt()->toString();
}
