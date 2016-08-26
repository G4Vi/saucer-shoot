///
/// A firework particle
///

#ifndef __FIREWORK_H__
#define __FIREWORK_H__

// Engine include.
#include "Particle.h"

namespace df {

class Firework : public Particle {
 private:
  unsigned char r, g, b;	 ///< RBG values for drawing.
  unsigned char initial_opacity; ///< Initial opacity when created.
  int initial_age;               ///< Initial age when created.
  float initial_size;		 ///< Initial size when created.

 public:
  /// Constructor, specifing size, age, opacity and rgb.
  Firework(float size, int age, unsigned char opacity,
	   unsigned char r, unsigned char g, unsigned char b);

  /// Handle step events.
  /// Return 0 if ignored, else 1.
  int eventHandler(const Event *p_e);
};

} // end of namespace df

#endif //__FIREWORK_H__
