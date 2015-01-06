#pragma once

///
/// Base class of singleton classes.
///
/// Usage:
///
/// class Foo : public SingletonBase<Foo> {
///     friend class SingletonBase<Foo>;
/// private:
///     Foo() {}
///     ~Foo() {}
/// public:
///     someFunc();
/// }
///
/// Foo::Instance().someFunc()
///
template<typename T>
class SingletonBase {
protected:
  // ctor & dtor
  SingletonBase() {}
  ~SingletonBase() {}

private:
  // A singleton class is uncopyable.
  SingletonBase(const SingletonBase &) = delete;
  SingletonBase &operator=(const SingletonBase &) = delete;

public:
  ///
  /// Returns the instance of the singleton.
  ///
  static T &Instance() {
    static T instance;
    return instance;
  }
};