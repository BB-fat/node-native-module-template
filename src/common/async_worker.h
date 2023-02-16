//
//  async_worker.h
//
//  Created by BBfat.
//

#ifndef NATIVE_BRIDGE_ASYNC_WORKER_H_
#define NATIVE_BRIDGE_ASYNC_WORKER_H_

#include <napi.h>
#include <tuple>

template <typename Func, typename... Args>
class VoidAsyncWorker : public Napi::AsyncWorker {
  using ArgsTuple = std::tuple<Args...>;

public:
  VoidAsyncWorker(const Napi::Function &callback, const Func &func,
                  const ArgsTuple &data)
      : AsyncWorker(callback), _func(func), _data(data) {}

  ~VoidAsyncWorker() override = default;

  void Execute() override { std::apply(_func, _data); }

private:
  std::function<Func> _func;
  ArgsTuple _data;
};

namespace native_bridge_async_worker {
std::vector<napi_value> GetResult(Napi::Env env, std::string result);

std::vector<napi_value> GetResult(Napi::Env env, int result);

std::vector<napi_value> GetResult(Napi::Env env,
                                  std::vector<std::string> result);
} // namespace native_bridge_async_worker

template <typename Func, typename... Args>
class GeneralAsyncWorker : public Napi::AsyncWorker {
  using ArgsTuple = std::tuple<Args...>;

public:
  GeneralAsyncWorker(const Napi::Function &callback, const Func &func,
                     const ArgsTuple &data)
      : AsyncWorker(callback), _func(func), _data(data) {}

  ~GeneralAsyncWorker() override = default;

  void Execute() override { _resultValue = std::apply(_func, _data); }

  std::vector<napi_value> GetResult(Napi::Env env) override {
    auto results = native_bridge_async_worker::GetResult(env, _resultValue);
    if (results.size() == 0) {
      return {env.Undefined()};
    }
    std::vector<napi_value> returnValue = {env.Undefined()};
    std::copy(results.begin(), results.end(), std::back_inserter(returnValue));
    return returnValue;
  }

private:
  std::function<Func> _func;
  ArgsTuple _data;
  std::invoke_result_t<Func, Args...> _resultValue;
};

#endif // NATIVE_BRIDGE_ASYNC_WORKER_H_
