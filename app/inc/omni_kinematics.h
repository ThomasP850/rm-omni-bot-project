#ifndef OMNI_KINEMATICS_H
#define OMNI_KINEMATICS_H

typedef struct ChassisVelocities {
  float x;
  float y;
  float omega;
} ChassisVelocities;

typedef struct OmniWheelVelocities {
  float frontLeft;
  float frontRight;
  float backLeft;
  float backRight;
} OmniWheelVelocities;

void calculateOmniWheelVelocities(ChassisVelocities targetVelocities, float outputVelocities[4], float maxWheelSpeed, float wheelRadius, float trackWidth, float wheelBase);

#endif
