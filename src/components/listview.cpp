/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "listview_p.h"
#include "listview_p_p.h"
#include "variantlistmodel_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QScrollBar>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QGraphicsOpacityEffect>
#include <QTimer>

ListView::ListView(QWidget *parent) :
    QListView(parent),
    d_ptr(new ListViewPrivate(this))
{
    Q_D(ListView);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
}

ListView::ListView(ListViewPrivate &dd, QWidget *parent) :
    QListView(parent),
    d_ptr(&dd)
{
    Q_D(ListView);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
}

ListView::~ListView() {}

void ListView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ListView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal ListView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void ListView::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine ListView::left() const {
    Q_D(const ListView);

    return d->left;
}

AnchorLine ListView::right() const {
    Q_D(const ListView);

    return d->right;
}

AnchorLine ListView::top() const {
    Q_D(const ListView);

    return d->top;
}

AnchorLine ListView::bottom() const {
    Q_D(const ListView);

    return d->bottom;
}

AnchorLine ListView::horizontalCenter() const {
    Q_D(const ListView);

    return d->horizontalCenter;
}

AnchorLine ListView::verticalCenter() const {
    Q_D(const ListView);

    return d->verticalCenter;
}

bool ListView::interactive() const {
    Q_D(const ListView);

    return d->kineticScroller->isEnabled();
}

void ListView::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(ListView);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool ListView::moving() const {
    Q_D(const ListView);

    if (d->scrollTimer->isActive()) {
        return true;
    }

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool ListView::atXBeginning() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->minimum();
}

bool ListView::atXEnd() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum();
}

bool ListView::atYBeginning() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->minimum();
}

bool ListView::atYEnd() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->maximum();
}

int ListView::contentX() const {
    return this->horizontalScrollBar()->value();
}

void ListView::setContentX(int x) {
    this->horizontalScrollBar()->setValue(x);
}

int ListView::contentY() const {
    return this->horizontalScrollBar()->value();
}

void ListView::setContentY(int y) {
    this->verticalScrollBar()->setValue(y);
}

qreal ListView::flickDeceleration() const {
    Q_D(const ListView);

    return d->kineticScroller->decelerationFactor();
}

void ListView::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(ListView);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal ListView::maximumFlickVelocity() const {
    Q_D(const ListView);

    return d->kineticScroller->maximumVelocity();
}

void ListView::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(ListView);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

void ListView::positionViewAtBeginning() {
    if (this->model()) {
        this->scrollTo(this->model()->index(0, 0, this->rootIndex()), QListView::PositionAtTop);
    }
}

void ListView::positionViewAtEnd() {
    if (this->model()) {
        this->scrollTo(this->model()->index(model()->rowCount() - 1, 0, this->rootIndex()), QListView::PositionAtBottom);
    }
}

void ListView::positionViewAtIndex(const QModelIndex &index, ScrollHint mode) {
    this->scrollTo(index, mode);
}

void ListView::positionViewAtIndex(int index, ScrollHint mode) {
    if (this->model()) {
        this->positionViewAtIndex(this->model()->index(index, 0, this->rootIndex()), mode);
    }
}

void ListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    emit currentIndexChanged();
    QListView::currentChanged(current, previous);
}

void ListView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QListView::changeEvent(event);
}

void ListView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QListView::moveEvent(event);
}

void ListView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QListView::resizeEvent(event);
}

void ListView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QListView::showEvent(event);
}

void ListView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QListView::hideEvent(event);
}

void ListView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QListView::focusInEvent(event);
}

void ListView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QListView::focusOutEvent(event);
}

void ListView::classBegin() {}

