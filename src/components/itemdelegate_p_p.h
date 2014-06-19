#ifndef ITEMDELEGATE_P_P_H
#define ITEMDELEGATE_P_P_H

#include "itemdelegate_p.h"

class ItemDelegatePrivate
{

public:
    ItemDelegatePrivate(ItemDelegate *parent);
    virtual ~ItemDelegatePrivate();

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    virtual QDeclarativeListProperty<QObject> data();

    virtual void componentComplete();

    ItemDelegate *q_ptr;

    bool complete;

    QList<QObject*> dataList;

    QList<DelegateItem*> visualDataList;

    Q_DECLARE_PUBLIC(ItemDelegate)
};

#endif // ITEMDELEGATE_P_P_H
