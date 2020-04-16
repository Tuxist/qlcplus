/*
  Q Light Controller Plus
  scriptv4.cpp

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

#include <QDebug>
#include <typeinfo>

#include "function.h"
#include "scriptv3.h"
#include "scriptv4.h"
#include "script.h"

short Script::ScriptVersion=0;

const QString Script::startFunctionCmd = QString("startfunction");
const QString Script::stopFunctionCmd = QString("stopfunction");
const QString Script::blackoutCmd = QString("blackout");

const QString Script::waitCmd = QString("wait");
const QString Script::waitKeyCmd = QString("waitkey");

const QString Script::setFixtureCmd = QString("setfixture");
const QString Script::systemCmd = QString("systemcommand");

const QString Script::labelCmd = QString("label");
const QString Script::jumpCmd = QString("jump");

const QString Script::blackoutOn = QString("on");
const QString Script::blackoutOff = QString("off");

void *Script::operator new(size_t size)
{
    switch(Script::ScriptVersion){
        case 4:{
            size+=sizeof(ScriptV4);
            break;
        };
        case 3:{
            size+=sizeof(ScriptV3);
            break;
        };
        default:{
            qDebug("No Script Version Set !");
            exit(1);
        };
    }
    return ::operator new(size);
}

void *Script::operator new(size_t size,void *ptr)
{
    switch(Script::ScriptVersion){
        case 4:{
            size+=sizeof(ScriptV4);
            break;
        };
        case 3:{
            size+=sizeof(ScriptV3);
            break;
        };
        default:{
            qDebug("No Script Version Set !");
            exit(1);
        };
    }
    return ::operator new(size,ptr);
}

void Script::Reinitalize(Script* ins,Doc* doc){
    switch(Script::ScriptVersion){
        case 4:{
            ins=qobject_cast<Script*> (new (ins) ScriptV4(doc));
            break;
        }case 3:{
            ins=qobject_cast<Script*> (new (ins) ScriptV3(doc));
            break;
        }default:{
            qDebug("No Script Version Set !");
            exit(1);
        }
    }
}

Script::Script(Doc* doc,bool reinitalize) : ScriptApi(doc){
    if(reinitalize)
        Reinitalize(this,doc);
    else
        ScriptIns=NULL;
}

Script::~Script()
{
    if(this->ScriptIns && this->ScriptIns == this)
    {
        this->ScriptIns = NULL;
    }
    delete (Script*)this->ScriptIns;
}

QIcon Script::getIcon() const
{
    return ((Script*)ScriptIns)->getIcon();
};

quint32 Script::totalDuration()
{
    return ((Script*)ScriptIns)->totalDuration();
};

Function* Script::createCopy(Doc* doc, bool addToDoc)
{
    return ((Script*)ScriptIns)->createCopy(doc,addToDoc);
};

bool Script::copyFrom(const Function* function)
{
    return ((Script*)ScriptIns)->copyFrom(function);
};

bool Script::setData(const QString& str)
{
    return ((Script*)ScriptIns)->setData(str);
};

bool Script::appendData(const QString& str)
{
    return ((Script*)ScriptIns)->appendData(str);
};

QString Script::data() const
{
    return ((Script*)ScriptIns)->data();
};

QStringList Script::dataLines() const{
    return ((Script*)ScriptIns)->dataLines();
};

QList<quint32> Script::functionList() const
{
    return ((Script*)ScriptIns)->functionList();
};

QList<quint32> Script::fixtureList() const
{
    return ((Script*)ScriptIns)->fixtureList();
};

QList<int> Script::syntaxErrorsLines()
{
    return ((Script*)ScriptIns)->syntaxErrorsLines();
};

QStringList Script::syntaxErrorsLinesString()
{
    return ((Script*)ScriptIns)->syntaxErrorsLinesString();
};

void Script::preRun(MasterTimer *timer)
{
    ((Script*)ScriptIns)->preRun(timer);
};

void Script::write(MasterTimer *timer, QList<Universe*> universes)
{
    ((Script*)ScriptIns)->write(timer,universes);
};

void Script::postRun(MasterTimer *timer, QList<Universe*> universes)
{
    ((Script*)ScriptIns)->postRun(timer,universes);
};

bool Script::loadXML(QXmlStreamReader &root)
{
    return ((Script*)ScriptIns)->loadXML(root);
};

bool Script::saveXML(QXmlStreamWriter *doc)
{
    return ((Script*)ScriptIns)->saveXML(doc);
};

void Script::slotRunnerFinished()
{
    ((Script*)ScriptIns)->slotRunnerFinished();
};

ScriptApi::ScriptApi(Doc* doc) : Function(doc,Function::ScriptType){
    
}

ScriptApi::~ScriptApi(){
}
