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

#include "headerview_p.h"
#include "headerview_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

HeaderView::HeaderView(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent),
    d_ptr(new HeaderViewPrivate(this))
{
    this->setClickable(true);
    this->setHighlightSections(true);
}

HeaderView::HeaderView(HeaderViewPrivate &dd, QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent),
    d_ptr(&dd)
{
    this->setClickable(true);
    this->setHighlightSections(true);
}

HeaderView::~HeaderView() {}

void HeaderView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void HeaderView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal HeaderView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void HeaderView::setOpacity(qreal opacity) {
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

void HeaderView::setFocus(bool focus) {
    Q_D(const HeaderView);

    if ((d->complete) && (focus != this->hasFocus())) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

AnchorLine HeaderView::left() const {
    Q_D(const HeaderView);

    return d->left;
}

AnchorLine HeaderView::right() const {
    Q_D(const HeaderView);

    return d->right;
}

AnchorLine HeaderView::top() const {
    Q_D(const HeaderView);

    return d->top;
}

AnchorLine HeaderView::bottom() const {
    Q_D(const HeaderView);

    return d->bottom;
}

AnchorLine HeaderView::horizontalCenter() const {
    Q_D(const HeaderView);

    return d->horizontalCenter;
}

AnchorLine HeaderView::verticalCenter() const {
    Q_D(const HeaderView);

    return d->verticalCenter;
}

QStringList HeaderView::labels() const {
    Q_D(const HeaderView);

    return d->labels ? d->labels->stringList() : QStringList();
}

void HeaderView::setLabels(const QStringList &labels) {
    Q_D(HeaderView);

    if (!d->labels) {
        d->labels = new HeaderLabelModel(this);
        this->setModel(d->labels);
    }

    d->labels->setStringList(labels);
    emit labelsChanged();
}

void HeaderView::changeEvent(QEvent *event) {
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

    QHeaderView::changeEvent(event);
}

void HeaderView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QHeaderView::moveEvent(event);
}

void HeaderView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QHeaderView::resizeEvent(event);
}

void HeaderView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QHeaderView::showEvent(event);
}

void HeaderView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QHeaderView::hideEvent(event);
}

void HeaderView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QHeaderView::focusInEvent(event);
}

void HeaderView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QHeaderView::focusOutEvent(event);
}

void HeaderView::classBegin() {}

void HeaderView::componentComplete() {
    Q_D(HeaderView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void HeaderViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void HeaderViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void HeaderViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
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

QDeclarativeListProperty<QObject> HeaderViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, HeaderViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> HeaderViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, HeaderViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> HeaderViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, HeaderViewPrivate::actions_append);
}

QVariant HeaderViewPrivate::currentIndex() const {
    Q_Q(const HeaderView);

    return QVariant::fromValue<QModelIndex>(q->currentIndex());
}

void HeaderViewPrivate::setCurrentIndex(const QVariant &index) {
    if (index != this->currentIndex()) {
        Q_Q(HeaderView);
        q->setCurrentIndex(index.value<QModelIndex>());
        emit q->currentIndexChanged();
    }
}

bool HeaderViewPrivate::isClickable() const {
    Q_Q(const HeaderView);

    return q->isClickable();
}

void HeaderViewPrivate::setClickable(bool clickable) {
    if (clickable != this->isClickable()) {
        Q_Q(HeaderView);
        q->setClickable(clickable);
        emit q->clickableChanged();
    }
}

bool HeaderViewPrivate::isSortIndicatorShown() const {
    Q_Q(const HeaderView);

    return q->isSortIndicatorShown();
}

void HeaderViewPrivate::setSortIndicatorShown(bool shown) {
    if (shown != this->isSortIndicatorShown()) {
        Q_Q(HeaderView);
        q->setSortIndicatorShown(shown);
        emit q->showSortIndicatorChanged();
    }
}

bool HeaderViewPrivate::highlightSections() const {
    Q_Q(const HeaderView);

    return q->highlightSections();
}

void HeaderViewPrivate::setHighlightSections(bool highlight) {
    if (highlight != this->highlightSections()) {
        Q_Q(HeaderView);
        q->setHighlightSections(highlight);
        emit q->highlightSectionsChanged();
    }
}

bool HeaderViewPrivate::stretchLastSection() const {
    Q_Q(const HeaderView);

    return q->stretchLastSection();
}

void HeaderViewPrivate::setStretchLastSection(bool stretch) {
    if (stretch != this->stretchLastSection()) {
        Q_Q(HeaderView);
        q->setStretchLastSection(stretch);
        emit q->stretchLastSectionChanged();
    }
}

bool HeaderViewPrivate::cascadingSectionResizes() const {
    Q_Q(const HeaderView);

    return q->cascadingSectionResizes();
}

void HeaderViewPrivate::setCascadingSectionResizes(bool resizes) {
    if (resizes != this->cascadingSectionResizes()) {
        Q_Q(HeaderView);
        q->setCascadingSectionResizes(resizes);
        emit q->cascadingSectionResizesChanged();
    }
}

int HeaderViewPrivate::defaultSectionSize() const {
    Q_Q(const HeaderView);

    return q->defaultSectionSize();
}

void HeaderViewPrivate::setDefaultSectionSize(int size) {
    if (size != this->defaultSectionSize()) {
        Q_Q(HeaderView);
        q->setDefaultSectionSize(size);
        emit q->defaultSectionSizeChanged();
    }
}

int HeaderViewPrivate::minimumSectionSize() const {
    Q_Q(const HeaderView);

    return q->minimumSectionSize();
}

void HeaderViewPrivate::setMinimumSectionSize(int size) {
    if (size != this->minimumSectionSize()) {
        Q_Q(HeaderView);
        q->setMinimumSectionSize(size);
        emit q->minimumSectionSizeChanged();
    }
}

Qt::Alignment HeaderViewPrivate::defaultAlignment() const {
    Q_Q(const HeaderView);

    return q->defaultAlignment();
}

void HeaderViewPrivate::setDefaultAlignment(Qt::Alignment alignment) {
    if (alignment != this->defaultAlignment()) {
        Q_Q(HeaderView);
        q->setDefaultAlignment(alignment);
        emit q->defaultAlignmentChanged();
    }
}

HeaderLabelModel::HeaderLabelModel(QObject *parent) :
    QStringListModel(parent)
{
}

HeaderLabelModel::HeaderLabelModel(const QStringList &strings, QObject *parent) :
    QStringListModel(strings, parent)
{
}

int HeaderLabelModel::columnCount(const QModelIndex &parent) const {
    return this->rowCount(parent);
}

QVariant HeaderLabelModel::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(orientation);

    return this->data(this->index(section), role);
}

#include "moc_headerview_p.cpp"
