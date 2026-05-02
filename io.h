#ifndef AC_WAVEFORM_ANALYSER_IO_H
#define AC_WAVEFORM_ANALYSER_IO_H
#include "waveform.h"
#include <stddef.h>
/*Filename: AC_Waveform_Analyser
Description: AC Waveform Analyser
Author: Adam Rychlinski - 23024670
Date: 02/05/2026
Version 2.0
Log: Creating Mathmatical solutions required for waveform
*/

int loaded_csv(const char *filename, Waveform **waveform, size_t *count);// Loads CSV into allocated Array

int results(
    const char *filename,//writes results to a text file, 1 if succesfull, 0 if any errors appear
    const PhaseR *phaseA,
    const PhaseR *phaseB,
    const PhaseR *phaseC,
    size_t sample_count

);

#endif //AC_WAVEFORM_ANALYSER_IO_H
