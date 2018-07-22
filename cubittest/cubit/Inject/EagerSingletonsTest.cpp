#include "pch.h"

#include <cubit/Inject/EagerSingleton.h>

using namespace cubit;
namespace di = boost::di;
namespace {
struct Spy {
  bool called = false;
};
}  // namespace

TEST(EagerSingletonTest, eagerSingleton_created) {
  struct Foo : public EagerSingleton {
    Foo(Spy& spy) { spy.called = true; }
  };

  auto injector = di::make_injector(di::bind<Foo>().to<Foo>());

  InitializeEagerSingletons(injector);

  EXPECT_TRUE(injector.create<Spy&>().called);
}

TEST(EagerSingletonTest, noneagerSingleton_notCreated) {
  struct Foo {
    Foo(Spy& spy) { spy.called = true; }
  };

  auto injector = di::make_injector(di::bind<Foo>().to<Foo>());

  InitializeEagerSingletons(injector);

  EXPECT_FALSE(injector.create<Spy&>().called);
}
