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


#ifndef TEXTEDITAUTORESIZER_P_P_H
#define TEXTEDITAUTORESIZER_P_P_H

#include <QTextEdit>
#include <QAbstractKineticScroller>

class TextEditAutoResizer : public QObject
{
    Q_OBJECT

public:
    TextEditAutoResizer(QTextEdit *parent)
        : QObject(parent),
          textEdit(parent),
          edit(qobject_cast<QFrame*>(parent))
    {
        this->connect(parent, SIGNAL(textChanged()), this, SLOT(textEditChanged()));
        this->connect(parent, SIGNAL(cursorPositionChanged()), this, SLOT(textEditChanged()));
    }

private slots:
    inline void textEditChanged();

private:
    QTextEdit *textEdit;
    QFrame *edit;
};

void TextEditAutoResizer::textEditChanged() {
    QRect cursor = textEdit->cursorRect();
    QSize s = textEdit->document()->size().toSize();

    const QRect fr = edit->frameRect();
    const QRect cr = edit->contentsRect();

    edit->setMinimumWidth(qMax(70, s.width() + (fr.width() - cr.width() - 1)));
    edit->setMinimumHeight(qMax(70, s.height() + (fr.height() - cr.height() - 1)));

    // make sure the cursor is visible in case we have a QAbstractScrollArea parent
    QPoint pos = edit->pos();
    QWidget *pw = edit->parentWidget();

    while (pw) {
        if (pw->parentWidget()) {
            if (QAbstractScrollArea *area = qobject_cast<QAbstractScrollArea*>(
                        pw->parentWidget()->parentWidget())) {
                if (QAbstractKineticScroller * scroller =
                        area->property("kineticScroller").value<QAbstractKineticScroller*>()) {
                    scroller->ensureVisible(pos + cursor.center(), 10 + cursor.width(),
                                            2 * cursor.height());
                }

                break;
            }
        }

        pos = pw->mapToParent(pos);
        pw = pw->parentWidget();
    }
}

#endif // TEXTEDITAUTORESIZER_P_P_H
