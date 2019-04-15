#ifndef FILECHECKER_FILECHECKER_H
#define FILECHECKER_FILECHECKER_H

#include <experimental/filesystem>
#include <thread>
#include <unordered_map>
#include <chrono>
#include <string>
#include <functional>
//#include <experimental/algorithm>


enum class State {Created, Modified, Removed};
using namespace std::experimental;

class FileChecker{
private:
    std::unordered_map<std::string, filesystem::file_time_type> paths_;
    std::chrono::duration<int, std::milli> delay_;
    std::string main_path;

    bool contains(const std::string& file_name){
        // return std::find_if(paths_.begin(), paths_.end(), [file_name](const auto& pair){
        // return pair.first == file_name;}) != paths_.end();
        return paths_.find(file_name) != paths_.end();
    }
public:
    FileChecker(const std::string& file_path, std::chrono::duration<int, std::milli> delay): main_path(file_path),
        delay_(delay){
        for(auto& f: filesystem::recursive_directory_iterator(main_path))
            paths_[f.path().string()] = filesystem::last_write_time(f);     // add path as a key, and time data as a value
    }

    void startChecking(const std::function<void(const std::string&, State)>& validate){
        while(true){  // infinity loop
            std::this_thread::sleep_for(delay_);    // set refresh every "delay_" seconds

            // checking if one of the files was erased
            for(auto&[path, time]: paths_){
                if(!filesystem::exists(path)){
                    validate(path, State::Removed);
                    paths_.erase(path);             // delete erased path
                }
            }

            for(auto& file: filesystem::recursive_directory_iterator(main_path)){
                auto lastWriteTime(filesystem::last_write_time(file));

                    // check if file was created
                if(auto s(file.path().string()); !contains(s)){
                    paths_[s] = lastWriteTime;
                    validate(s,State::Created);
                }else{
                    // check if file was modificated
                    if(paths_[s] != lastWriteTime){
                        paths_[s] = lastWriteTime;
                        validate(s,State::Modified);
                    }
                }
            }

        }
    }
};

#endif //FILECHECKER_FILECHECKER_H
