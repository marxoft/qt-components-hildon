#include "delegateitem_p.h"
#include "delegateitem_p_p.h"
#include <QEvent>

DelegateItem::DelegateItem(QObject *parent) :
    QObject(parent),
    d_ptr(new DelegateItemPrivate(this))
{
}

DelegateItem::DelegateItem(DelegateItemPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

DelegateItem::~DelegateItem() {}

int DelegateItem::x() const {
    Q_D(const DelegateItem);

    return d->x;
}

void DelegateItem::setX(int x) {
    if (x != this->x()) {
        Q_D(DelegateItem);
        d->x = x;
        emit xChanged();
    }
}

int DelegateItem::y() const {
    Q_D(const DelegateItem);

    return d->y;
}

void DelegateItem::setY(int y) {
    if (y != this->y()) {
        Q_D(DelegateItem);
        d->y = y;
        emit yChanged();
    }
}

int DelegateItem::width() const {
    Q_D(const DelegateItem);

    return d->width;
}

void DelegateItem::setFixedWidth(int width) {
    if (width != this->width()) {
        Q_D(DelegateItem);
        d->width = width;
        emit widthChanged();
    }
}

int DelegateItem::height() const {
    Q_D(const DelegateItem);

    return d->height;
}

void DelegateItem::setFixedHeight(int height) {
    if (height != this->height()) {
        Q_D(DelegateItem);
        d->height = height;
        emit heightChanged();
    }
}

bool DelegateItem::isVisible() const {
    Q_D(const DelegateItem);

    return d->visible;
}

void DelegateItem::setVisible(bool visible) {
    if (visible != this->isVisible()) {
        Q_D(DelegateItem);
        d->visible = visible;
    }
}

void DelegateItem::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }
}

DelegateItemPrivate::DelegateItemPrivate(DelegateItem *parent) :
    q_ptr(parent),
    x(0),
    y(0),
    width(0),
    height(0),
    visible(true)
{
}

DelegateItemPrivate::~DelegateItemPrivate() {}

#include "moc_delegateitem_p.cpp"
