#ifndef DELEGATEITEM_P_P_H
#define DELEGATEITEM_P_P_H

#include "delegateitem_p.h"

class DelegateItemPrivate
{

public:
    DelegateItemPrivate(DelegateItem *parent);
    virtual ~DelegateItemPrivate();

    DelegateItem *q_ptr;

    int x;
    int y;

    int width;
    int height;

    bool visible;

    Q_DECLARE_PUBLIC(DelegateItem)
};

#endif // DELEGATEITEM_P_P_H
