/*
 * This file is part of crash-reporter
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Ville Ilvonen <ville.p.ilvonen@nokia.com>
 * Author: Riku Halonen <riku.halonen@nokia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef UT_CREPORTERDAEMONPROXY_H
#define UT_CREPORTERDAEMONPROXY_H

#include <QTest>
#include <QStringList>

class CReporterDaemonProxy;
class CReporterDaemon;
class QSettings;

class Ut_CReporterDaemonProxy : public QObject
{
	Q_OBJECT

private slots:

	void initTestCase();
	void init();

    void testProxyCollectAllCoreFiles();

	void cleanupTestCase();
	void cleanup();

private:

    CReporterDaemonProxy *proxy;
    CReporterDaemon *daemon;
    QSettings *settings;
};

#endif // UT_CREPORTERDAEMONPROXY_H
