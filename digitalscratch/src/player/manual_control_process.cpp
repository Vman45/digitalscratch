/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch Player                           */
/*                                                                            */
/*                                                                            */
/*-------------------------------------------( manual_control_process.cpp )-*/
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
/*                 buttons                                                    */
/*                                                                            */
/*============================================================================*/

#include <QtDebug>
#include <QString>

#include "manual_control_process.h"
#include "application_logging.h"

Manual_control_process::Manual_control_process(const QSharedPointer<Playback_parameters> &param) : Control_process(param)
{
    this->params = param;
    this->speed  = 1.0;

    return;
}

Manual_control_process::~Manual_control_process()
{
    return;
}

bool
Manual_control_process::run()
{
    this->params->set_data_state(true);

    this->params->set_volume(1.0); // TODO calculate volume based on speed.
    this->params->set_volume_state(true);
    emit volume_changed((double)(floorf((this->params->get_volume() * 100.0) * 10.0) / 10.0));

    return true;
}

void
Manual_control_process::inc_speed(const float &speed_inc)
{
    this->params->set_speed(this->params->get_speed() + speed_inc);
    emit speed_changed(this->params->get_speed());
}

void
Manual_control_process::reset_speed_to_100p()
{
    this->params->set_speed(1.0);
}
