//
//  async_worker.cpp
//
//  Created by BBfat.
//

#include "common/async_worker.h"

std::vector<napi_value>
native_bridge_async_worker::GetResult(Napi::Env env, std::string result) {
  return {Napi::String::New(env, result)};
}

std::vector<napi_value> native_bridge_async_worker::GetResult(Napi::Env env,
                                                              int result) {
  return {Napi::Number::New(env, result)};
}

std::vector<napi_value>
native_bridge_async_worker::GetResult(Napi::Env env,
                                      std::vector<std::string> result) {
  auto array = Napi::Array::New(env);
  for (long i = 0; i < result.size(); i++) {
    Napi::HandleScope scope(env);
    array.Set(i, Napi::String::New(env, result[i]));
  }
  return {array};
}
