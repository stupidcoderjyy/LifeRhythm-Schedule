//
// Created by JYY on 24-10-26.
//

#ifndef RULEMANAGER_H
#define RULEMANAGER_H
#include <IOManager.h>
#include "Rule.h"

BEGIN_NAMESPACE(lr::schedule)

class RuleManager final : public AbstractLoader {
private:
    QMap<int, std::function<AbstractRule*()>> builders;
    QVector<AbstractRule*> rules;
public:
    RuleManager();
    void registerRuleBuilder(int type, const std::function<AbstractRule*()>& builder);
    void getSchedules(QVector<ScheduleItem>& list, const QDate& date);
protected:
    void load(IByteReader *in) override;
    void clear() override;
    void save(IByteWriter *out) override;
};

END_NAMESPACE

#endif //RULEMANAGER_H
