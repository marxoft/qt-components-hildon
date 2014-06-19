#ifndef ITEMDELEGATE_P_H
#define ITEMDELEGATE_P_H

#include "delegateitem_p.h"
#include <QStyledItemDelegate>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class ItemDelegatePrivate;

class ItemDelegate : public QStyledItemDelegate, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PRIVATE_PROPERTY(ItemDelegate::d_func(), QDeclarativeListProperty<QObject> data READ data)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ItemDelegate(QObject *parent = 0);
    ~ItemDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    ItemDelegate(ItemDelegatePrivate &dd, QObject *parent = 0);

    void classBegin();
    void componentComplete();

    QScopedPointer<ItemDelegatePrivate> d_ptr;

    Q_DISABLE_COPY(ItemDelegate)
    Q_DECLARE_PRIVATE(ItemDelegate)
};

QML_DECLARE_TYPE(ItemDelegate)

#endif // ITEMDELEGATE_P_H
