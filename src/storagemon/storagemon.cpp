/*
 * This file is part of crash-reporter
 *
 * Copyright (C) 2017 Jolla Ltd.
 * Contact: Martin Kampas <martin.kampas@jolla.com>
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

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QTranslator>

#include "creporterapplicationsettings.h"
#include "creportercoreregistry.h"
#include "creporternamespace.h"
#include "creporternotification.h"
#include "creportersavedstate.h"
#include "creporterutils.h"

#ifndef QT_NO_DEBUG_OUTPUT
#include "creporterlogger.h"
#endif

constexpr int TOO_MUCH_BYTES = 100 << 20;

using CReporter::LoggingCategory::cr;

/*!
  * @brief Crash Reporter storage usage monitor application.
  */
class Application : public QCoreApplication
{
    Q_OBJECT

public:
    /*!
      * @brief Constructor
      *
      * @param argc Argument count.
      * @param argv Arguments.
      */
    Application(int argc, char **argv)
        : QCoreApplication(argc, argv)
    {
        QTranslator *translator = new QTranslator(this);
        translator->load("crash-reporter_eng_en", "/usr/share/translations");
        installTranslator(translator);

        QTimer::singleShot(0, this, &Application::run);
    }

    ~Application()
    {
        CReporterApplicationSettings::freeSingleton();
    }

private:
    void run()
    {
        checkStorageUsage();
        quit();
    }

    void checkStorageUsage()
    {

        qint64 totalSize = 0;
        CReporterCoreRegistry *registry = CReporterCoreRegistry::instance();
        foreach (const QString &coreFile, registry->collectAllCoreFiles()) {
            totalSize += QFileInfo(coreFile).size();
        }

        if (totalSize < TOO_MUCH_BYTES) {
            qCDebug(cr) << "Low storage usage - will not be reported";
            return;
        }

        qCDebug(cr) << "High storage usage - will be reported";

        CReporterSavedState *state = CReporterSavedState::instance();

        CReporterNotification notification(CReporter::StorageUsageNotificationEventType,
                state->storageUsageNotificationId(), this);

        //% "Many crash reports available"
        notification.update(
                qtTrId("crash_reporter-notify-storage_usage"),
                //% "You should upload or delete some of them. You have %1 MiB of crash data."
                qtTrId("crash_reporter-notify-storage_usage_body").arg(totalSize >> 20));

        state->setStorageUsageNotificationId(notification.id());

        CReporterSavedState::freeSingleton();
    }

};

/*!
  * @brief Crash Reporter storage usage monitor main function.
  *
  * @param argc Argument count.
  * @param argv Arguments.
  */
Q_DECL_EXPORT int main(int argc, char **argv)
{
#ifndef QT_NO_DEBUG_OUTPUT
    Logger logger(CReporterApplicationSettings::instance()->loggerType());
#endif

    Application app(argc, argv);
    return app.exec();
}

#include "storagemon.moc"
