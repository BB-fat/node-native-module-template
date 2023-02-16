//
//  utils.h
//
//  Created by BBfat.
//

#ifndef NATIVE_BRIDGE_UTILS_H_
#define NATIVE_BRIDGE_UTILS_H_

#include <string>

#define THROW_JS_EXCEPTION(_env, _msg) Napi::TypeError::New(_env, _msg).ThrowAsJavaScriptException()

#define BOOL_FROM_OBJ(_obj, _key) _obj.Has(_key) && _obj.Get(_key).IsBoolean() && _obj.Get(_key)

#endif /* NATIVE_BRIDGE_UTILS_H_ */
