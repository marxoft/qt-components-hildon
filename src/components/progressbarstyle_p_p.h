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

#ifndef PROGRESSBARSTYLE_P_P_H
#define PROGRESSBARSTYLE_P_P_H

#include "progressbarstyle_p.h"
#include "boxstyle_p_p.h"

class ProgressBarStylePrivate : public BoxStylePrivate
{

public:
    ProgressBarStylePrivate(ProgressBarStyle *parent);
    
    virtual QString chunkBody() const;
    virtual QString mainBody() const;
    
    Style *chunk;
    
    Qt::Alignment textAlignment;
    
    Q_DECLARE_PUBLIC(ProgressBarStyle)
};

#endif // PROGRESSBARSTYLE_P_P_H

