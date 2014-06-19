#ifndef ITEMDELEGATETEXT_P_P_H
#define ITEMDELEGATETEXT_P_P_H

#include "delegateitem_p_p.h"
#include "itemdelegatetext_p.h"

class ItemDelegateTextPrivate : public DelegateItemPrivate
{

public:
    ItemDelegateTextPrivate(ItemDelegateText *parent);

    QString text;

    Q_DECLARE_PUBLIC(ItemDelegateText)
};

#endif // ITEMDELEGATETEXT_P_P_H
