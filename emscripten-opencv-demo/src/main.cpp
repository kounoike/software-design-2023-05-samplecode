#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <opencv2/opencv.hpp>

const int WIDTH = 640;
const int HEIGHT = 480;
unsigned char buffer[WIDTH * HEIGHT * 4];

intptr_t getBuffer() {
  return reinterpret_cast<intptr_t>(buffer);
}

void flip() {
  cv::Mat mat(HEIGHT, WIDTH, CV_8UC4, buffer);
  cv::flip(mat, mat, 0);
}

EMSCRIPTEN_BINDINGS(wasm_module) {
  emscripten::function("getBuffer", &getBuffer);
  emscripten::function("flip", &flip);
}
