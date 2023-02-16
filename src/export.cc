// Copyright 2021 BBfat

#include "shared/shared.h"
#include <napi.h>
#include <tuple>

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  InitPlatformExports(env, exports);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
