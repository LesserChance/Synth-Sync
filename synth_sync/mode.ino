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
