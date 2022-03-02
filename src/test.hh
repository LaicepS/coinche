#pragma once

#include <functional>

namespace coinche
{
  struct tester
  {
    using test_fn = void (*)();
    using fixture_fn = std::function<void()>;

    static tester& instance()
    {
      static tester instance;
      return instance;
    }

    auto add_test(test_fn f)
    {
      all_tests[test_idx++] = f;
      return 0;
    }

    auto add_test(fixture_fn f) 
    {
      all_fixtures[test_idx++] = f;
      return 0;
    }

    void run_tests()
    {
      for (auto t : all_tests)
        if (t)
          t();
    }

    int test_idx = 0;
    test_fn all_tests[100];
    fixture_fn all_fixtures[100];
  };

} // namespace coinche

#define CAT_(x, y) x##y
#define CAT(x, y) CAT_(x, y)
#define unittest(FUN)                                                          \
  void FUN();                                                                  \
  auto CAT(FUN, __LINE__) = tester::instance().add_test(FUN);                  \
  void FUN()

#define funittest(fixture, name)                                               \
  struct CAT("TestFixture", name)                                               \
      : fixture                                                                \
  {                                                                            \
    void body() const; \
  };\
  tester::instance().add_test([]() { CAT("TestFixture", name)::body(); }) \

