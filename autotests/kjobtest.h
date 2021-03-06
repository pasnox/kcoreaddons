/*
    This file is part of the KDE project
    SPDX-FileCopyrightText: 2006 Kevin Ottens <ervin@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KJOBTEST_H
#define KJOBTEST_H

#include <QObject>
#include <QEventLoop>
#include "kjob.h"
#include "kjobuidelegate.h"

class TestJob : public KJob
{
    Q_OBJECT
public:
    TestJob();
    ~TestJob() override;

    void start() override;

protected:
    bool doKill() override;

public:
    void setError(int errorCode);
    void setErrorText(const QString &errorText);
    void setProcessedSize(qulonglong size);
    void setTotalSize(qulonglong size);
    void setPercent(unsigned long percentage);

private Q_SLOTS:
    void doEmit();
};

class TestJobUiDelegate : public KJobUiDelegate
{
    Q_OBJECT
protected:
    virtual void connectJob(KJob *job);
};

class WaitJob;

class KJobTest : public QObject
{
    Q_OBJECT
public:
    KJobTest();

public Q_SLOTS:

    // These slots need to be public, otherwise qtestlib calls them as part of the test
    void slotStartInnerJob();
    void slotFinishOuterJob();
    void slotFinishInnerJob();

private Q_SLOTS:
    void testEmitResult_data();
    void testEmitResult();
    void testProgressTracking();
    void testExec_data();
    void testExec();
    void testKill_data();
    void testKill();
    void testDelegateUsage();
    void testNestedExec();

    void slotResult(KJob *job);
    void slotFinished(KJob *job);

private:
    QEventLoop loop;
    int m_lastError;
    QString m_lastErrorText;
    int m_resultCount;
    int m_finishedCount;

    WaitJob *m_outerJob;
    WaitJob *m_innerJob;
};

class WaitJob : public KJob
{
    Q_OBJECT
public:

    void start() override;
    void makeItFinish();
};

#endif

