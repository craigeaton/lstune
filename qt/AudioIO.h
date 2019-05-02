/*   Copyright 2010 Craig Eaton
 *
 *   This file is part of LSTune.
 *
 *    LSTune is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) 
 * any later version.
 *
 *   LSTune is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 *   You should have received a copy of the GNU General Public License along
 * with LSTune. If not, see http://www.gnu.org/licenses/.
 */ 

#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QBuffer>
#include <QWidget>
#include <QTimer>
#include "filter.h"

class AudioIO : public QWidget
{
  Q_OBJECT;

public:
  AudioIO(int fsample, int inFrameRate = 30, QWidget *parent = 0);
  ~AudioIO();
  void setNotifyInterval(int ms);

public slots:
  qint64 getAudio(float *inBuffer, int maxSamples);
  QList<QAudioDeviceInfo> getDevices();
  void start();
  void stop();
  void switchDevice(int deviceIndex);

 signals:
  void notify();

private:
  void initHW(QAudioDeviceInfo inDevice);

  // QT Sound objects
  QAudioInput *audioInput;
  QBuffer *IODevice;
  int fSample, frameRate;

  // List of audio devices
  QList<QAudioDeviceInfo> devices;

  // Read pointer for IODevice
  qint64 readPointer; 
  qint64 maxBufSize; // Maximum buffer size
  bool started;

  int notifyInterval;
};

#endif
