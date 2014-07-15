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

#include "anchors_p.h"
#include "anchors_p_p.h"
#include <QPoint>
#include <QSize>
#include <qdeclarativeinfo.h>

static int position(QObject *item, AnchorLine::Line line) {
    int ret = 0;

    switch (line) {
    case AnchorLine::Left:
        ret = item->property("x").toInt();
        break;
    case AnchorLine::Right:
        ret = item->property("x").toInt() + item->property("width").toInt();
        break;
    case AnchorLine::Top:
        ret = item->property("y").toInt();
        break;
    case AnchorLine::Bottom:
        ret = item->property("y").toInt() + item->property("height").toInt();
        break;
    case AnchorLine::HCenter:
        ret = item->property("x").toInt() + item->property("width").toInt() / 2;
        break;
    case AnchorLine::VCenter:
        ret = item->property("y").toInt() + item->property("height").toInt() / 2;
        break;
    default:
        break;
    }

    return ret;
}

//position when origin is 0,0
static int adjustedPosition(QObject *item, AnchorLine::Line line) {
    int ret = 0;

    switch (line) {
    case AnchorLine::Left:
        ret = 0;
        break;
    case AnchorLine::Right:
        ret = item->property("width").toInt();
        break;
    case AnchorLine::Top:
        ret = 0;
        break;
    case AnchorLine::Bottom:
        ret = item->property("height").toInt();
        break;
    case AnchorLine::HCenter:
        ret = item->property("width").toInt() / 2;
        break;
    case AnchorLine::VCenter:
        ret = item->property("height").toInt() / 2;
        break;
    default:
        break;
    }

    return ret;
}

Anchors::Anchors(QObject *item, QObject *parent) :
    QObject(parent),
    d_ptr(new AnchorsPrivate(item, this))
{
}

