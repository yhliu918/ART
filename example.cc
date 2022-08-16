#include "art32.h"

#include <chrono>
int random(int m) { return rand() % m; }

std::string source_file = "books_log";
std::vector<uint32_t> data;
std::ifstream srcFile(source_file, std::ios::in);
const int N = 200000000;

int main() {
  std::vector<uint32_t> ra_pos(N);
  while (srcFile.good()) {
    uint32_t next;
    srcFile >> next;
    if (!srcFile.good()) {
      break;
    }
    data.push_back(next);
  }
  srcFile.close();

  ART32 art;
  for (int i = 0; i < N; i++) {
    // ra_pos.emplace_back(i);
    ra_pos[i]=(random(N));
  }
  std::vector<KeyValue<uint32_t>> data_vec;
  for (size_t i = 0; i < data.size(); ++i) {
    data_vec.push_back((KeyValue<uint32_t>){data[i], i});
  }
  art.Build(data_vec);

  auto t1 = std::chrono::high_resolution_clock::now();
  std::vector<ART32::Node *> search_node;
  search_node.reserve(16);
  for (auto index : ra_pos) {
    // for(int index=1834752;index<N;index++){
    auto tmp = art.upper_bound_new(index, search_node);
    // std::cout <<index<<" "<< tmp << std::endl;
    // #ifdef NDEBUG
    // if (data[tmp] <= index || data[tmp - 1] > index) {
    //   std::cout << index << " " << tmp << std::endl;
    // }
    assert(data[tmp] > index && data[tmp - 1] <= index);
    // #endif
  }

  // for (int i = 0;i < data.size();i++) {
  //     // auto tmp = art.upper_bound_new(i);
  //     auto tmp = art.EqualityLookup(data[i]);
  //     std::cout <<i<<" "<< tmp << std::endl;
  //     assert(tmp==i);
  // }
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout
      << "time: "
      << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() /
             N
      << std::endl;
}
