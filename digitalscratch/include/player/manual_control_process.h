/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch Player                           */
/*                                                                            */
/*                                                                            */
/*-----------------------------------------------( manual_control_process.h )-*/
/*                                                                            */
/*  Copyright (C) 2003-2015                                                   */
/*                Julien Rosener <julien.rosener@digital-scratch.org>         */
/*                                                                            */
/*----------------------------------------------------------------( License )-*/
/*                                                                            */
/*  This program is free software: you can redistribute it and/or modify      */
/*  it under the terms of the GNU General Public License as published by      */
/*  the Free Software Foundation, either version 3 of the License, or         */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  This package is distributed in the hope that it will be useful,           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU General Public License for more details.                              */
/*                                                                            */
/*  You should have received a copy of the GNU General Public License         */
/*  along with this program. If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/*------------------------------------------------------------( Description )-*/
/*                                                                            */
/* Behavior class: determine playback parametrs based on keyboard and gui     */
/*                 buttons.                                                   */
/*                                                                            */
/*============================================================================*/

#pragma once

#include <iostream>
#include <QSharedPointer>
#include <QObject>

#include "playback_parameters.h"
#include "application_const.h"
#include "control_process.h"

using namespace std;

class Manual_control_process : public Control_process
{
    Q_OBJECT

 private:
    float speed;

 public:
    Manual_control_process(const QSharedPointer<Playback_parameters> &param);
    virtual ~Manual_control_process();

    bool run();
    void inc_speed(const float &speed_inc);
    void reset_speed_to_100p();
};
