/*
  Q Light Controller Plus
  script.h

  Copyright (C) Jan Koester

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef SCRIPT_H
#define SCRIPT_H

#include <QStringList>
#include <QObject>
#include <QMap>
#include <QList>

#include "function.h"

class ScriptRunner;
class MasterTimer;
class Universe;
class Doc;

class ScriptApi : public Function
{
    Q_OBJECT
public:
    ScriptApi(Doc* doc);
    virtual ~ScriptApi();
    virtual QIcon getIcon() const=0;
    virtual quint32 totalDuration()=0;
    virtual Function* createCopy(Doc* doc, bool addToDoc = true)=0;
    virtual bool copyFrom(const Function* function)=0;
    virtual bool setData(const QString& str)=0;
    virtual bool appendData(const QString& str)=0;
    virtual QString data() const =0;
    virtual QStringList dataLines() const =0;
    virtual QList<quint32> functionList() const=0;
    virtual QList<quint32> fixtureList() const=0;
    virtual bool loadXML(QXmlStreamReader &root)=0;
    virtual bool saveXML(QXmlStreamWriter *doc)=0;
    virtual QList<int> syntaxErrorsLines()=0;
    virtual QStringList syntaxErrorsLinesString()=0;
    virtual void preRun(MasterTimer *timer)=0;
    virtual void write(MasterTimer *timer, QList<Universe*> universes)=0;
    virtual void postRun(MasterTimer *timer, QList<Universe*> universes)=0;
protected slots:
    virtual void slotRunnerFinished()=0;

    friend class Script;
};

class Script : public ScriptApi
{
    Q_OBJECT

public:
     /************************************************************************
     * Script keywords
     ************************************************************************/
    static const QString startFunctionCmd;
    static const QString stopFunctionCmd;
    static const QString blackoutCmd;

    static const QString waitCmd;
    static const QString waitKeyCmd;

    static const QString setFixtureCmd;
    static const QString systemCmd;

    static const QString labelCmd;
    static const QString jumpCmd;

    static const QString blackoutOn;
    static const QString blackoutOff;

public:
    static short ScriptVersion;
    Script(Doc* doc,bool reinitalize=true);
    virtual ~Script();
    void *operator new(size_t size);
    void *operator new(size_t size,void *ptr);
    static void Reinitalize(Script* ins,Doc* doc);
    QIcon getIcon() const override;
    quint32 totalDuration() override ;
    Function* createCopy(Doc* doc, bool addToDoc = true) override;
    bool copyFrom(const Function* function) override;
    bool setData(const QString& str) override;
    bool appendData(const QString& str) override;
    QString data() const override;
    QStringList dataLines() const override;
    QList<quint32> functionList() const override;
    QList<quint32> fixtureList() const override;
    QList<int> syntaxErrorsLines() override;
    QStringList syntaxErrorsLinesString() override;
    void preRun(MasterTimer *timer) override;
    void write(MasterTimer *timer, QList<Universe*> universes) override;
    void postRun(MasterTimer *timer, QList<Universe*> universes) override;
    bool loadXML(QXmlStreamReader &root) override;
    bool saveXML(QXmlStreamWriter *doc) override;
protected slots:
    virtual void slotRunnerFinished();
};

#endif
 