void ListView::componentComplete() {
    Q_D(ListView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ListViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ListView *view = qobject_cast<ListView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void ListViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (ListView *view = qobject_cast<ListView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void ListViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ListView *view = qobject_cast<ListView*>(list->object)) {
        view->d_func()->actionList.append(obj);
        view->d_func()->dataList.append(obj);

        if (!view->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            view->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            view->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> ListViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ListViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ListViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ListViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> ListViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ListViewPrivate::actions_append);
}

QVariant ListViewPrivate::model() const {
    return modelVariant;
}

void ListViewPrivate::setModel(const QVariant &model) {
    Q_Q(ListView);

    if (model == this->model()) {
        return;
    }

    VariantListModel *oldModel = variantModel;
    variantModel = 0;
    modelVariant = model;
    QObject *obj = qvariant_cast<QObject*>(model);
    QAbstractItemModel *itemModel = 0;

    if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
        q->setModel(itemModel);
    }
    else {
        variantModel = new VariantListModel(q);
        variantModel->setVariant(model);
        q->setModel(variantModel);
    }

    if (oldModel) {
        delete oldModel;
    }

    emit q->modelChanged();
}

QVariant ListViewPrivate::rootIndex() const {
    Q_Q(const ListView);

    return QVariant::fromValue<QModelIndex>(q->rootIndex());
}

void ListViewPrivate::setRootIndex(const QVariant &index) {
    if (index != this->rootIndex()) {
        Q_Q(ListView);
        q->setRootIndex(index.value<QModelIndex>());
        emit q->rootIndexChanged();
    }
}

QVariant ListViewPrivate::currentIndex() const {
    Q_Q(const ListView);

    return QVariant::fromValue<QModelIndex>(q->currentIndex());
}

void ListViewPrivate::setCurrentIndex(const QVariant &index) {
    if (index != this->currentIndex()) {
        Q_Q(ListView);
        q->setCurrentIndex(index.value<QModelIndex>());
        emit q->currentIndexChanged();
    }
}

QVariantList ListViewPrivate::selectedIndexes() const {
    Q_Q(const ListView);
    QVariantList indexes;
    
    foreach(QModelIndex index, q->selectedIndexes()) {
        indexes.append(QVariant::fromValue(index));
    }
    
    return indexes;
}

void ListViewPrivate::setSelectedIndexes(const QVariantList &indexes) {
    Q_Q(ListView);
    
    if (!q->selectionModel()) {
        return;
    }
    
    q->clearSelection();
    
    foreach (QVariant index, indexes) {
        q->selectionModel()->select(index.value<QModelIndex>(), QItemSelectionModel::Select);
    }
}

QDeclarativeComponent* ListViewPrivate::delegate() const {
    return delegateComponent;
}

void ListViewPrivate::setDelegate(QDeclarativeComponent *delegate) {
    if (delegate != delegateComponent) {
        Q_Q(ListView);
        QDeclarativeComponent *oldDelegate = delegateComponent;
        delegateComponent = delegate;

        if (delegateComponent) {
            delegateComponent->setParent(q);

            QDeclarativeContext *creationContext = delegateComponent->creationContext();
            QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(q));

            if (QObject *obj = delegateComponent->create(context)) {
                if (QAbstractItemDelegate *delegate = qobject_cast<QAbstractItemDelegate*>(obj)) {
                    context->setParent(delegate);
                    context->setContextProperty("view", q);
                    q->setItemDelegate(delegate);
                }
                else {
                    qmlInfo(q) << ListView::tr("Component is not a valid item delegate.");
                    delete obj;
                    delete context;
                }
            }
            else {
                delete context;
            }
        }

        if (oldDelegate) {
            delete oldDelegate;
        }

        emit q->delegateChanged();
    }
}

void ListViewPrivate::_q_onHorizontalScrollPositionChanged() {
    Q_Q(ListView);

    if (!scrollTimer->isActive()) {
        emit q->movingChanged();

        if (atXBeginning) {
            atXBeginning = false;
            emit q->atXBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atXEndChanged();
        }
    }

    emit q->contentXChanged();

    scrollTimer->start();
}

void ListViewPrivate::_q_onVerticalScrollPositionChanged() {
    Q_Q(ListView);

    if (!scrollTimer->isActive()) {
        emit q->movingChanged();

        if (atYBeginning) {
            atYBeginning = false;
            emit q->atYBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atYEndChanged();
        }
    }

    emit q->contentYChanged();

    scrollTimer->start();
}

void ListViewPrivate::_q_onScrollingStopped() {
    Q_Q(ListView);

    bool xb = q->atXBeginning();
    bool xe = q->atYEnd();
    bool yb = q->atYBeginning();
    bool ye = q->atYEnd();

    if (xb != atXBeginning) {
        atXBeginning = xb;
        emit q->atXBeginningChanged();
    }

    if (xe != atXEnd) {
        atXEnd = xe;
        emit q->atXEndChanged();
    }

    if (yb != atYBeginning) {
        atYBeginning = yb;
        emit q->atYBeginningChanged();
    }

    if (ye != atYEnd) {
        atYEnd = ye;
        emit q->atYEndChanged();
    }

    emit q->movingChanged();
}

#include "moc_listview_p.cpp"
