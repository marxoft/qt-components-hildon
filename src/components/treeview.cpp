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

#include "treeview_p.h"
#include "treeview_p_p.h"
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

TreeView::TreeView(QWidget *parent) :
    QTreeView(parent),
    d_ptr(new TreeViewPrivate(this))
{
    Q_D(TreeView);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
}

TreeView::TreeView(TreeViewPrivate &dd, QWidget *parent) :
    QTreeView(parent),
    d_ptr(&dd)
{
    Q_D(TreeView);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
}

TreeView::~TreeView() {}

void TreeView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void TreeView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal TreeView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void TreeView::setOpacity(qreal opacity) {
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

AnchorLine TreeView::left() const {
    Q_D(const TreeView);

    return d->left;
}

AnchorLine TreeView::right() const {
    Q_D(const TreeView);

    return d->right;
}

AnchorLine TreeView::top() const {
    Q_D(const TreeView);

    return d->top;
}

AnchorLine TreeView::bottom() const {
    Q_D(const TreeView);

    return d->bottom;
}

AnchorLine TreeView::horizontalCenter() const {
    Q_D(const TreeView);

    return d->horizontalCenter;
}

AnchorLine TreeView::verticalCenter() const {
    Q_D(const TreeView);

    return d->verticalCenter;
}

bool TreeView::interactive() const {
    Q_D(const TreeView);

    return d->kineticScroller->isEnabled();
}

void TreeView::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(TreeView);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool TreeView::moving() const {
    Q_D(const TreeView);

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

bool TreeView::atXBeginning() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->minimum();
}

bool TreeView::atXEnd() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum();
}

bool TreeView::atYBeginning() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->minimum();
}

bool TreeView::atYEnd() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->maximum();
}

int TreeView::contentX() const {
    return this->horizontalScrollBar()->value();
}

void TreeView::setContentX(int x) {
    this->horizontalScrollBar()->setValue(x);
}

int TreeView::contentY() const {
    return this->horizontalScrollBar()->value();
}

void TreeView::setContentY(int y) {
    this->verticalScrollBar()->setValue(y);
}

qreal TreeView::flickDeceleration() const {
    Q_D(const TreeView);

    return d->kineticScroller->decelerationFactor();
}

void TreeView::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(TreeView);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal TreeView::maximumFlickVelocity() const {
    Q_D(const TreeView);

    return d->kineticScroller->maximumVelocity();
}

void TreeView::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(TreeView);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

void TreeView::positionViewAtBeginning(bool immediate) {
    if (this->model()) {
        if (immediate) {
            this->scrollTo(this->model()->index(0, 0, this->rootIndex()), QTreeView::PositionAtTop);
        }
        else {
            Q_D(TreeView);
            d->kineticScroller->scrollTo(QPoint(this->horizontalScrollBar()->minimum(), this->verticalScrollBar()->minimum()));
        }
    }
}

void TreeView::positionViewAtEnd(bool immediate) {
    if (this->model()) {
        if (immediate) {
            this->scrollTo(this->model()->index(model()->rowCount() - 1, 0, this->rootIndex()), QTreeView::PositionAtBottom);
        }
        else {
            Q_D(TreeView);
            d->kineticScroller->scrollTo(QPoint(this->horizontalScrollBar()->maximum(), this->verticalScrollBar()->maximum()));
        }
    }
}

void TreeView::positionViewAtIndex(const QModelIndex &index, ScrollHint mode, bool immediate) {
    if (immediate) {
        this->scrollTo(index, mode);
    }
    else {
        Q_D(TreeView);
        QRect rect = this->visualRect(index);
        const QRect viewRect = this->viewport()->rect();
        const int wDiff = viewRect.width() - rect.width();
        const int hDiff = viewRect.height() - rect.height();
        
        switch (mode) {
        case PositionAtTop:
            break;
        case PositionAtBottom:
            rect.translate(-wDiff, -hDiff);
            break;
        case PositionAtCenter:
            rect.translate(wDiff ? -(wDiff / 2) : 0, hDiff ? -(hDiff / 2) : 0);
            break;
        default:
            d->kineticScroller->ensureVisible(rect.topLeft(), rect.height(), rect.height());
            return;
        }
        
        d->kineticScroller->scrollTo(QPoint(qBound(0, rect.left() + this->horizontalScrollBar()->value(),
                                                   this->horizontalScrollBar()->maximum()),
                                            qBound(0, rect.top() + this->verticalScrollBar()->value(), 
                                                   this->verticalScrollBar()->maximum())));
    }
}

void TreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    emit currentIndexChanged();
    QTreeView::currentChanged(current, previous);
}

void TreeView::changeEvent(QEvent *event) {
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

    QTreeView::changeEvent(event);
}

void TreeView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QTreeView::moveEvent(event);
}

void TreeView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QTreeView::resizeEvent(event);
}

void TreeView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QTreeView::showEvent(event);
}

void TreeView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QTreeView::hideEvent(event);
}

void TreeView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QTreeView::focusInEvent(event);
}

void TreeView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QTreeView::focusOutEvent(event);
}

void TreeView::classBegin() {}

void TreeView::componentComplete() {
    Q_D(TreeView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void TreeViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TreeView *view = qobject_cast<TreeView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void TreeViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (TreeView *view = qobject_cast<TreeView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void TreeViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TreeView *view = qobject_cast<TreeView*>(list->object)) {
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

QDeclarativeListProperty<QObject> TreeViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TreeViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> TreeViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, TreeViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> TreeViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TreeViewPrivate::actions_append);
}

QVariant TreeViewPrivate::model() const {
    return modelVariant;
}

void TreeViewPrivate::setModel(const QVariant &model) {
    Q_Q(TreeView);

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

QVariant TreeViewPrivate::rootIndex() const {
    Q_Q(const TreeView);

    return QVariant::fromValue<QModelIndex>(q->rootIndex());
}

void TreeViewPrivate::setRootIndex(const QVariant &index) {
    if (index != this->rootIndex()) {
        Q_Q(TreeView);
        q->setRootIndex(index.value<QModelIndex>());
        emit q->rootIndexChanged();
    }
}

QVariant TreeViewPrivate::currentIndex() const {
    Q_Q(const TreeView);

    return QVariant::fromValue<QModelIndex>(q->currentIndex());
}

void TreeViewPrivate::setCurrentIndex(const QVariant &index) {
    if (index != this->currentIndex()) {
        Q_Q(TreeView);
        q->setCurrentIndex(index.value<QModelIndex>());
        emit q->currentIndexChanged();
    }
}

QVariantList TreeViewPrivate::selectedIndexes() const {
    Q_Q(const TreeView);
    QVariantList indexes;
    
    foreach(QModelIndex index, q->selectedIndexes()) {
        indexes.append(QVariant::fromValue(index));
    }
    
    return indexes;
}

void TreeViewPrivate::setSelectedIndexes(const QVariantList &indexes) {
    Q_Q(TreeView);
    
    if (!q->selectionModel()) {
        return;
    }
    
    q->clearSelection();
    
    foreach (QVariant index, indexes) {
        q->selectionModel()->select(index.value<QModelIndex>(), QItemSelectionModel::Select);
    }
}

QDeclarativeComponent* TreeViewPrivate::delegate() const {
    return delegateComponent;
}

void TreeViewPrivate::setDelegate(QDeclarativeComponent *delegate) {
    if (delegate != delegateComponent) {
        Q_Q(TreeView);
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
                    qmlInfo(q) << TreeView::tr("Component is not a valid item delegate.");
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

void TreeViewPrivate::_q_onHorizontalScrollPositionChanged() {
    Q_Q(TreeView);

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

void TreeViewPrivate::_q_onVerticalScrollPositionChanged() {
    Q_Q(TreeView);

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

void TreeViewPrivate::_q_onScrollingStopped() {
    Q_Q(TreeView);

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

#include "moc_treeview_p.cpp"
