#include "missioncontrol_p.h"
#include <QDateTime>

#define HAL_PATH_RX51_JACK "/org/freedesktop/Hal/devices/platform_soc_audio_logicaldev_input"

MissionControl* MissionControl::instance = NULL;

MissionControl* MissionControl::acquire()
{
    return instance ? instance : instance = new MissionControl();
}

MissionControl::MissionControl() :
    QObject()
{
    mafwState = Transitioning;

    metadataReady = false;

    pausedByCall = false;
    wasRinging = false;

    wiredHeadsetIsConnected = false;
    headsetPauseStamp = -1;
    wirelessResumeTimer = NULL;

    mafwRegistry = MafwRegistryAdapter::get();
    mafwRenderer = mafwRegistry->renderer();

    connect(mafwRenderer, SIGNAL(rendererReady()), mafwRenderer, SLOT(getStatus()));
    connect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
            this, SLOT(onStatusReceived(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

    QDBusConnection::systemBus().connect("", "", "org.bluez.AudioSink", "Connected",
                                         this, SLOT(onWirelessHeadsetConnected()));
    QDBusConnection::systemBus().connect("", "", "org.bluez.AudioSink", "Disconnected",
                                         this, SLOT(onHeadsetDisconnected()));
    QDBusConnection::systemBus().connect("", "", "org.bluez.Headset", "Connected",
                                         this, SLOT(onWirelessHeadsetConnected()));
    QDBusConnection::systemBus().connect("", "", "org.bluez.Headset", "Disconnected",
                                         this, SLOT(onHeadsetDisconnected()));

    QDBusConnection::systemBus().connect("", "/org/freedesktop/Hal/devices/platform_headphone", "org.freedesktop.Hal.Device", "PropertyModified",
                                         this, SLOT(updateWiredHeadset()));

    QDBusConnection::systemBus().connect("", "", "org.freedesktop.Hal.Device", "Condition",
                                         this, SLOT(onHeadsetButtonPressed(QDBusMessage)));

    QDBusConnection::systemBus().connect("", "", "com.nokia.mce.signal", "sig_call_state_ind",
                                         this, SLOT(onCallStateChanged(QDBusMessage)));

    updateWiredHeadset();
}

void MissionControl::togglePlayback()
{
    if (mafwState == Playing) {
        mafwRenderer->pause();
    } else if (mafwState == Paused) {
        mafwRenderer->resume();
    } else if (mafwState == Stopped) {
        mafwRenderer->play();
    }
}

void MissionControl::onStatusReceived(MafwPlaylist *, uint, MafwPlayState state, const char *, QString)
{
    disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
               this, SLOT(onStatusReceived(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

    connect(mafwRenderer, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));

    onStateChanged(state);

}

void MissionControl::onStateChanged(int state)
{
    mafwState = state;

    if (state == Playing) {
        headsetPauseStamp = -1;
        pausedByCall = false;
    }
}

void MissionControl::onCallStateChanged(QDBusMessage msg)
{
    QString state = msg.arguments()[0].toString();

    if (state == "ringing") {
        wasRinging = true;
        pausedByCall = mafwState == Playing;
        if (pausedByCall) mafwRenderer->pause();
    }
    else if (!wasRinging && state == "active") {
        pausedByCall = mafwState == Playing;
        if (pausedByCall) mafwRenderer->pause();
    }
    else if (state == "none") {
        if (pausedByCall && headsetPauseStamp == -1)
            mafwRenderer->resume();
        pausedByCall = false;
        wasRinging = false;
    }
}

void MissionControl::handlePhoneButton()
{
    if (mafwState == Playing) {
        mafwRenderer->next();
    } else {
        togglePlayback();
    }
}

// The purpose of distinction between wired and wireless headset is to postpone
// playback resuming when Bluetooth headset is connected. This is needed because
// the signal from Bluetooth daemon arrives before audio system is reconfigured,
// which results in OMP playing via internal speakers for 1-2 seconds.
void MissionControl::onWirelessHeadsetConnected()
{
    if (wirelessResumeTimer) {
        wirelessResumeTimer->stop();
    } else {
        wirelessResumeTimer = new QTimer(this);
        wirelessResumeTimer->setSingleShot(true);
        connect(wirelessResumeTimer, SIGNAL(timeout()), this, SLOT(onHeadsetConnected()));
    }
    wirelessResumeTimer->start(4000);
}

void MissionControl::onHeadsetConnected()
{
    if (headsetPauseStamp != -1
    &&  mafwState == Paused
    && !pausedByCall)
        mafwRenderer->resume();

    headsetPauseStamp = -1;
}

void MissionControl::onHeadsetDisconnected()
{
    if (mafwState == Playing) {
        mafwRenderer->pause();
        headsetPauseStamp = QDateTime::currentMSecsSinceEpoch();
    } else if (pausedByCall) {
        headsetPauseStamp = QDateTime::currentMSecsSinceEpoch();
    }
    if (wirelessResumeTimer) {
        disconnect(wirelessResumeTimer, SIGNAL(timeout()), this, SLOT(onHeadsetConnected()));
        wirelessResumeTimer->stop();
        wirelessResumeTimer->deleteLater();
        wirelessResumeTimer = NULL;
    }
}

void MissionControl::updateWiredHeadset()
{
    QDBusInterface jackInterface("org.freedesktop.Hal", HAL_PATH_RX51_JACK, "org.freedesktop.Hal.Device", QDBusConnection::systemBus(), this);
    QDBusInterface buttInterface("org.freedesktop.Hal", "/org/freedesktop/Hal/devices/platform_headphone", "org.freedesktop.Hal.Device", QDBusConnection::systemBus(), this);

    if (!jackInterface.isValid() || !buttInterface.isValid()) return;

    // State contains jack GPIO state -- false when nothing is connected to jack
    bool state = QDBusReply<bool>(buttInterface.call("GetProperty", "button.state.value"));

    // The list contains "headphone" when headset is connected
    bool connected = state && QDBusReply<QStringList>(jackInterface.call("GetProperty", "input.jack.type")).value().contains("headphone");

    if (connected && !wiredHeadsetIsConnected) {
        onHeadsetConnected();
        wiredHeadsetIsConnected = true;
    } else if (!connected && wiredHeadsetIsConnected) {
        onHeadsetDisconnected();
        wiredHeadsetIsConnected = false;
    }
}

void MissionControl::onHeadsetButtonPressed(QDBusMessage msg)
{
    if (msg.arguments()[0] == "ButtonPressed") {
        if (msg.arguments()[1] == "play-cd" || msg.arguments()[1] == "pause-cd")
            togglePlayback();
        else if (msg.arguments()[1] == "stop-cd")
            mafwRenderer->stop();
        else if (msg.arguments()[1] == "next-song")
            mafwRenderer->next();
        else if (msg.arguments()[1] == "previous-song")
            mafwRenderer->previous();
        else if (msg.arguments()[1] == "fast-forward")
            mafwRenderer->setPosition(SeekRelative, 3);
        else if (msg.arguments()[1] == "rewind")
            mafwRenderer->setPosition(SeekRelative, -3);
        else if (msg.arguments()[1] == "phone")
            handlePhoneButton();
        else if (msg.arguments()[1] == "jack_insert" && msg.path() == HAL_PATH_RX51_JACK) // wired headset was connected or disconnected
            updateWiredHeadset();
    }
}
