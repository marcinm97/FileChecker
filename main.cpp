#include <iostream>
#include "FileChecker.h"
#include <algorithm>

// EXAMPLE

//        File created: C:\Users\Marcin\CLionProjects\FileChecker\cmake-build-debug\Nowy dokument tekstowy.txt
//        File removed: C:\Users\Marcin\CLionProjects\FileChecker\cmake-build-debug\Nowy dokument tekstowy.txt
//        File created: C:\Users\Marcin\CLionProjects\FileChecker\cmake-build-debug\poq.txt
//        File modified: C:\Users\Marcin\CLionProjects\FileChecker\cmake-build-debug\poq.txt
//        File removed: C:\Users\Marcin\CLionProjects\FileChecker\cmake-build-debug\poq.txt

int main() {

using namespace std::experimental;


    auto delay(std::chrono::milliseconds(5000));

    FileChecker monit{filesystem::current_path().string(), delay, true};

    auto disp_Alert([](const std::string& path_, State type_of_change)-> void{

//        if(!filesystem::is_regular_file(filesystem::path(path_)) && type_of_change != State::Removed){
//            return;
//        }

        switch(type_of_change){
            case State::Created:
                std::cout<<"File created: "<< path_ <<"\n";
                break;
            case State::Modified:
                std::cout<<"File modified: "<< path_ <<"\n";
                break;
            case State::Removed:
                std::cout<<"File removed: "<< path_<< "\n";
                break;
            default:
                std::cout<<"Unknown file status.\n";
        }
    });

    monit.startChecking(disp_Alert);

    return 0;
}