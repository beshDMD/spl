/*-------------------------------------------------------------------------
	    Copyright 2013 Damage Control Engineering, LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*-------------------------------------------------------------------------*/
#ifndef DcMidi_h__
#define DcMidi_h__


#include <QStringList>
#include <QHash>
#include <QTextStream>
#include <QObject>

#include <string>
#include <cmn/DcLog.h>

#include "DcMidiData.h"

static const int kNotOpen = -1;

// Control exception handling
#undef QRTMIDI_USE_TRY

class RtMidi;

class DcMidi : public QObject
{
    Q_OBJECT

public:
    
    DcMidi(QObject* parent);
    DcMidi();
    virtual ~DcMidi() {};

    bool init();
    void destroy();

    bool update();

    bool open(QString portName = "",quint32 flags = 0);
    void close();

    int getPortCount();
    bool isOpen();

    QStringList getPortNames();
    QString getLastErrorString();
    
    /*!
      Return the midi interface port name
    */ 
    QString getPortName() const { return _curPortName; }

    virtual void setLoglevel( int val ) 
    { 
        _loglevel = val; 
    }
    virtual int getLoglevel() const 
    { 
        return _loglevel; 
    }

protected:
    virtual void stopIo() {}
    virtual void setupAfterOpen(quint32 flags=0) {Q_UNUSED(flags);};

    virtual RtMidi* getRtMidi() = 0;
    virtual bool createRtMidiDev() = 0;
    virtual void destoryRtMidiDev() = 0;
    

    void buildPortNameList(RtMidi* pRtMidi);
    QString filterPortName( QString& portName );

    bool isOk();

    void setError(const char* msg, const std::string& msg2 );
    void setError( const char* msg);
    void setError(const char* msg1,QString msg2,const char* msg3);

    void clearLastStatus();
    
    



private:   
    QString _lastError;

    QHash<QString,int> _portNameIndexHash;

    // What the caller wants to use
    QString _curPortName;
    
    // Control what gets logged: 0 is off
    int _loglevel;

    // What is currently open
    int _curOpenPortIdx;
};

#endif // DcMidi_h__
