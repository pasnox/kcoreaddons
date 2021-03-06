/*
    This file is part of the KDE Frameworks

    SPDX-FileCopyrightText: 2011 Nokia Corporation and/or its subsidiary(-ies).
    SPDX-FileCopyrightText: 2019 David Hallas <david@davidhallas.dk>

    SPDX-License-Identifier: LGPL-2.1-only WITH Qt-LGPL-exception-1.1 OR LicenseRef-Qt-Commercial
*/

#ifndef KPROCESSLIST_P_H
#define KPROCESSLIST_P_H

#include <QSharedData>
#include "kprocesslist.h"

namespace KProcessList
{

class KProcessInfoPrivate : public QSharedData {
public:
    KProcessInfoPrivate();

    bool valid;
    qint64 pid;
    QString name;
    QString user;
    QString command;
};

} // KProcessList namespace

#endif // KPROCESSLIST_P_H
