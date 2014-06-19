#ifndef ITEMDELEGATETEXT_P_H
#define ITEMDELEGATETEXT_P_H

#include "delegateitem_p.h"

class ItemDelegateTextPrivate;

class ItemDelegateText : public DelegateItem
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    ItemDelegateText(QObject *parent = 0);
    ~ItemDelegateText();

    QString text() const;
    void setText(const QString &text);

signals:
    void textChanged();

private:
    ItemDelegateText(ItemDelegateTextPrivate &dd, QObject *parent = 0);

    Q_DISABLE_COPY(ItemDelegateText)
    Q_DECLARE_PRIVATE(ItemDelegateText)
};

QML_DECLARE_TYPE(ItemDelegateText)

#endif // ITEMDELEGATETEXT_P_H
