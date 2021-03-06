/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 2000 Stephan Kulow <coolo@kde.org>
    SPDX-FileCopyrightText: 2000 David Faure <faure@kde.org>
    SPDX-FileCopyrightText: 2006 Kevin Ottens <ervin@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kjobuidelegate.h"
#include "kjob.h"

class Q_DECL_HIDDEN KJobUiDelegate::Private
{
public:
    Private(KJobUiDelegate *delegate)
        : q(delegate), job(nullptr),
          autoErrorHandling(false),
          autoWarningHandling(true) { }

    KJobUiDelegate *const q;

    KJob *job;
    bool autoErrorHandling : 1;
    bool autoWarningHandling : 1;

    void connectJob(KJob *job);
    void _k_result();
};

KJobUiDelegate::KJobUiDelegate()
    : QObject(), d(new Private(this))
{
}

KJobUiDelegate::KJobUiDelegate(Flags flags)
    : QObject(), d(new Private(this))
{
    if (flags & AutoErrorHandlingEnabled) {
        d->autoErrorHandling = true;
    }
    if (flags & AutoWarningHandlingEnabled) {
        d->autoWarningHandling = true;
    }
}

KJobUiDelegate::~KJobUiDelegate()
{
    delete d;
}

bool KJobUiDelegate::setJob(KJob *job)
{
    if (d->job != nullptr) {
        return false;
    }

    d->job = job;
    setParent(job);

    return true;
}

KJob *KJobUiDelegate::job() const
{
    return d->job;
}

void KJobUiDelegate::showErrorMessage()
{
}

void KJobUiDelegate::setAutoErrorHandlingEnabled(bool enable)
{
    d->autoErrorHandling = enable;
}

bool KJobUiDelegate::isAutoErrorHandlingEnabled() const
{
    return d->autoErrorHandling;
}

void KJobUiDelegate::setAutoWarningHandlingEnabled(bool enable)
{
    d->autoWarningHandling = enable;
}

bool KJobUiDelegate::isAutoWarningHandlingEnabled() const
{
    return d->autoWarningHandling;
}

void KJobUiDelegate::slotWarning(KJob *job, const QString &plain,
                                 const QString &rich)
{
    Q_UNUSED(job)
    Q_UNUSED(plain)
    Q_UNUSED(rich)
}

void KJobUiDelegate::connectJob(KJob *job)
{
    connect(job, &KJob::result, this, [this](){ d->_k_result();} );
    connect(job, &KJob::warning, this, &KJobUiDelegate::slotWarning);
}

void KJobUiDelegate::Private::_k_result()
{
    if (job->error() && autoErrorHandling) {
        q->showErrorMessage();
    }
}

#include "moc_kjobuidelegate.cpp"
