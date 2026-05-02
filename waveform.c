#include "waveform.h"
#include <math.h>
#include <stdlib.h>
/*Filename: AC_Waveform_Analyser
Description: AC Waveform Analyser
Author: Adam Rychlinski - 23024670
Date: 02/05/2026
Version 2.0
Log: Creating Mathmatical solutions required for waveform
Analyses voltage data for requested phase
 *Computes RMS values, peak to peak voltages and DC offset
 *clipping count and tolerance
*/

double phase_vol (const Waveform *waveform, char phase) {
    //Allow the return of voltage to specific phase A,B or C in this case
    if (phase == 'A'){
        return waveform->phase_A_Voltage;//check which phase is required
    } else if (phase == 'B') {
        return waveform->phase_B_Voltage;
    } else {
        return waveform->phase_C_Voltage;
    }
}

PhaseR analyse_phase_r(const Waveform *waveform, size_t count, char phase) {
   PhaseR result;

    double sum = 0.0;//sum of voltages, sum of squared voltages, minimum voltage and maximum voltage
    double squared= 0.0;
    double min_volt;
    double max_volt;

    result.c_count = 0;
//Initiation Min and Max
    const Waveform *first = waveform;
    min_volt = phase_vol(first, phase);
    max_volt = min_volt;

    for (size_t i = 0; i < count; i++) {
        const Waveform *current = waveform + i;
        double volt = phase_vol(current, phase);//get voltage for user selected phase

        sum += volt;//values for calculations
        squared += volt * volt;

        if (volt < min_volt) {
            min_volt = volt;
        }

        if (volt > max_volt) {
            max_volt = volt;
        }

        if (fabs(volt) >= C_Limit) {//fabs used for detection of both peaks of the waveform
            result.c_count++;
        }

    }
    result.rms = sqrt(squared / count);//calculation for rms
    result.ptp = max_volt - min_volt;//calculation for peak to peak
    result.dc_offset = sum / count;//calculation for DC offset

    double lower_lim = Rms_Nom * (1.0 - Rms_Tol);//limits for RMS
    double upper_lim = Rms_Nom * (1.0 + Rms_Tol);

    if (result.rms >= lower_lim && result.rms <= upper_lim) {//check whether the rms is within range
        result.w_tolerance = 1;//within range
    }else {
        result.w_tolerance = 0;//outside of range
    }

    return result;





}