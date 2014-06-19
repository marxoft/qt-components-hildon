#ifndef LISTSELECTOR_P_P_H
#define LISTSELECTOR_P_P_H

#include "valueselector_p_p.h"
#include "listselector_p.h"

class VariantListModel;

class ListSelectorPrivate : public ValueSelectorPrivate
{

public:
    ListSelectorPrivate(ListSelector *parent) :
        ValueSelectorPrivate(parent),
        variantModel(0),
        modelColumn(0),
        currentIndex(0)
    {
    }

    QVariant modelVariant;

    VariantListModel *variantModel;

    int modelColumn;

    int currentIndex;

    Q_DECLARE_PUBLIC(ListSelector)
};

#endif // LISTSELECTOR_P_P_H
