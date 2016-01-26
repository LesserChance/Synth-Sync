// CONSTANTS
const int MS_PER_PULSE = 17;          // How long to send a pulse for voltage output
const int MIN_BPM_TEMPO_REPEAT = 1;   // How many times we see a tempo before we consider it changed
const int SMOOTHNESS = 2;             // How many pulse lengths we keep to find an average
const int MIN_PULSE = 10;             // The minimum duration of a pulse to read for voltage input
const int BPM_PULSE_MS = 30000;       // Convert BPM to pulses (2 pulses per beat - 30000 / bpm) i.e. 60 BPM = 1 BPS -> 1 pulse every 500 ms

const int MODE_MASTER = 0;            // Controlling the bpm
const int MODE_SLAVE = 1;             // Getting bpm from input

const int BPM_INPUT = 2;              // Pin for BPM voltage input
const int BPM_OUTPUT = 4;             // D4 - Pin for BPM voltage output - channel 1

const int ENCODER_PIN_A = 3;          // Pin for the rotary encoder
const int ENCODER_PIN_B = 7;          // Pin for the rotary encoder

const int DIGIT_LATCH_PIN = 8;        // B0 - Pin for the digit SR latch
const int DIGIT_CLOCK_PIN = 13;       // Pin for the digit SR clock
const int DIGIT_DATA_PIN = 11;        // Pin for the digit SR data

const int SLAVE_TIMEOUT = 1000;       // How long to wait while not receiving input to switch to slave mode

// GLOBALS
unsigned long time;                   // the current time in milliseconds
float bpm = 120;                      // the current beats per minutes
int mode = -1;                        // the current mode the synth sync is in

volatile unsigned long last_bpm_up_time = 0;   // the last time the bpm input went HIGH

// TEMPORARY
float output_bpm;
float output_pulse_start;
float output_speed = .25;

void setup() {
  pinMode(BPM_INPUT, INPUT);
  pinMode(BPM_OUTPUT, OUTPUT);

  Serial.begin(9600);

  setBpm(bpm);
  initSync();
  initMasterMode();
  initDigits();
}

void loop() {
  time = millis();
  
  readEncoder();

  //todo: only do this in slave mode once we're properly reading for connection
  updateBpmFromPulse();
  
  outputString("1234");
  
  //todo: only do this if we have output
  outputBpmPulse();

  mode_loop();
}

/**
 * Update the master bpm
 */
void setBpm(float new_bpm) {
  bpm = new_bpm;
  
  Serial.print("SET BPM: ");
  Serial.println(bpm);

  // output at half speed
  output_bpm = bpm * output_speed;
}

/**
 * Update the master pulse start timing
 */
void setPulseStart(int pulse_start) {
  output_pulse_start = pulse_start * output_speed;
}
