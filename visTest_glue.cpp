
#include <emscripten.h>

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.
void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    EM_ASM_INT({
      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
    }, array_idx, array_size);
  }
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// CImageUtilHtml5

CImageUtilHtml5* EMSCRIPTEN_KEEPALIVE emscripten_bind_CImageUtilHtml5_CImageUtilHtml5_0() {
  return new CImageUtilHtml5();
}

char* EMSCRIPTEN_KEEPALIVE emscripten_bind_CImageUtilHtml5_LoadImageBuffer_3(CImageUtilHtml5* self, char* arg0, int arg1, int arg2) {
  return self->LoadImageBuffer(arg0, arg1, arg2);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CImageUtilHtml5___destroy___0(CImageUtilHtml5* self) {
  delete self;
}

}

