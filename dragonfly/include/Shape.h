///
/// A single-space, 2d shape for drawing.
///

#ifndef __SHAPE_H__
#define __SHAPE_H__

// System includes.
#include <SFML/Graphics/CircleShape.hpp>

// Engine includes.
#include "Color.h"
#include "Vector.h"

namespace df {

enum ShapeType {
  UNDEFINED_SHAPE = -1,
  CIRCLE,
  SQUARE,
  TRIANGLE,
};

class Shape {

 private:
  Color color;		  ///< Shape color.
  unsigned char r,g,b;	  ///< RGB colors used if color is CUSTOM.
  ShapeType type;	  ///< Type of shape.
  float size;		  ///< Shape radius size (in pixels).
  unsigned char opacity;  ///< Range (transparent) 0 to 255 (opaque).

 public:

  /// Default is circle, white, size 1 cell.
  Shape();

  void setSize(float new_size);
  void setType(ShapeType new_type);
  void setColor(Color new_color);
  void setColor(unsigned char r, unsigned char g, unsigned char b);
  void setOpacity(unsigned char new_opacity);
  float getSize() const;
  ShapeType getType() const;
  Color getColor() const;
  unsigned char getOpacity() const;

  /// Shapes know how to draw themselves at given world position.
  void draw(Vector world_pos);
};

} // end of namespace df
#endif //__SHAPE_H__
