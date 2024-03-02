use autocxx::prelude::*;

use crate::{
    cv_image::{self, CvImage},
    matrix::Matrix,
    rectangle::Rectangles,
};

pub struct ImageWindow {
    pub(crate) inner: cxx::UniquePtr<crate::ffi::wrapper::ImageWindow>,
}

impl ImageWindow {
    pub fn new() -> Self {
        Self {
            inner: crate::ffi::wrapper::ImageWindow::new().within_unique_ptr(),
        }
    }

    pub fn set_image(&mut self, cv_image: &mut CvImage) {
        self.inner.pin_mut().setImage(cv_image.inner.pin_mut())
    }

    pub fn add_overlays(&mut self, rectangles: &mut Rectangles) {
        self.inner.pin_mut().addOverlay1(rectangles.inner.pin_mut());
    }

    pub fn clear_overlay(&mut self) {
        self.inner.pin_mut().clearOverlay();
    }
}
