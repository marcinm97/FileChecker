#ifndef FILECHECKER_FILECHECKER_H
#define FILECHECKER_FILECHECKER_H

#include <experimental/filesystem>
#include <thread>
#include <unordered_map>
#include <chrono>
#include <string>
#include <functional>

enum class State {Created, Modified, Removed};
using namespace std::experimental;

class FileChecker{
    FileChecker(const std::string& file_path, std::chrono::duration<int, std::milli> delay)
private:
    std::unordered_map<std::string, filesystem::file_time_type> paths_;
    std::chrono::duration<int, std::milli> delay_;
};

#endif //FILECHECKER_FILECHECKER_H
