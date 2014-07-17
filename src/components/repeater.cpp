#include "repeater_p.h"
#include "variantlistmodel_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QDeclarativeListReference>
#include <QWidget>
#include <QHashIterator>
#include <QEvent>

class RepeaterPrivate
{

public:
    RepeaterPrivate(Repeater *parent) :
        q_ptr(parent),
        model(0),
        delegateComponent(0),
        complete(false)
    {
    }

    virtual ~RepeaterPrivate() {}

    void _q_onRowsInserted(const QModelIndex &parent, int start, int end) {
        if (!complete) {
            return;
        }

        for (int i = start; i <= end; i++) {
            this->createItem(model->index(i, 0, parent));
        }
    }

    void _q_onRowsRemoved(const QModelIndex &parent, int start, int end) {
        Q_UNUSED(parent);

        if (!complete) {
            return;
        }

        for (int i = start; i <= end; i++) {
            this->removeItem(i);
        }
    }

    void _q_onRowsMoved(const QModelIndex & sourceParent, int sourceStart, int sourceEnd,
                        const QModelIndex & destinationParent, int destinationRow) {

        Q_UNUSED(sourceParent);
        Q_UNUSED(sourceStart);
        Q_UNUSED(sourceEnd);
        Q_UNUSED(destinationParent);
        Q_UNUSED(destinationRow);

        this->layoutItems();
    }

    void _q_onDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight) {
        const int start = topLeft.row();
        const int end = bottomRight.row();

        for (int i = start; i <= end; i++) {
            this->updateItem(model->index(i, 0));
        }
    }

    void layoutItems() {
        if (!complete) {
            return;
        }

        while (!widgetList.isEmpty()) {
            this->removeItem(0);
        }

        if (model) {
            for (int i = 0; i < model->rowCount(); i++) {
                this->createItem(model->index(i, 0));
            }
        }
    }

    void createItem(const QModelIndex &index) {
        Q_Q(Repeater);

        QWidget *parent = this->parentWidget();

        if (!parent) {
            qmlInfo(q) << Repeater::tr("Repeater can only be used inside a visual layout item");
            return;
        }

        QDeclarativeContext *creationContext = delegateComponent->creationContext();
        QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(q));

        if (QObject *obj = delegateComponent->beginCreate(context)) {
            if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
                widget->setParent(parent);
                context->setParent(widget);
                context->setContextProperty("index", index.row());

                QHashIterator<int, QByteArray> iterator(model->roleNames());

                while (iterator.hasNext()) {
                    iterator.next();
                    context->setContextProperty(iterator.value(), index.data(iterator.key()));
                }

                delegateComponent->completeCreate();

                QDeclarativeListReference data(parent, "data");

                if ((data.canAppend()) && (data.append(widget))) {
                    widgetList.append(widget);
                    emit q->itemAdded(widgetList.size() - 1, widget);
                    emit q->countChanged();
                }
                else {
                    qmlInfo(q) << Repeater::tr("Repeater can only be used inside a visual layout item");
                    delete widget;
                }
            }
            else {
                qmlInfo(q) << Repeater::tr("Repeater does not support loading non-visual elements.");
                delete obj;
                delete context;
            }
        }
        else {
            delete context;
        }
    }

    void removeItem(int i) {
        if ((i >= 0) && (i < widgetList.size())) {
            if (QWidget *widget = widgetList.takeAt(i)) {
                Q_Q(Repeater);
                emit q->itemRemoved(i, widget);
                emit q->countChanged();
                widget->deleteLater();
            }
        }
    }

    void updateItem(const QModelIndex &index) {
        const int i = index.row();

        if ((i >= 0) && (i < widgetList.size())) {
            Q_Q(Repeater);
            if (QWidget *widget = widgetList.at(i)) {
                QDeclarativeContext *context = qmlContext(widget);
                context->setContextProperty("index", i);

                QHashIterator<int, QByteArray> iterator(model->roleNames());

                while (iterator.hasNext()) {
                    iterator.next();
                    context->setContextProperty(iterator.value(), index.data(iterator.key()));
                }
            }
        }
    }

    QWidget* parentWidget() const {
        Q_Q(const Repeater);

        bool isWidget = false;
        QObject *parent = q->parent();

        while ((parent) && (!isWidget)) {
            isWidget = parent->isWidgetType();

            if (!isWidget) {
                parent = parent->parent();
            }
        }

        if ((parent) && (isWidget)) {
            return qobject_cast<QWidget*>(parent);
        }

        return 0;
    }

    Repeater *q_ptr;

    QVariant modelVariant;

    QAbstractItemModel *model;

    QDeclarativeComponent *delegateComponent;

    bool complete;

    QList<QWidget*> widgetList;

    Q_DECLARE_PUBLIC(Repeater)
};

Repeater::Repeater(QObject *parent) :
    QObject(parent),
    d_ptr(new RepeaterPrivate(this))
{
}

Repeater::Repeater(RepeaterPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Repeater::~Repeater() {}

QVariant Repeater::model() const {
    Q_D(const Repeater);

    return d->modelVariant;
}

void Repeater::setModel(const QVariant &model) {
    if (model == this->model()) {
        return;
    }

    Q_D(Repeater);

    QAbstractItemModel *oldModel = d->model;
    d->model = 0;
    d->modelVariant = model;
    QObject *obj = qvariant_cast<QObject*>(model);
    QAbstractItemModel *itemModel = 0;

    if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
        d->model = itemModel;
    }
    else {
        VariantListModel *variantModel = new VariantListModel(this);
        variantModel->setVariant(model);
        d->model = variantModel;
    }

    this->connect(d->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                  this, SLOT(_q_onRowsInserted(QModelIndex,int,int)), Qt::UniqueConnection);
    this->connect(d->model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                  this, SLOT(_q_onRowsRemoved(QModelIndex,int,int)), Qt::UniqueConnection);
    this->connect(d->model, SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
                  this, SLOT(_q_onRowsMoved(QModelIndex,int,int,QModelIndex,int)), Qt::UniqueConnection);
    this->connect(d->model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                  this, SLOT(_q_onDataChanged(QModelIndex,QModelIndex)), Qt::UniqueConnection);

    if (oldModel) {
        delete oldModel;
    }

    emit modelChanged();

    if (d->complete) {
        d->layoutItems();
    }
}

QDeclarativeComponent* Repeater::delegate() const {
    Q_D(const Repeater);

    return d->delegateComponent;
}

void Repeater::setDelegate(QDeclarativeComponent *delegate) {
    Q_D(Repeater);

    if (delegate != d->delegateComponent) {
        QDeclarativeComponent *oldDelegate = d->delegateComponent;
        d->delegateComponent = delegate;

        if (d->delegateComponent) {
            d->delegateComponent->setParent(this);
        }

        if (oldDelegate) {
            delete oldDelegate;
        }

        emit delegateChanged();

        if (d->complete) {
            d->layoutItems();
        }
    }
}

int Repeater::count() const {
    Q_D(const Repeater);

    return d->widgetList.size();
}

QWidget* Repeater::itemAt(int index) const {
    Q_D(const Repeater);

    if ((index > 0) && (index < d->widgetList.size())) {
        return d->widgetList.at(index);
    }

    return 0;
}

void Repeater::classBegin() {}

void Repeater::componentComplete() {
    Q_D(Repeater);

    d->complete = true;
    d->layoutItems();
}

bool Repeater::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    return QObject::event(event);
}

#include "moc_repeater_p.cpp"
