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

Script::Script(Doc* doc,bool reinitalize) : ScriptApi(doc){
    if(reinitalize){
        this->~Script();
        switch(ScriptVersion){
            case 4:{
                new (this) ScriptV4(doc);
                qobject_cast<Script*> (this);
                break;
            }case 3:{
                new (this) ScriptV3(doc);
                qobject_cast<Script*> (this);
                break;
            }default:{
                exit(1);
            }
        }
    }
}

Script::~Script(){
}

QIcon Script::getIcon() const{return QIcon(0);};
quint32 Script::totalDuration(){};
Function* Script::createCopy(Doc* doc, bool addToDoc){};
bool Script::copyFrom(const Function* function){};
bool Script::setData(const QString& str){};
bool Script::appendData(const QString& str){};
QString Script::data() const{};
QStringList Script::dataLines() const{};
QList<quint32> Script::functionList() const{};
QList<quint32> Script::fixtureList() const{};
QList<int> Script::syntaxErrorsLines(){};
QStringList Script::syntaxErrorsLinesString(){};
void Script::preRun(MasterTimer *timer){};
void Script::write(MasterTimer *timer, QList<Universe*> universes){};
void Script::postRun(MasterTimer *timer, QList<Universe*> universes){};
bool Script::loadXML(QXmlStreamReader &root){};
bool Script::saveXML(QXmlStreamWriter *doc){};

void Script::slotRunnerFinished(){};

ScriptApi::ScriptApi(Doc* doc) : Function(doc,Function::ScriptType){
    
}

ScriptApi::~ScriptApi(){
    
}
