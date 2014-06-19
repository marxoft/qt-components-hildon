#include "itemdelegatetext_p.h"
#include "itemdelegatetext_p_p.h"

ItemDelegateText::ItemDelegateText(QObject *parent) :
    DelegateItem(*new ItemDelegateTextPrivate(this), parent)
{
}

ItemDelegateText::ItemDelegateText(ItemDelegateTextPrivate &dd, QObject *parent) :
    DelegateItem(dd, parent)
{
}

ItemDelegateText::~ItemDelegateText() {}

QString ItemDelegateText::text() const {
    Q_D(const ItemDelegateText);

    return d->text;
}

void ItemDelegateText::setText(const QString &text) {
    if (text != this->text()) {
        Q_D(ItemDelegateText);
        d->text = text;
        emit textChanged();
    }
}

ItemDelegateTextPrivate::ItemDelegateTextPrivate(ItemDelegateText *parent) :
    DelegateItemPrivate(parent)
{
}

#include "moc_itemdelegatetext_p.cpp"
