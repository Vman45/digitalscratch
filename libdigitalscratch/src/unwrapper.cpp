/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch System                           */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------( unwrapper.cpp )-*/
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
/*                Unwrapper class : unwrap phase from a signal                */
/*                                                                            */
/*============================================================================*/

#include <unwrapper.h>

using namespace std;

Unwrapper::Unwrapper()
{
    this->last_phase = 0.0;
    this->current_phase = 0.0;
}

Unwrapper::~Unwrapper()
{
    return;
}

double Unwrapper::compute(const double &phase)
{
    double deltaPhase = phase - this->last_phase;

    if (deltaPhase > 3.1416) // Overflow
        this->current_phase += deltaPhase - 3.1416*2;
    else if (deltaPhase < -3.1416) // Underflow
        this->current_phase += deltaPhase + 3.1416*2;
    else // There is no phase over/underflow
        this->current_phase += deltaPhase;
    this->last_phase = phase;

    return this->current_phase;
}