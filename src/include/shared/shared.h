// Copyright 2023 BBfat
#ifndef NATIVE_BRIDGE_SHARED_H_
#define NATIVE_BRIDGE_SHARED_H_

#include <napi.h>

/**
 * 在平台的export.cc中实现
 * 用于将平台特有的native方法注册到对js export的对象上
 */
void InitPlatformExports(Napi::Env env, Napi::Object exports);

#endif  // NATIVE_BRIDGE_SHARED_H_
