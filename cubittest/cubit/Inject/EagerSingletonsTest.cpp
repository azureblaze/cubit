#include "pch.h"

#include <cubit/Inject/EagerSingleton.h>

using namespace cubit;
namespace di = boost::di;
namespace {
struct Spy {
  int called = 0;
};
}  // namespace

TEST(EagerSingletonTest, eagerSingleton_created) {
  struct Foo : public EagerSingleton {
    Foo(Spy& spy) { spy.called++; }
  };

  auto injector = di::make_injector(di::bind<Foo>().to<Foo>());

  InitializeEagerSingletons(injector);

  EXPECT_EQ(1, injector.create<Spy&>().called);
}

TEST(EagerSingletonTest, noneagerSingleton_notCreated) {
  struct Foo {
    Foo(Spy& spy) { spy.called++; }
  };

  auto injector = di::make_injector(di::bind<Foo>().to<Foo>());

  InitializeEagerSingletons(injector);

  EXPECT_EQ(0, injector.create<Spy&>().called);
}

di::injector<Spy&> getParentInjector() {
  struct Foo : public EagerSingleton {
    Foo(Spy& spy) { spy.called++; }
  };
  auto injector = di::make_injector(di::bind<Foo>().to<Foo>());
  InitializeEagerSingletons(injector);
  return injector;
}

TEST(EagerSingletonTest, eagerSingleton_initializedInParent_created) {
  auto injector = di::make_injector(getParentInjector());

  EXPECT_EQ(1, injector.create<Spy&>().called);
}

TEST(EagerSingletonTest, eagerSingleton_initializedInChild_created) {
  struct BarSpy {
    int called = 0;
  };
  struct Bar : public EagerSingleton {
    Bar(BarSpy& spy) { spy.called++; }
  };

  auto injector =
      di::make_injector(getParentInjector(), di::bind<Bar>().to<Bar>());
  InitializeEagerSingletons(injector);

  EXPECT_EQ(1, injector.create<Spy&>().called);
  EXPECT_EQ(1, injector.create<BarSpy&>().called);
}
