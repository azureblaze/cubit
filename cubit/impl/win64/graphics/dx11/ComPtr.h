#pragma once
namespace cubit {
namespace impl {
template <class T>
class ComPtr {
  T* ptr;

 public:
  ComPtr(T* ptr) : ptr(ptr) {}
  ComPtr() : ptr(nullptr) {}

  ComPtr(ComPtr<T>&& other) : ptr(other.ptr) { other.ptr = nullptr; }

  ComPtr(ComPtr<T>&) = delete;

  ~ComPtr() {
    if (ptr != nullptr) {
      ptr->Release();
    }
  }

  ComPtr<T>& operator=(ComPtr&& other) {
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
  };

  ComPtr<T>& operator=(const ComPtr&) = delete;

  T* operator->() const { return ptr; }

  operator T*() const { return ptr; }

  T* Get() const { return ptr; }

  T** GetAddressOf() { return &ptr; }
  const T** GetAddressOf() const { return &ptr; }
};
}  // namespace impl
}  // namespace cubit
