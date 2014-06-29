#ifndef MULTILISTSELECTOR_P_P_H
#define MULTILISTSELECTOR_P_P_H

#include "valueselector_p_p.h"
#include "multilistselector_p.h"

class VariantListModel;

class MultiListSelectorPrivate : public ValueSelectorPrivate
{

public:
    MultiListSelectorPrivate(MultiListSelector *parent) :
        ValueSelectorPrivate(parent),
        dialog(0),
        variantModel(0),
        modelColumn(0),
        currentIndex(0)
    {
    }

    MultiListPickDialog *dialog;

    QVariant modelVariant;

    VariantListModel *variantModel;

    int modelColumn;

    int currentIndex;

    Q_DECLARE_PUBLIC(MultiListSelector)
};

#endif // MULTILISTSELECTOR_P_P_H