Anchors::Anchors(AnchorsPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Anchors::~Anchors() {
    Q_D(Anchors);

    d->inDestructor = true;
    d->remDepend(d->fill);
    d->remDepend(d->centerIn);
    d->remDepend(d->left.item);
    d->remDepend(d->right.item);
    d->remDepend(d->top.item);
    d->remDepend(d->bottom.item);
    d->remDepend(d->horizontalCenter.item);
    d->remDepend(d->verticalCenter.item);
}

AnchorLine Anchors::left() const {
    Q_D(const Anchors);

    return d->left;
}

void Anchors::setLeft(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->left == edge)) {
        return;
    }

    d->usedAnchors |= LeftAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~LeftAnchor;
        return;
    }

    QObject *oldLeft = d->left.item;

    d->left = edge;
    d->remDepend(oldLeft);
    d->addDepend(d->left.item);
    emit leftChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetLeft() {
    Q_D(Anchors);

    d->usedAnchors &= ~LeftAnchor;
    d->remDepend(d->left.item);
    d->left = AnchorLine();
    emit leftChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::leftMargin() const {
    Q_D(const Anchors);

    return d->leftMargin;
}

void Anchors::setLeftMargin(int offset) {
    Q_D(Anchors);

    d->leftMarginExplicit = true;

    if (d->leftMargin == offset) {
        return;
    }

    d->leftMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit leftMarginChanged();
}

void Anchors::resetLeftMargin() {
    Q_D(Anchors);

    d->leftMarginExplicit = false;

    if (d->leftMargin == d->margins) {
        return;
    }

    d->leftMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit leftMarginChanged();
}

AnchorLine Anchors::right() const {
    Q_D(const Anchors);

    return d->right;
}

void Anchors::setRight(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->right == edge)) {
        return;
    }

    d->usedAnchors |= RightAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~RightAnchor;
        return;
    }

    QObject *oldRight = d->right.item;
    d->right = edge;
    d->remDepend(oldRight);
    d->addDepend(d->right.item);
    emit rightChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetRight() {
    Q_D(Anchors);

    d->usedAnchors &= ~RightAnchor;
    d->remDepend(d->right.item);
    d->right = AnchorLine();
    emit rightChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::rightMargin() const {
    Q_D(const Anchors);

    return d->rightMargin;
}

void Anchors::setRightMargin(int offset) {
    Q_D(Anchors);

    d->rightMarginExplicit = true;

    if (d->rightMargin == offset) {
        return;
    }

    d->rightMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit rightMarginChanged();
}

void Anchors::resetRightMargin() {
    Q_D(Anchors);

    d->rightMarginExplicit = false;

    if (d->rightMargin == d->margins) {
        return;
    }

    d->rightMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit rightMarginChanged();
}

AnchorLine Anchors::top() const {
    Q_D(const Anchors);

    return d->top;
}

void Anchors::setTop(const AnchorLine &edge) {
    Q_D(Anchors);

    if (!d->checkVAnchorValid(edge) || d->top == edge) {
        return;
    }

    d->usedAnchors |= TopAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~TopAnchor;
        return;
    }

    QObject *oldTop = d->top.item;
    d->top = edge;
    d->remDepend(oldTop);
    d->addDepend(d->top.item);
    emit topChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetTop() {
    Q_D(Anchors);

    d->usedAnchors &= ~TopAnchor;
    d->remDepend(d->top.item);
    d->top = AnchorLine();
    emit topChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::topMargin() const {
    Q_D(const Anchors);

    return d->topMargin;
}

void Anchors::setTopMargin(int offset) {
    Q_D(Anchors);

    d->topMarginExplicit = true;

    if (d->topMargin == offset) {
        return;
    }

    d->topMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit topMarginChanged();
}

void Anchors::resetTopMargin() {
    Q_D(Anchors);

    d->topMarginExplicit = false;

    if (d->topMargin == d->margins) {
        return;
    }

    d->topMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit topMarginChanged();
}

AnchorLine Anchors::bottom() const {
    Q_D(const Anchors);

    return d->bottom;
}

void Anchors::setBottom(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkVAnchorValid(edge)) || (d->bottom == edge)) {
        return;
    }

    d->usedAnchors |= BottomAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~BottomAnchor;
        return;
    }

    QObject *oldBottom = d->bottom.item;
    d->bottom = edge;
    d->remDepend(oldBottom);
    d->addDepend(d->bottom.item);
    emit bottomChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetBottom() {
    Q_D(Anchors);

    d->usedAnchors &= ~BottomAnchor;
    d->remDepend(d->bottom.item);
    d->bottom = AnchorLine();
    emit bottomChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::bottomMargin() const {
    Q_D(const Anchors);

    return d->bottomMargin;
}

void Anchors::setBottomMargin(int offset) {
    Q_D(Anchors);

    d->bottomMarginExplicit = true;

    if (d->bottomMargin == offset) {
        return;
    }

    d->bottomMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit bottomMarginChanged();
}

void Anchors::resetBottomMargin() {
    Q_D(Anchors);

    d->bottomMarginExplicit = false;

    if (d->bottomMargin == d->margins) {
        return;
    }

    d->bottomMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit bottomMarginChanged();
}

int Anchors::margins() const {
    Q_D(const Anchors);

    return d->margins;
}

void Anchors::setMargins(int offset) {
    Q_D(Anchors);

    if (d->margins == offset) {
        return;
    }

    d->margins = offset;
    bool updateHorizontal = false;
    bool updateVertical = false;

    if ((!d->rightMarginExplicit) && (d->rightMargin != offset)) {
        d->rightMargin = offset;
        updateHorizontal = true;
        emit rightMarginChanged();
    }

    if ((!d->leftMarginExplicit) && (d->leftMargin != offset)) {
        d->leftMargin = offset;
        updateHorizontal = true;
        emit leftMarginChanged();
    }

    if ((!d->topMarginExplicit) && (d->topMargin != offset)) {
        d->topMargin = offset;
        updateVertical = true;
        emit topMarginChanged();
    }

    if ((!d->bottomMarginExplicit) && (d->bottomMargin != offset)) {
        d->bottomMargin = offset;
        updateVertical = true;
        emit bottomMarginChanged();
    }

    if (d->fill) {
        if ((updateHorizontal) || (updateVertical)) {
            d->fillChanged();
        }
    }
    else {
        if (updateHorizontal) {
            d->_q_updateHorizontalAnchors();
        }

        if (updateVertical) {
            d->_q_updateVerticalAnchors();
        }
    }

    emit marginsChanged();
}

AnchorLine Anchors::horizontalCenter() const {
    Q_D(const Anchors);

    return d->horizontalCenter;
}

void Anchors::setHorizontalCenter(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->horizontalCenter == edge)) {
        return;
    }

    d->usedAnchors |= HCenterAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~HCenterAnchor;
        return;
    }

    QObject *oldHCenter = d->horizontalCenter.item;
    d->horizontalCenter = edge;
    d->remDepend(oldHCenter);
    d->addDepend(d->horizontalCenter.item);
    emit horizontalCenterChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetHorizontalCenter() {
    Q_D(Anchors);

    d->usedAnchors &= ~HCenterAnchor;
    d->remDepend(d->horizontalCenter.item);
    d->horizontalCenter = AnchorLine();
    emit horizontalCenterChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::horizontalCenterOffset() const {
    Q_D(const Anchors);

    return d->horizontalCenterOffset;
}

void Anchors::setHorizontalCenterOffset(int offset) {
    Q_D(Anchors);

    if (d->horizontalCenterOffset == offset) {
        return;
    }

    d->horizontalCenterOffset = offset;

    if (d->centerIn) {
        d->centerInChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit horizontalCenterOffsetChanged();
}

AnchorLine Anchors::verticalCenter() const {
    Q_D(const Anchors);

    return d->verticalCenter;
}

void Anchors::setVerticalCenter(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkVAnchorValid(edge)) || (d->verticalCenter == edge)) {
        return;
    }

    d->usedAnchors |= VCenterAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~VCenterAnchor;
        return;
    }

    QObject *oldverticalCenter = d->verticalCenter.item;
    d->verticalCenter = edge;
    d->remDepend(oldverticalCenter);
    d->addDepend(d->verticalCenter.item);
    emit verticalCenterChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetVerticalCenter() {
    Q_D(Anchors);

    d->usedAnchors &= ~VCenterAnchor;
    d->remDepend(d->verticalCenter.item);
    d->verticalCenter = AnchorLine();
    emit verticalCenterChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::verticalCenterOffset() const {
    Q_D(const Anchors);

    return d->verticalCenterOffset;
}

void Anchors::setVerticalCenterOffset(int offset) {
    Q_D(Anchors);

    if (d->verticalCenterOffset == offset) {
        return;
    }

    d->verticalCenterOffset = offset;

    if (d->centerIn) {
        d->centerInChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit verticalCenterOffsetChanged();
}

QObject* Anchors::centerIn() const {
    Q_D(const Anchors);

    return d->centerIn;
}

void Anchors::setCenterIn(QObject *obj) {
    Q_D(Anchors);

    QObject *c = qobject_cast<QObject*>(obj);

    if (d->centerIn == c) {
        return;
    }

    if (!c) {
        QObject *oldCI = d->centerIn;
        d->centerIn = c;
        d->remDepend(oldCI);
        emit centerInChanged();
        return;
    }

    if ((c != d->item->parent()) && (c->parent() != d->item->parent())) {
        qmlInfo(d->item) << tr("Cannot anchor to an item that isn't a parent or sibling.");
        return;
    }

    QObject *oldCI = d->centerIn;
    d->centerIn = c;
    d->remDepend(oldCI);
    d->addDepend(d->centerIn);
    emit centerInChanged();
    d->centerInChanged();
}

void Anchors::resetCenterIn() {
    this->setCenterIn(0);
}

QObject* Anchors::fill() const {
    Q_D(const Anchors);

    return d->fill;
}

void Anchors::setFill(QObject *obj) {
    Q_D(Anchors);

    QObject *f = qobject_cast<QObject*>(obj);

    if (d->fill == f) {
        return;
    }

    if (!f) {
        QObject *oldFill = d->fill;
        d->fill = f;
        d->remDepend(oldFill);
        emit fillChanged();
        return;
    }

    if ((f != d->item->parent()) && (f->parent() != d->item->parent())) {
        qmlInfo(d->item) << tr("Cannot anchor to an item that isn't a parent or sibling.");
        return;
    }

    QObject *oldFill = d->fill;
    d->fill = f;
    d->remDepend(oldFill);
    d->addDepend(d->fill);
    emit fillChanged();
    d->fillChanged();
}

void Anchors::resetFill() {
    this->setFill(0);
}

Anchors::AnchorFlags Anchors::usedAnchors() const {
    Q_D(const Anchors);

    return d->usedAnchors;
}

void AnchorsPrivate::fillChanged() {
    if ((!fill) || (!this->isItemComplete())) {
        return;
    }

    if (updatingFill < 2) {
        ++updatingFill;

        if (fill == item->parent()) { //child-parent
            this->setItemPos(QPoint(leftMargin, topMargin));
        }
        else if (fill->parent() == item->parent()) { //siblings
            this->setItemPos(QPoint(fill->property("x").toInt() + leftMargin, fill->property("y").toInt() + topMargin));
        }

        this->setItemSize(QSize(fill->property("width").toInt() -leftMargin - rightMargin, fill->property("height").toInt() - topMargin - bottomMargin));
        --updatingFill;
    }
    else {
        // ### Make this certain :)
        qmlInfo(item) << Anchors::tr("Possible anchor loop detected on fill.");
    }
}

void AnchorsPrivate::centerInChanged() {
    if ((!centerIn) || (fill) || (!this->isItemComplete())) {
        return;
    }

    if (updatingCenterIn < 2) {
        ++updatingCenterIn;

        if (centerIn == item->parent()) {
            QPoint p(item->parent()->property("width").toInt() / 2 - item->property("width").toInt() / 2 + horizontalCenterOffset,
                     item->parent()->property("height").toInt() / 2 - item->property("height").toInt() / 2 + verticalCenterOffset);
            this->setItemPos(p);
        }
        else if (centerIn->parent() == item->parent()) {
            QPoint p(centerIn->property("x").toInt() + centerIn->property("width").toInt() / 2 - item->property("width").toInt() / 2 + horizontalCenterOffset,
                     centerIn->property("y").toInt() + centerIn->property("height").toInt() / 2 - item->property("height").toInt() / 2 + verticalCenterOffset);
            this->setItemPos(p);
        }

        --updatingCenterIn;
    }
    else {
        // ### Make this certain :)
        qmlInfo(item) << Anchors::tr("Possible anchor loop detected on centerIn.");
    }
}

void AnchorsPrivate::clearItem(QObject *i) {
    if (!i) {
        return;
    }

    if (fill == i) {
        fill = 0;
    }

    if (centerIn == i) {
        centerIn = 0;
    }

    if (left.item == i) {
        left.item = 0;
        usedAnchors &= ~Anchors::LeftAnchor;
    }

    if (right.item == i) {
        right.item = 0;
        usedAnchors &= ~Anchors::RightAnchor;
    }

    if (top.item == i) {
        top.item = 0;
        usedAnchors &= ~Anchors::TopAnchor;
    }

    if (bottom.item == i) {
        bottom.item = 0;
        usedAnchors &= ~Anchors::BottomAnchor;
    }

    if (horizontalCenter.item == i) {
        horizontalCenter.item = 0;
        usedAnchors &= ~Anchors::HCenterAnchor;
    }

    if (verticalCenter.item == i) {
        verticalCenter.item = 0;
        usedAnchors &= ~Anchors::VCenterAnchor;
    }
}

void AnchorsPrivate::addDepend(QObject *i) {
    if ((!i) || (inDestructor)) {
        return;
    }

    Q_Q(Anchors);

    //TODO: Install event filter or use interface instead of connecting to signals.

    if (centerIn) {
        q->connect(item, SIGNAL(parentChanged()), q, SLOT(centerInChanged()));
        q->connect(i, SIGNAL(xChanged()), q, SLOT(centerInChanged()));
        q->connect(i, SIGNAL(widthChanged()), q, SLOT(centerInChanged()));
        q->connect(i, SIGNAL(yChanged()), q, SLOT(centerInChanged()));
        q->connect(i, SIGNAL(heightChanged()), q, SLOT(centerInChanged()));
    }
    else if (fill) {
        q->connect(item, SIGNAL(parentChanged()), q, SLOT(fillChanged()));
        q->connect(i, SIGNAL(xChanged()), q, SLOT(fillChanged()));
        q->connect(i, SIGNAL(widthChanged()), q, SLOT(fillChanged()));
        q->connect(i, SIGNAL(yChanged()), q, SLOT(fillChanged()));
        q->connect(i, SIGNAL(heightChanged()), q, SLOT(fillChanged()));
    }
    else {
        if ((usedAnchors & Anchors::LeftAnchor) || (usedAnchors & Anchors::RightAnchor) || (usedAnchors & Anchors::HCenterAnchor)) {
            q->connect(item, SIGNAL(parentChanged()), q, SLOT(_q_updateHorizontalAnchors()));
            q->connect(i, SIGNAL(xChanged()), q, SLOT(_q_updateHorizontalAnchors()));
            q->connect(i, SIGNAL(widthChanged()), q, SLOT(_q_updateHorizontalAnchors()));
        }

        if ((usedAnchors & Anchors::TopAnchor) || (usedAnchors & Anchors::BottomAnchor) || (usedAnchors & Anchors::VCenterAnchor)) {
            q->connect(item, SIGNAL(parentChanged()), q, SLOT(_q_updateVerticalAnchors()));
            q->connect(i, SIGNAL(yChanged()), q, SLOT(_q_updateVerticalAnchors()));
            q->connect(i, SIGNAL(heightChanged()), q, SLOT(_q_updateVerticalAnchors()));
        }
    }
}

void AnchorsPrivate::remDepend(QObject *i) {
    if ((!i) || (inDestructor)) {
        return;
    }

    Q_Q(Anchors);

    q->disconnect(i, SIGNAL(xChanged()), q, SLOT(_q_updateHorizontalAnchors()));
    q->disconnect(i, SIGNAL(widthChanged()), q, SLOT(_q_updateHorizontalAnchors()));
    q->disconnect(i, SIGNAL(yChanged()), q, SLOT(_q_updateVerticalAnchors()));
    q->disconnect(i, SIGNAL(heightChanged()), q, SLOT(_q_updateVerticalAnchors()));
}

bool AnchorsPrivate::isItemComplete() const {
    return itemComplete;
}

void AnchorsPrivate::setItemX(int x) {
    updatingMe = true;
    item->setProperty("x", x);
    updatingMe = false;
}

void AnchorsPrivate::setItemY(int y) {
    updatingMe = true;
    item->setProperty("y", y);
    updatingMe = false;
}

void AnchorsPrivate::setItemPos(const QPoint &pos) {
    updatingMe = true;
    item->setProperty("x", pos.x());
    item->setProperty("y", pos.y());
    updatingMe = false;
}

void AnchorsPrivate::setItemWidth(int width) {
    updatingMe = true;
    item->setProperty("width", width);
    updatingMe = false;
}

void AnchorsPrivate::setItemHeight(int height) {
    updatingMe = true;
    item->setProperty("height", height);
    updatingMe = false;
}

void AnchorsPrivate::setItemSize(const QSize &size) {
    updatingMe = true;
    item->setProperty("width", size.width());
    item->setProperty("height", size.height());
    updatingMe = false;
}

bool AnchorsPrivate::checkHValid() const {
    if ((usedAnchors & Anchors::LeftAnchor) &&
            (usedAnchors & Anchors::RightAnchor) &&
            (usedAnchors & Anchors::HCenterAnchor)) {

        qmlInfo(item) << Anchors::tr("Cannot specify left, right, and horizontalCenter anchors at the same time.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::checkVValid() const {
    if (usedAnchors & Anchors::TopAnchor &&
            usedAnchors & Anchors::BottomAnchor &&
            usedAnchors & Anchors::VCenterAnchor) {

        qmlInfo(item) << Anchors::tr("Cannot specify top, bottom, and verticalCenter anchors at the same time.");
        return false;

    }

    return true;
}

bool AnchorsPrivate::checkHAnchorValid(AnchorLine anchor) const {
    if (!anchor.item) {
        qmlInfo(item) << Anchors::tr("Cannot anchor to a null item.");
        return false;
    }
    else if (anchor.line & AnchorLine::Vertical_Mask) {
        qmlInfo(item) << Anchors::tr("Cannot anchor a horizontal edge to a vertical edge.");
        return false;
    }
    else if (anchor.item != item->parent() && anchor.item->parent() != item->parent()){
        qmlInfo(item) << Anchors::tr("Cannot anchor to an item that isn't a parent or sibling.");
        return false;
    }
    else if (anchor.item == item) {
        qmlInfo(item) << Anchors::tr("Cannot anchor item to self.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::checkVAnchorValid(AnchorLine anchor) const {
    if (!anchor.item) {
        qmlInfo(item) << Anchors::tr("Cannot anchor to a null item.");
        return false;
    }
    else if (anchor.line & AnchorLine::Horizontal_Mask) {
        qmlInfo(item) << Anchors::tr("Cannot anchor a vertical edge to a horizontal edge.");
        return false;
    }
    else if (anchor.item != item->parent() && anchor.item->parent() != item->parent()){
        qmlInfo(item) << Anchors::tr("Cannot anchor to an item that isn't a parent or sibling.");
        return false;
    }
    else if (anchor.item == item){
        qmlInfo(item) << Anchors::tr("Cannot anchor item to self.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::calcStretch(const AnchorLine &edge1,
                                 const AnchorLine &edge2,
                                 int offset1,
                                 int offset2,
                                 AnchorLine::Line line,
                                 int &stretch) {

    bool edge1IsParent = (edge1.item == item->parent());
    bool edge2IsParent = (edge2.item == item->parent());
    bool edge1IsSibling = (edge1.item->parent() == item->parent());
    bool edge2IsSibling = (edge2.item->parent() == item->parent());
    bool invalid = false;

    if ((edge2IsParent && edge1IsParent) || (edge2IsSibling && edge1IsSibling)) {
        stretch = (position(edge2.item, edge2.line) + offset2)
                - (position(edge1.item, edge1.line) + offset1);
    }
    else if (edge2IsParent && edge1IsSibling) {
        stretch = (position(edge2.item, edge2.line) + offset2)
                - (position(item->parent(), line)
                   + position(edge1.item, edge1.line) + offset1);
    }
    else if (edge2IsSibling && edge1IsParent) {
        stretch = (position(item->parent(), line) + position(edge2.item, edge2.line) + offset2)
                - (position(edge1.item, edge1.line) + offset1);
    }
    else {
        invalid = true;
    }

    return invalid;
}

void AnchorsPrivate::onItemCompleted() {
    itemComplete = true;
    this->update();
}

void AnchorsPrivate::update() {
    this->fillChanged();
    this->centerInChanged();

    if (usedAnchors & AnchorLine::Horizontal_Mask) {
        this->_q_updateHorizontalAnchors();
    }

    if (usedAnchors & AnchorLine::Vertical_Mask) {
        this->_q_updateVerticalAnchors();
    }
}

void AnchorsPrivate::_q_updateVerticalAnchors() {
    if ((fill) || (centerIn) || (!this->isItemComplete())) {
        return;
    }

    if (updatingVerticalAnchor < 2) {
        ++updatingVerticalAnchor;

        if (usedAnchors & Anchors::TopAnchor) {
            //Handle stretching
            bool invalid = true;
            int height = 0;

            if (usedAnchors & Anchors::BottomAnchor) {
                invalid = this->calcStretch(top, bottom, topMargin, -bottomMargin, AnchorLine::Top, height);
            }
            else if (usedAnchors & Anchors::VCenterAnchor) {
                invalid = this->calcStretch(top, verticalCenter, topMargin, verticalCenterOffset, AnchorLine::Top, height);
                height *= 2;
            }

            if (!invalid) {
                this->setItemHeight(height);
            }

            //Handle top
            if (top.item == item->parent()) {
                this->setItemY(adjustedPosition(top.item, top.line) + topMargin);
            }
            else if (top.item->parent() == item->parent()) {
                this->setItemY(position(top.item, top.line) + topMargin);
            }
        }
        else if (usedAnchors & Anchors::BottomAnchor) {
            //Handle stretching (top + bottom case is handled above)
            if (usedAnchors & Anchors::VCenterAnchor) {
                int height = 0;
                bool invalid = this->calcStretch(verticalCenter, bottom, verticalCenterOffset, -bottomMargin,
                                                 AnchorLine::Top, height);
                if (!invalid) {
                    this->setItemHeight(height * 2);
                }
            }

            //Handle bottom
            if (bottom.item == item->parent()) {
                this->setItemY(adjustedPosition(bottom.item, bottom.line) - item->property("height").toInt() - bottomMargin);
            }
            else if (bottom.item->parent() == item->parent()) {
                this->setItemY(position(bottom.item, bottom.line) - item->property("height").toInt() - bottomMargin);
            }
        }
        else if (usedAnchors & Anchors::VCenterAnchor) {
            //(stetching handled above)
            //Handle verticalCenter
            if (verticalCenter.item == item->parent()) {
                this->setItemY(adjustedPosition(verticalCenter.item, verticalCenter.line)
                                 - item->property("height").toInt() / 2 + verticalCenterOffset);
            }
            else if (verticalCenter.item->parent() == item->parent()) {
                this->setItemY(position(verticalCenter.item, verticalCenter.line) - item->property("height").toInt() / 2 + verticalCenterOffset);
            }
        }

        --updatingVerticalAnchor;
    }
    else {
        // ### Make this certain :)
        qmlInfo(item) << Anchors::tr("Possible anchor loop detected on vertical anchor.");
    }
}

inline AnchorLine::Line reverseAnchorLine(AnchorLine::Line line) {
    if (line == AnchorLine::Left) {
        return AnchorLine::Right;
    }
    else if (line == AnchorLine::Right) {
        return AnchorLine::Left;
    }
    else {
        return line;
    }
}

void AnchorsPrivate::_q_updateHorizontalAnchors() {
    if ((fill) || (centerIn) || (!this->isItemComplete())) {
        return;
    }

    if (updatingHorizontalAnchor < 3) {
        ++updatingHorizontalAnchor;

        int effectiveRightMargin, effectiveLeftMargin, effectiveHorizontalCenterOffset;
        AnchorLine effectiveLeft, effectiveRight, effectiveHorizontalCenter;
        Anchors::Anchor effectiveLeftAnchor, effectiveRightAnchor;

        effectiveLeftAnchor = Anchors::LeftAnchor;
        effectiveRightAnchor = Anchors::RightAnchor;
        effectiveLeft = left;
        effectiveRight = right;
        effectiveHorizontalCenter = horizontalCenter;
        effectiveLeftMargin = leftMargin;
        effectiveRightMargin = rightMargin;
        effectiveHorizontalCenterOffset = horizontalCenterOffset;

        if (usedAnchors & effectiveLeftAnchor) {
            //Handle stretching
            bool invalid = true;
            int width = 0;

            if (usedAnchors & effectiveRightAnchor) {
                invalid = this->calcStretch(effectiveLeft, effectiveRight, effectiveLeftMargin, -effectiveRightMargin, AnchorLine::Left, width);
            }
            else if (usedAnchors & Anchors::HCenterAnchor) {
                invalid = this->calcStretch(effectiveLeft, effectiveHorizontalCenter, effectiveLeftMargin, effectiveHorizontalCenterOffset, AnchorLine::Left, width);
                width *= 2;
            }

            if (!invalid) {
                this->setItemWidth(width);
            }

            //Handle left
            if (effectiveLeft.item == item->parent()) {
                this->setItemX(adjustedPosition(effectiveLeft.item, effectiveLeft.line) + effectiveLeftMargin);
            }
            else if (effectiveLeft.item->parent() == item->parent()) {
                this->setItemX(position(effectiveLeft.item, effectiveLeft.line) + effectiveLeftMargin);
            }
        }
        else if (usedAnchors & effectiveRightAnchor) {
            //Handle stretching (left + right case is handled in updateLeftAnchor)
            if (usedAnchors & Anchors::HCenterAnchor) {
                int width = 0;
                bool invalid = this->calcStretch(effectiveHorizontalCenter, effectiveRight, effectiveHorizontalCenterOffset, -effectiveRightMargin,
                                                 AnchorLine::Left, width);
                if (!invalid) {
                    this->setItemWidth(width * 2);
                }
            }

            //Handle right
            if (effectiveRight.item == item->parent()) {
                this->setItemX(adjustedPosition(effectiveRight.item, effectiveRight.line) - item->property("width").toInt() - effectiveRightMargin);
            }
            else if (effectiveRight.item->parent() == item->parent()) {
                this->setItemX(position(effectiveRight.item, effectiveRight.line) - item->property("width").toInt() - effectiveRightMargin);
            }
        }
        else if (usedAnchors & Anchors::HCenterAnchor) {
            //Handle hCenter
            if (effectiveHorizontalCenter.item == item->parent()) {
                this->setItemX(adjustedPosition(effectiveHorizontalCenter.item, effectiveHorizontalCenter.line) - item->property("width").toInt() / 2 + effectiveHorizontalCenterOffset);
            }
            else if (effectiveHorizontalCenter.item->parent() == item->parent()) {
                this->setItemX(position(effectiveHorizontalCenter.item, effectiveHorizontalCenter.line) - item->property("width").toInt() / 2 + effectiveHorizontalCenterOffset);
            }
        }

        --updatingHorizontalAnchor;
    }
    else {
        // ### Make this certain :)
        qmlInfo(item) << Anchors::tr("Possible anchor loop detected on horizontal anchor.");
    }
}

#include "moc_anchors_p.cpp"
