/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch System                           */
/*                                                                            */
/*                                                                            */
/*-------------------------------------------------------------( volume.cpp )-*/
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
/*               Volume class : define the music volume concept.              */
/*                                                                            */
/*============================================================================*/

#include <iostream>
#include <string>
using namespace std;

#include "log.h"
#include "volume.h"

Volume::Volume(string turntable_name) : Playing_parameter(turntable_name)
{
    this->value = 0.0;
}

Volume::~Volume()
{
}

float Volume::get_value()
{
    return this->value;
}

bool Volume::set_value(float volume_value)
{
    // Volume can not be negative.
    if (volume_value < 0.0)
    {
        return false;
    }

    this->value = volume_value;

    return true;
}
