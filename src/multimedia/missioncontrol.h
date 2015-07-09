#ifndef MISSIONCONTROL_P_H
#define MISSIONCONTROL_P_H

#include <QObject>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

#include "mafw/mafwregistryadapter.h"

class MissionControl : public QObject
{
    Q_OBJECT

public:
    static MissionControl* acquire();

private:
    static MissionControl *instance;

    MafwRegistryAdapter *mafwRegistry;
    MafwRendererAdapter *mafwRenderer;

    int mafwState;

    bool metadataReady;

    bool pausedByCall;
    bool wasRinging;

    bool wiredHeadsetIsConnected;
    qint64 headsetPauseStamp;
    QTimer *wirelessResumeTimer;

    MissionControl();

    void togglePlayback();
    void handlePhoneButton();

private slots:
    void onStatusReceived(MafwPlaylist *, uint, MafwPlayState state, const char *, QString);
    void onStateChanged(int state);

    void onCallStateChanged(QDBusMessage msg);

    void onWirelessHeadsetConnected();
    void onHeadsetConnected();
    void onHeadsetDisconnected();
    void onHeadsetButtonPressed(QDBusMessage msg);
    void updateWiredHeadset();
};

#endif // MISSIONCONTROL_P_H
