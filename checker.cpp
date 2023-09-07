#include <iostream>
#include <assert.h>
#include <unistd.h>
using namespace std;

void PrintCriticalMessage(string message) {
    cout << message << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "\r* " << flush;
        sleep(1);
        cout << "\r *" << flush;
        sleep(1);
    }
}

void PrintWarningMessage(){
  cout <<"Approaching hypothermia" <<endl;
}
bool istemperatureCritical(float temperature){
    return temperature > 102 || temperature < 95;
}
bool isTemperatureWarning(float temperature) {
    float warningTolerance = 102 * 0.015;
    return temperature >= 102 - warningTolerance || temperature <= 95 + warningTolerance;
}

bool checkTemperature(float temperature) {

    if (isTemperatureWarning(temperature)) {
        PrintWarningMessage();
    }
    else if (istemperatureCritical(temperature)) {
        PrintCriticalMessage("Temperature critical!");
        return false;
    }
    return true;
}


bool ispulseRateCritical(float pulseRate){
    return pulseRate < 60 || pulseRate > 100;
}
bool ispulseRateWarning(float pulseRate)
{   
    float warningTolerance = 100 * 0.015;
    return pulseRate >= 100 - warningTolerance || pulseRate <= 60 + warningTolerance;
}

bool checkPulseRate(float pulseRate) {
    
    if (ispulseRateWarning(pulseRate)) {
        PrintWarningMessage();
    }
    else if (ispulseRateCritical(pulseRate)) {
        PrintCriticalMessage("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

bool checkSpo2(float spo2) {
    float warningTolerance = 90 * 0.015;
    if (spo2 < 90) {
        PrintCriticalMessage("Oxygen Saturation out of range!");
        return false;
    }
    else if (spo2 <= 90 - warningTolerance) {
        PrintWarningMessage();
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
return checkTemperature(temperature) && checkPulseRate(pulseRate) && checkSpo2(spo2);
}

int main() {
  assert(!vitalsOk(99, 102, 70));
  assert(vitalsOk(98.1, 70, 98));
  assert(!vitalsOk(103,72,95));
  assert(!vitalsOk(94,72,95));
  assert(!vitalsOk(98.5,72,90));
    
  cout << "Done\n";
}
