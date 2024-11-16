#include <Arduino.h>
#include "OrbReader.h"

OrbReader::OrbReader() {}

void OrbReader::setup() {
  pinMode(ORB_READER_ORB_INSERTED_PIN, INPUT);
  pinMode(ORB_READER_ENERGY_LEVEL_PIN, INPUT);
  pinMode(ORB_READER_TOXIC_TRAIT_PIN, INPUT);
  Serial.println("Set up Orb Reader pins");
}

void OrbReader::CheckDataSendHID() {
  if (not _orb_inserted) {
    if (digitalRead(ORB_READER_ORB_INSERTED_PIN)) {
      Serial.println("Orb Inserted");
      _orb_inserted = true;
    }
  } else {
    if (digitalRead(ORB_READER_ORB_INSERTED_PIN) == false) {
      Serial.println("Orb Removed");
      _orb_inserted = false;
    }
  }
}

void OrbReader::UpdateAnimationFrame() {
  // No animation for orb reader for now
}
