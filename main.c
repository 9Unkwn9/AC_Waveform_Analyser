#include <stdio.h>
#include "waveform.h"
#include "io.h"
#include <stdlib.h>

/*Filename: AC_Waveform_Analyser
Description: AC Waveform Analyser
Author: Adam Rychlinski - 23024670
Date: 02/05/2026
Version 2.0
Log:
*/

int main(int argc, char* argv[]) {//

    if (argc < 2) {//Checking the provided CSV filename
        printf("File: %s power_quality_log.csv\n", argv[0]);
        return 1;
    }

    Waveform *waveform = NULL;//Pointer directed to waveform data
    size_t count = 0;//Samples loaded from CSV file

    if (!loaded_csv(argv[1], &waveform, &count)) {//Load into memory
        return 1;//Return if there is a loading failure
    }

    PhaseR phaseA = analyse_phase_r(waveform, count, 'A');//Analysis of each phase
    PhaseR phaseB = analyse_phase_r(waveform, count, 'B');
    PhaseR phaseC = analyse_phase_r(waveform, count, 'C');

    if (!results("results.txt", &phaseA, &phaseB, &phaseC, count)) {//Write results to output file
        free(waveform);
        return 1;
    }
    printf("Data Collected, results written within results.txt\n");

    free(waveform);//Free memory if not needed

    return 0;
}
