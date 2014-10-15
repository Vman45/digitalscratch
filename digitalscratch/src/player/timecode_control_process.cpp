/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch Player                           */
/*                                                                            */
/*                                                                            */
/*-------------------------------------------( timecode_control_process.cpp )-*/
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
/* Behavior class: analyze captured timecode and determine playback           */
/* parameters.                                                                */
/*                                                                            */
/*============================================================================*/

#include <QtDebug>
#include <QString>
#include <cmath>

#include "timecode_control_process.h"
#include "digital_scratch_api.h"
#include "application_logging.h"

Timecode_control_process::Timecode_control_process(Playback_parameters *in_params[],
                                                   unsigned short int   in_nb_decks,
                                                   QString              in_vinyl_type,
                                                   unsigned int         in_sample_rate)
{
    if (in_params == NULL)
    {
        qCCritical(DS_PLAYBACK) << "playback_parameters is NULL";

    }
    else
    {
        this->params = in_params;
    }

    this->nb_decks = in_nb_decks;
    this->dscratch_ids = new int[in_nb_decks];

    //
    // Initialize DigitalScratch library.
    //
    for (unsigned short int i = 0; i < in_nb_decks; i++)
    {
        // Create turntable.
        QString turntable_name;
        turntable_name = "turntable_" + i;
        if (dscratch_create_turntable((char*)turntable_name.toStdString().c_str(),
                                      (char*)in_vinyl_type.toStdString().c_str(),
                                      in_sample_rate,
                                      &this->dscratch_ids[i]) != 0)
        {
            qCCritical(DS_PLAYBACK) << "can not create turntable";
        }
    }

    return;
}

Timecode_control_process::~Timecode_control_process()
{
    // Delete dscratch turntable.
    for (unsigned short int i = 0; i < this->nb_decks; i++)
    {
        dscratch_delete_turntable(this->dscratch_ids[i]);
    }

    // Delete dscratch ids.
    delete [] this->dscratch_ids;

    return;
}

bool
Timecode_control_process::run(unsigned short int  in_nb_samples,
                               float              *in_samples_1,
                               float              *in_samples_2,
                               float              *in_samples_3,
                               float              *in_samples_4)
{
    int   j              = 0;
    int   are_new_params = 0;
    float speed    = 0.0;
    float volume   = 0.0;
    float *samples[] = { in_samples_1, in_samples_2, in_samples_3, in_samples_4 };

    // Iterate over decks and analyze captured timecode.
    for (int i = 0; i < this->nb_decks; i++)
    {
        if (dscratch_analyze_recorded_datas(this->dscratch_ids[i],
                                            samples[j],
                                            samples[j+1],
                                            in_nb_samples) != 0)
        {
            qCWarning(DS_PLAYBACK) << "cannot analyze captured data";
        }

        // Update playing parameters.
        if ((are_new_params = dscratch_get_playing_parameters(this->dscratch_ids[i],
                                                              &speed,
                                                              &volume)) == 0)
        {
            if (are_new_params == 0)
            {
                this->params[i]->set_new_data(true);
                if (speed != NO_NEW_SPEED_FOUND)
                {
                    this->params[i]->set_speed(speed);
                    this->params[i]->set_new_speed(true);
                }
                else
                {
                    this->params[i]->set_new_speed(false);
                }
                if (volume != NO_NEW_VOLUME_FOUND)
                {
                    this->params[i]->set_volume(volume);
                    this->params[i]->set_new_volume(true);
                }
                else
                {
                    this->params[i]->set_new_volume(false);
                }
            }
            else
            {
                this->params[i]->set_new_data(false);
            }
        }
        j = j + 2;
    }

    return true;
}

int
Timecode_control_process::get_dscratch_id(unsigned short int in_index)
{
    int out_dscratch_id = -1;

    if (in_index < this->nb_decks)
    {
        out_dscratch_id = this->dscratch_ids[in_index];
    }

    return out_dscratch_id;
}