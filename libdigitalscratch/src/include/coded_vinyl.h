/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*                           Digital Scratch System                           */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------( coded_vinyl.h )-*/
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
/*            Coded_vynil class : define a coded vinyl disk                   */
/*                                                                            */
/*============================================================================*/

#pragma once

#include <string>
#include <vector>
#include "dscratch_parameters.h"
#include "digital_scratch_api.h"

#ifdef DISPLAY_CODE_LINE
    #define TRACE_PREFIX_CODED_VINYL "[Coded_vinyl:" + Utils::to_string(__LINE__) + "]\t\t"
#else
    #define TRACE_PREFIX_CODED_VINYL "[Coded_vinyl]\t\t\t"
#endif

#define MAX_SIN_WAV_AREA_FACTOR      100
#define SPEED_FOR_VOLUME_CUT         0.90
#define MAX_NO_NEW_SPEED_FOUND       3
#define UNKNOWN_SAMPLE_VALUE         -99.0f

#define DEFAULT_INPUT_AMPLIFY_COEFF  1
#define DEFAULT_RPM                  RPM_33

/**
 * Define a Coded_vinyl class.\n
 * A coded vinyl is the definition of a vinyl disc with a timecoded signal.
 * @author Julien Rosener
 */
class Coded_vinyl
{
    /* Attributes */
    protected:
        float min_amplitude_for_normal_speed;
        float min_amplitude;

    private:
        // Signal.
        int sample_rate;
        unsigned short int rpm;
        int input_amplify_coeff;
        vector<float> samples_channel_1;
        vector<float> samples_channel_2;

        // Speed analysis.
        vector< pair<bool, unsigned int> > zero_cross_list_1;
        vector< pair<bool, unsigned int> > zero_cross_list_2;
        float old_speed;
        float current_speed;
        float sin_wave_area_size;
        unsigned int no_new_speed_found_counter;
        unsigned int too_diff_new_speed_counter;
        bool last_signal_was_centered;
        unsigned int last_zero_cross_list_size;
        bool validating_turntable_started;
        bool validating_changing_direction;
        void smoothly_change_speed(float &speed);
        bool is_reverse_direction;

    /* Constructor / Destructor */
    public:
        /**
         * Constructor
         */
        Coded_vinyl(unsigned int sample_rate);

        /**
         * Destructor
         */
        virtual ~Coded_vinyl();


    /* Methods */

    private:
        void      calculate_sin_wave_area_size();
        void      fill_zero_cross_list(vector< pair<bool, unsigned int> > &zero_cross_list, vector<float> &samples);
        float     calculate_speed();
        float     calculate_average_speed_one_channel(vector< pair<bool, unsigned int> > &zero_cross_list);
        short int calculate_direction();
        bool      validate_and_adjust_speed_against_amplitude(float &speed);
        void      validate_and_ajust_speed_when_starting(float &speed);
        void      validate_and_ajust_speed_when_changing_direction(float &speed);
        void      keep_unused_samples();
        void      remove_used_samples(vector< pair<bool, unsigned int> > &zero_cross_list, vector<float> &samples);
        void      align_samples();
        float     get_signal_average_amplitude(vector<float> &samples);
        float     get_signal_amplitude(vector<float> &samples);
        void      amplify_and_clip_signal(float symetric_amp, vector<float> &samples);
        void      center_signal(vector<float> &samples);
        void      store_and_return_speed(float &speed);

    public:
        /**
         * Get the current speed value.
         * Define the pure virtual method in base class (Coded_vinyl)
         * @return the speed value or NO_NEW_SPEED_FOUND if nothing is found
         */
        float get_speed();

        /**
         * Get the current volume value.
         * Define the pure virtual method in base class (Coded_vinyl)
         * @return the volume value or NO_NEW_VOLUME_FOUND if nothing is found
         */
        float get_volume();

        /**
         * Add and analyze channels recording datas.
         * @param input_samples_1 are the samples of channel 1.
         * @param input_samples_2 are the samples of channel 2.
         *
         * @note input_samples_1 and input_samples_2 must have the same number
         *       of element.
         */
        void add_sound_data(vector<float> &input_samples_1,
                            vector<float> &input_samples_2);

        /**
         * Set the sample rate used to record timecoded vinyl.
         * @param sample_rate is the value to set.
         * @return TRUE if all is OK, otherwise FALSE.
         */
        bool set_sample_rate(int sample_rate);

        /**
         * Get the sample rate used to record timecoded vinyl.
         * @return the value to get.
         */
        int get_sample_rate();

        /**
         * Set coeff to be multiplied to input samples (amplification).
         * @param coeff is the value to set.
         * @return TRUE if all is OK, otherwise FALSE.
         */
        bool set_input_amplify_coeff(int coeff);

        /**
         * Get coeff to be multiplied to input samples.
         * @return the value to get.
         */
        int get_input_amplify_coeff();

        /**
         * Set number of RPM of the turntable.
         * @param rpm is the value to set.
         * @return TRUE if all is OK, otherwise FALSE.
         */
        bool set_rpm(unsigned short int rpm);

        /**
         * Get number of RPM of the turntable.
         * @return the value to get.
         */
        unsigned short int get_rpm();

        /**
         * Get the sinusoidal frequency
         */
        virtual int get_sinusoidal_frequency() = 0;

        /**
         * @brief Getter/Setter for the minimal acceptable amplitude for a normal speed.
         */
        void  set_min_amplitude_for_normal_speed(float amplitude);
        float get_min_amplitude_for_normal_speed();
        virtual float get_default_min_amplitude_for_normal_speed() = 0;

        /**
         * @brief Getter/Setter for the minimal detectable amplitude.
         */
        void  set_min_amplitude(float amplitude);
        float get_min_amplitude();
        virtual float get_default_min_amplitude() = 0;

    protected:
        /**
         * Set boolean to reverse direction (useful for Mixvibes record).
         */
        bool set_reverse_direction(bool is_reverse_direction);

        /**
         * Is reverse direction used ?.
         */
        bool get_reverse_direction();
};
