// GLOBALS
int smooth_pulse_length[SMOOTHNESS];  // used for smoothing tempo reads by getting average
int smooth_pulse_length_i = 0;        // the current index to write in smooth_pulse_length
int total_pulse_length = 0;           // used for smoothing tempo reads by getting average
float temp_bpm = 0;                   // the last read tempo value
int tempo_counter = 0;                // how many times we have seen new tempo value

/*
 * INITIALIZIATION
 */
void initSync() {
  // initialize the smoothing vars
  for (int i = 0; i < SMOOTHNESS; i++) {
    smooth_pulse_length[i] = 0;
  }
  
  attachInterrupt(digitalPinToInterrupt(BPM_INPUT), inputBpmPulse, RISING);
}

/**
 * We've received a voltage pulse
 */
void inputBpmPulse() {
  int pulse_length = time - last_bpm_up_time;
  last_bpm_up_time = time;
    
  if (pulse_length > MIN_PULSE) {
    float new_bpm = getBpmFromPulse(pulse_length);
    updateBpm(new_bpm);
  }
}

/**
 * We've got a new bpm value, update master bpm if we trust it
 */
void updateBpm(float new_bpm) {
  if (new_bpm != bpm) {
    if (new_bpm == temp_bpm) {
      // the value has repeated
      tempo_counter++;
      
      if (tempo_counter >= MIN_BPM_TEMPO_REPEAT) {
        //we've seen this a few times now, consider it changed
        setBpm(temp_bpm);

        // Assure output pulses happen in tandem with input pulses
        setPulseStart((time % int(BPM_PULSE_MS / bpm) - MIN_PULSE));
        
        tempo_counter = 0;
      }
    } else {
      if (tempo_counter > 0) {
        tempo_counter--;
      }
    }
    
    temp_bpm = new_bpm;
  }
}

/**
 * Output bpm pulse on supplied pin
 */
void outputBpmPulse(int pin) {
  //todo: maybe switch this to use a 555?
  int pulse = time % int(BPM_PULSE_MS / output_bpm);

  if (pulse >= output_pulse_start && pulse <= MS_PER_PULSE + output_pulse_start) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

/**
 * Given the length of the pulse, determine the bpm
 */
float getBpmFromPulse(int pulse_length) {
  float new_bpm = float(BPM_PULSE_MS)/getSmoothPulseLength(pulse_length);
  return floor(new_bpm + .5);
}

/**
 * Use average of recent pulses to determined a smoothed pulse value
 */
int getSmoothPulseLength(int new_pulse_length) {
  // update the total
  total_pulse_length -= smooth_pulse_length[smooth_pulse_length_i];
  total_pulse_length += new_pulse_length;

  // save the newest value
  smooth_pulse_length[smooth_pulse_length_i] = new_pulse_length;
  
  smooth_pulse_length_i++;
  if (smooth_pulse_length_i >= SMOOTHNESS) {
    smooth_pulse_length_i = 0;
  }
    
  return (total_pulse_length / SMOOTHNESS);
}
