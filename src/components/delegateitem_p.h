#ifndef DELEGATEITEM_P_H
#define DELEGATEITEM_P_H

#include <QObject>
#include <qdeclarative.h>

class DelegateItemPrivate;

class DelegateItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

public:
    DelegateItem(QObject *parent = 0);
    ~DelegateItem();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int width() const;
    void setFixedWidth(int width);

    int height() const;
    void setFixedHeight(int height);

    bool isVisible() const;
    void setVisible(bool visible);

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();

protected:
    DelegateItem(DelegateItemPrivate &dd, QObject *parent = 0);

    virtual void changeEvent(QEvent *event);

    QScopedPointer<DelegateItemPrivate> d_ptr;

    Q_DISABLE_COPY(DelegateItem)
    Q_DECLARE_PRIVATE(DelegateItem)
};

QML_DECLARE_TYPE(DelegateItem)

#endif // DELEGATEITEM_P_H
