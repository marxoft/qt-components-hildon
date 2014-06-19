#include "itemdelegate_p.h"
#include "itemdelegate_p_p.h"
#include "itemdelegatetext_p.h"
#include <QPainter>

ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(new ItemDelegatePrivate(this))
{
}

ItemDelegate::ItemDelegate(ItemDelegatePrivate &dd, QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(&dd)
{
}

ItemDelegate::~ItemDelegate() {}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(index);
    Q_D(const ItemDelegate);

    foreach (QObject *obj, d->dataList) {
        if (ItemDelegateText *delegateText = qobject_cast<ItemDelegateText*>(obj)) {
            painter->drawText(option.rect, Qt::AlignCenter, delegateText->text());
        }
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}

void ItemDelegate::classBegin() {}

void ItemDelegate::componentComplete() {
    Q_D(ItemDelegate);

    d->componentComplete();
}

ItemDelegatePrivate::ItemDelegatePrivate(ItemDelegate *parent) :
    q_ptr(parent),
    complete(false)
{
}

ItemDelegatePrivate::~ItemDelegatePrivate() {}

void ItemDelegatePrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ItemDelegate *delegate = qobject_cast<ItemDelegate*>(list->object)) {
        delegate->d_func()->dataList.append(obj);
    }
}

QDeclarativeListProperty<QObject> ItemDelegatePrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ItemDelegatePrivate::data_append);
}

void ItemDelegatePrivate::componentComplete() {
    complete = true;
}

#include "moc_itemdelegate_p.cpp"
