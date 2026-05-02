
#ifndef AC_WAVEFORM_ANALYSER_WAVEFORM_H
#define AC_WAVEFORM_ANALYSER_WAVEFORM_H
#include <stddef.h>
#define C_Limit 324.9
#define Rms_Nom 230.0
#define Rms_Tol 0.10
/*Filename: AC_Waveform_Analyser
Description: AC Waveform Analyser
Author: Adam Rychlinski- 23024670
Date: 02/05/2026
Version 2.0
Log: Creating Mathmatical solutions required for waveform
*/

typedef struct {
    double timestamp;
    double phase_A_Voltage;
    double phase_B_Voltage;
    double phase_C_Voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percentage;
} Waveform;

typedef struct {
    double rms;
    double ptp;//peak to peak
    double dc_offset;
    int c_count;
    int w_tolerance; //within tolerance
}PhaseR;

double phase_vol(const Waveform *waveform, char phase);

PhaseR analyse_phase_r(const Waveform *waveform, size_t count, char phase);

#endif //AC_WAVEFORM_ANALYSER_WAVEFORM_H