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

Script::Script(Doc* doc) : ScriptApi(doc){
    switch(ScriptVersion){
        case 4:
            new (this) ScriptV4(doc);
            break;
        case 3:
            new (this) ScriptV3(doc);
            break;
        default:
            exit(1);
    }
}

Script::~Script(){
}

QIcon Script::getIcon() const{
    return getIcon();
}

quint32 Script::totalDuration(){
    return totalDuration();
}

Function* Script::createCopy(Doc* doc, bool addToDoc){
    return createCopy(doc,addToDoc);
}


bool Script::copyFrom(const Function* function){
    return copyFrom(function);
}


bool Script::setData(const QString& str){
    return setData(str);
}


bool Script::appendData(const QString& str){
    return appendData(str);
}


QString Script::data() const{
    return data();
}


QStringList Script::dataLines() const{
    return dataLines();
}


QList<quint32> Script::functionList() const{
    return functionList();
}


QList<quint32> Script::fixtureList() const{
    return fixtureList();
}

QList<int>  Script::syntaxErrorsLines(){
    return syntaxErrorsLines();
}

QStringList Script::syntaxErrorsLinesString(){
    return syntaxErrorsLinesString();
}

void Script::slotRunnerFinished(){
  if(ScriptVersion==4)
      slotRunnerFinished();
}

void Script::preRun(MasterTimer *timer){
    preRun(timer);
}

void Script::write(MasterTimer *timer, QList<Universe*> universes){
    write(timer,universes);
}

void Script::postRun(MasterTimer *timer, QList<Universe*> universes){
    postRun(timer,universes);
}

bool Script::loadXML(QXmlStreamReader &root){
    return loadXML(root);
}


bool Script::saveXML(QXmlStreamWriter *doc){
    return CallApi->saveXML(doc);
}

ScriptApi::ScriptApi(Doc* doc) : Function(doc,Function::ScriptType){
    
}

ScriptApi::~ScriptApi(){
    
}
