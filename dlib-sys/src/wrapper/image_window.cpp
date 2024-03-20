#pragma once

#include <algorithm>
#include <dlib/gui_widgets.h>
#include <dlib/gui_widgets/widgets.h>
#include <iterator>
#include <memory>
#include <vector>

#include "cv_image.cpp"
#include "overlay_line.cpp"
#include "rectangle.cpp"

namespace wrapper {

struct ImageWindow {
  dlib::image_window inner;

  void set_image(CvImage &cv_image) { inner.set_image(cv_image.inner); }

  void add_rectangle_overlay(std::shared_ptr<Rectangle> rectangle) {
    this->inner.add_overlay(rectangle.get()->inner);
  }

  void add_line_overlay(std::vector<OverlayLine> overlay_lines) {
    std::vector<dlib::image_window::overlay_line> dlib_overlay_lines;

    std::transform(overlay_lines.begin(), overlay_lines.end(),
                   std::back_inserter(dlib_overlay_lines),
                   [](OverlayLine x) { return x.inner; });

    this->inner.add_overlay(dlib_overlay_lines);
  }

  void clear_overlay() { this->inner.clear_overlay(); }
};
} // namespace wrapper
