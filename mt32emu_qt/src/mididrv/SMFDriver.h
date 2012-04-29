#ifndef SMF_DRIVER_H
#define SMF_DRIVER_H

#include <QThread>

#include "MidiDriver.h"
#include "../Master.h"
#include "../MidiParser.h"
#include "../MasterClock.h"

class SMFDriver;

class SMFProcessor : public QThread {
	Q_OBJECT

public:
	SMFProcessor(SMFDriver *useSMFDriver);
	void start(QString fileName);
	void stop();
	void setTempo(uint newTempo);

protected:
	void run();

private:
	MidiParser parser;
	SMFDriver *driver;
	volatile bool stopProcessing;
	QString fileName;
	MasterClockNanos midiTick;

	static void sendAllNotesOff(SynthRoute *synthRoute);
};

class SMFDriver : public MidiDriver {
	Q_OBJECT
	friend class SMFProcessor;

public:
	SMFDriver(Master *master);
	~SMFDriver();
	void start();
	void start(QString fileName);
	void stop();

private:
	SMFProcessor processor;

signals:
	void playbackFinished();
	void playbackTimeChanged(quint64 currentNanos, quint32 totalSeconds);
};

#endif