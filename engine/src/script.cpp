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
#include <string.h>

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
            exit(1);
        };
    }
    return ::operator new(size,ptr);
}

void Script::Reinitalize(Script* ins,Doc* doc){
    switch(Script::ScriptVersion){
        case 4:{
            ins=new (ins) ScriptV4(doc);
            break;
        }case 3:{
            ins=new (ins) ScriptV3(doc);
            break;
        }default:{
            exit(1);
        }
    }
}

Script::Script(Doc* doc,bool reinitalize) : ScriptApi(doc){
    if(reinitalize){
        Reinitalize(this,doc);
        qobject_cast<Script*> (this);
    }
}

Script::~Script()
{
}

QIcon Script::getIcon() const
{
    return QIcon(0);
};

quint32 Script::totalDuration()
{
    return 0;
};

Function* Script::createCopy(Doc* doc, bool addToDoc)
{
    return 0;
};

bool Script::copyFrom(const Function* function)
{
    return false;
};

bool Script::setData(const QString& str)
{
    return false;
};

bool Script::appendData(const QString& str)
{
    return false;
};

QString Script::data() const
{
    return 0;
};

QStringList Script::dataLines() const{
    return QStringList(0);
};

QList<quint32> Script::functionList() const
{
    return {0};
};

QList<quint32> Script::fixtureList() const
{
    return {0};
};

QList<int> Script::syntaxErrorsLines()
{
    return{0};
};

QStringList Script::syntaxErrorsLinesString()
{
    return {0};
};

void Script::preRun(MasterTimer *timer)
{
};

void Script::write(MasterTimer *timer, QList<Universe*> universes)
{
};

void Script::postRun(MasterTimer *timer, QList<Universe*> universes)
{
};

bool Script::loadXML(QXmlStreamReader &root)
{
    return false;
};

bool Script::saveXML(QXmlStreamWriter *doc)
{
    return false;
};

void Script::slotRunnerFinished()
{
};

ScriptApi::ScriptApi(Doc* doc) : Function(doc,Function::ScriptType){
    
}

ScriptApi::~ScriptApi(){
    
}
