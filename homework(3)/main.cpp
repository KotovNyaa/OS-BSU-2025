#include "buffered_channel.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
  const int kMsg = 5000000;
  const int kBuffer_size = 1000;

  BufferedChannel<int> chan(kBuffer_size);
  std::atomic<long long> sum{0};

  auto start = std::chrono::high_resolution_clock::now();

  std::vector<std::thread> consumers;
  for (int i = 0; i < 2; ++i) {
    consumers.emplace_back([&]() {
      long long local_sum = 0;
      while (true) {
        auto res = chan.Recv();
        if (!res.second) {
          break;
        }
        local_sum += res.first;
      }
      sum += local_sum;
    });
  }

  std::vector<std::thread> producers;
  for (int i = 0; i < 2; ++i) {
    producers.emplace_back([&]() {
      for (int k = 0; k < kMsg; ++k) {
        chan.Send(1);
      }
    });
  }

  for (auto &t : producers) {
    t.join();
  }

  chan.Close();

  for (auto &t : consumers) {
    t.join();
  }

  long long expected = (long long)kMsg * 2;
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff = end - start;

  std::cout << "Time: " << diff.count() << " sec\n";
  std::cout << "Operation per sec: " << expected / diff.count() << "\n";
  std::cout << (sum == expected ? "OK" : "FAIL");
}
