/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch System                           */
/*                                                                            */
/*                                                                            */
/*---------------------------------------------------------( controller.cpp )-*/
/*                                                                            */
/*  Copyright (C) 2003-2014                                                   */
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
/*                Controller class : define a player controller               */
/*                                                                            */
/*============================================================================*/

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

#include "log.h"
#include "controller.h"

Controller::Controller(string name)
{
    this->set_name(name);
    this->speed    = new Speed(this->name);
    this->volume   = new Volume(this->name);
    this->set_playing_parameters_ready(false);
}

Controller::~Controller()
{
    delete this->speed;
    delete this->volume;
}

string Controller::get_name()
{
    return this->name;
}

bool Controller::set_name(string name)
{
    if (name == "")
    {
        qCCritical(DSLIB_CONTROLLER) << "Controller name empty.";
        return false;
    }

    this->name = name;
    qCDebug(DSLIB_CONTROLLER) << "New name=" << QString(this->name.c_str());

    return true;
}

int Controller::get_max_nb_no_new_speed_found()
{
    return this->speed->get_max_nb_no_new_speed_found();
}

bool Controller::set_max_nb_no_new_speed_found(int nb)
{
    if (this->speed->set_max_nb_no_new_speed_found(nb) == false)
    {
        return false;
    }

    return true;
}

int Controller::get_max_nb_cycle_before_starting()
{
    return this->speed->get_max_nb_cycle_before_starting();
}

bool Controller::set_max_nb_cycle_before_starting(int nb)
{
    if (this->speed->set_max_nb_cycle_before_starting(nb) == false)
    {
        return false;
    }

    return true;
}

bool Controller::get_playing_parameters(float *speed,
                                        float *volume)
{
    if (this->playing_parameters_ready == true)
    {
        *speed    = this->speed->get_value();
        *volume   = this->volume->get_value();

        return true;
    }
    else
    {
        return false;
    }
}

bool Controller::set_playing_parameters_ready(bool flag)
{
    this->playing_parameters_ready = flag;

    return true;
}
