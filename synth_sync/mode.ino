void mode_loop() {
  switch (mode) {
    case MODE_MASTER:
      detectSlaveMode();
      break;

    case MODE_SLAVE:
      detectMasterMode();
      break;
  }
}

void mode_handleEncoderChange(int encoder_direction, int encoder_state) {
  switch (mode) {
    case MODE_MASTER:
      // todo: if pushing down on the encoder, increment by tens
      setBpm(bpm + encoder_direction);
      break;

    case MODE_SLAVE:
      // todo
      break;
  }
}

/**
 * Determine if slave mode has started
 */
void detectSlaveMode() {
  // if we received a pulse recently, we've switched to slave
  // todo: in the future Ill use a pin to determine if theres a parent connection
  if (mode != MODE_SLAVE && (time - last_bpm_up_time) < SLAVE_TIMEOUT) {
    initSlaveMode();
  }
}

/**
 * Determine if master mode has started
 */
void detectMasterMode() {
  // if we havent received pulses in a while, we've switched to master
  // todo: in the future Ill use a pin to determine if theres a parent connection
  if (mode != MODE_MASTER && (time - last_bpm_up_time) > SLAVE_TIMEOUT) {
    initMasterMode();
  }
}

/**
 * Start master mode
 */
void initMasterMode() {
  Serial.println("SWITCH TO MASTER");
  mode = MODE_MASTER;
  setBpm(120);
}

/**
 * Start slave mode
 */
void initSlaveMode() {
  Serial.println("SWITCH TO SLAVE");
  mode = MODE_SLAVE;
}
