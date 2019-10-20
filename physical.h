/*
 * physical.h
 *
 *  Created on: Oct 17, 2019
 *      Author: shohei
 */

#ifndef PHYSICAL_H_
#define PHYSICAL_H_

/*
 * Definitions of physical parameters and unit converters
 *
 * units:
 *  [m], [s],
 */


/* unit converters */

// meter
#define PYSICAL_METER(l)	(l)
#define PYSICAL_CMETER(l)	(l * 100)
#define PYSICAL_MMETER(l)	(l * 1000)


/* constants */

#define G_ACC 9.80665 // [m/s^2]


/* machine body */

// wheel
#define DISTANCE_CENTER_TO_WHEEL (0.42306198718) // [m]

// encoder
#define PPR_GROUNDING_ENC (2400) // [dimensionless]

// encoder wheel
#define RADIUS_ENC_WHEEL (0.030) // [m]
#define DISTANCE_CENTER_TO_ENC_WHEEL (0.28837) // [m]


#endif /* PHYSICAL_H_ */
