/*!
 *   @brief Auterion QGCCorePlugin Declaration
 *   @author Gus Grubba <gus@grubba.com>
 */

#pragma once

#include "QGCCorePlugin.h"
#include "QGCOptions.h"
#include "QGCLoggingCategory.h"
#include "VideoReceiver.h"
#include "SettingsManager.h"

#include <QTranslator>

class AuterionPlugin;
class AuterionSettings;

Q_DECLARE_LOGGING_CATEGORY(AuterionLog)

class AuterionVideoReceiver : public VideoReceiver
{
    Q_OBJECT
public:

    explicit AuterionVideoReceiver(QObject* parent = nullptr);
    ~AuterionVideoReceiver();

};

//-----------------------------------------------------------------------------
class AuterionOptions : public QGCOptions
{
public:
    AuterionOptions(AuterionPlugin*, QObject* parent = nullptr);
    bool        wifiReliableForCalibration      () const final { return true; }
    QUrl        flyViewOverlay                  () const final { return QUrl::fromUserInput("qrc:/auterion/AuterionFlyView.qml"); }
    CustomInstrumentWidget* instrumentWidget    () final { return nullptr; }
    double      toolbarHeightMultiplier         () final;
};


//-----------------------------------------------------------------------------
class AuterionPlugin : public QGCCorePlugin
{
    Q_OBJECT
public:
    AuterionPlugin(QGCApplication* app, QGCToolbox *toolbox);
    ~AuterionPlugin();

    // Overrides from QGCCorePlugin
    QGCOptions*             options                         () final;
    QString                 brandImageIndoor                () const final;
    QString                 brandImageOutdoor               () const final;
    bool                    overrideSettingsGroupVisibility (QString name) final;
    VideoReceiver*          createVideoReceiver             (QObject* parent) final;
    QQmlApplicationEngine*  createRootWindow                (QObject* parent) final;
    bool                    adjustSettingMetaData           (const QString& settingsGroup, FactMetaData& metaData) final;

    // Overrides from QGCTool
    void                    setToolbox                      (QGCToolbox* toolbox);

private:
    AuterionOptions*     _pOptions;
};
