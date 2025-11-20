#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <stdexcept>
#include <utility>
#include <vector>

template <class T> class BufferedChannel {
public:
  explicit BufferedChannel(size_t size)
      : cap_(size), buffer_(size), head_(0), tail_(0), size_(0),
        closed_(false) {
    if (size == 0) {
      throw std::invalid_argument("BufferedChannel size must be > 0");
    }
  }

  void Send(T value) {
    std::unique_lock<std::mutex> lock(mtx_);

    cv_prod_.wait(lock, [this]() { return size_ < cap_ || closed_; });

    if (closed_) {
      throw std::runtime_error("BufferedChannel is closed");
    }

    buffer_[tail_] = std::move(value);

    if (++tail_ == cap_)
      tail_ = 0;
    ++size_;

    cv_cons_.notify_one();
  }

  std::pair<T, bool> Recv() {
    std::unique_lock<std::mutex> lock(mtx_);

    cv_cons_.wait(lock, [this]() { return size_ > 0 || closed_; });

    if (size_ == 0 && closed_) {
      return {T(), false};
    }

    T val = std::move(buffer_[head_]);

    if (++head_ == cap_)
      head_ = 0;
    --size_;

    cv_prod_.notify_one();
    return {std::move(val), true};
  }

  void Close() {
    std::lock_guard<std::mutex> lock(mtx_);
    closed_ = true;
    cv_cons_.notify_all();
    cv_prod_.notify_all();
  }

private:
  const size_t cap_;
  std::vector<T> buffer_;
  size_t head_;
  size_t tail_;
  size_t size_;
  bool closed_;
  std::mutex mtx_;
  std::condition_variable cv_cons_;
  std::condition_variable cv_prod_;
};

#endif // BUFFERED_CHANNEL_H_
