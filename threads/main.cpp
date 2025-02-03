#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex Mutex;

void parseFiles(const std::string& File, std::unordered_map<std::string, int>& Map) {
    std::ifstream Con(File);
    bool IsMulti = false;
    std::string Line;

    while (std::getline(Con, Line)) {
        if (Line.empty()) {
            Map["Blank"]++;
            continue;
        }

        for (size_t I = 0; I < Line.length(); ++I) {
            if (IsMulti) {
                if (I == 0) Map["Multi comment"]++;
                if (Line[I] == '*' && I + 1 < Line.length() && Line[I + 1] == '/') {
                    IsMulti = false;
                    break;
                }
                continue;
            }

            if (Line[I] == ' ') continue;

            if (Line[I] == '/' && I + 1 < Line.length()) {
                if (Line[I + 1] == '/') {
                    Map["Single comment"]++;
                } else if (Line[I + 1] == '*') {
                    IsMulti = true;
                    Map["Multi comment"]++;
                }
            } else {
                Map["Physical line"]++;
            }
            break;
        }
    }
    Con.close();
}

void processFile(const std::string& File, std::unordered_map<std::string, int>& Map) {
    std::unordered_map<std::string, int> LocalMap;

    parseFiles(File, LocalMap);

    std::lock_guard<std::mutex> Lock(Mutex);
    for (const auto& [Key, Val] : LocalMap) {
        Map[Key] += Val;
    }
}

void threads(std::vector<std::string> Files, std::unordered_map<std::string, int>& Map) {
    std::vector<std::thread> Threads;
    for (const auto& File : Files) {
        Threads.push_back(std::thread(processFile, File, std::ref(Map)));
    }
    for (auto& T : Threads) {
        T.join();
    }
}

void single(std::vector<std::string> Files, std::unordered_map<std::string, int>& Map) {
    std::unordered_map<std::string, int> LocalMap;

    for(const auto& File : Files) {
        parseFiles(File, LocalMap);

        for (const auto& [Key, Val] : LocalMap) {
            Map[Key] += Val;
        }
        LocalMap.clear();
    }
}

void writeResultsToFile(const std::unordered_map<std::string, int>& Map, const std::string& OutputFile) {
    std::ofstream OutFile(OutputFile);
    if (!OutFile.is_open()) {
        std::cerr << "Error: Could not open file " << OutputFile << " for writing." << std::endl;
        return;
    }

    for (const auto& [Key, Val] : Map) {
        OutFile << Key << ": " << Val << std::endl;
    }

    OutFile.close();
    std::cout << "Results written to " << OutputFile << std::endl;
}

int main() {
    std::string Path = "../cgal-master/";
    std::vector<std::string> Files;
    std::unordered_map<std::string, int> MM;
    std::unordered_map<std::string, int> MS;

    for (const auto& File : std::filesystem::recursive_directory_iterator(Path)) {
        if (std::filesystem::is_regular_file(File.path())) {
            std::string Extension = File.path().extension().string();
            if (Extension == ".c" || Extension == ".cpp" || Extension == ".h" || Extension == ".hpp") {
                Files.emplace_back(File.path().string());
            }
        }
    }

    {
        auto Start = std::chrono::high_resolution_clock::now();
        threads(Files, MM);
        auto End = std::chrono::high_resolution_clock::now();
        auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(End - Start);
        std::cout << "Multiple Threads: " << Duration.count() << std::endl;
    }

    {
        auto Start = std::chrono::high_resolution_clock::now();
        single(Files, MS);
        auto End = std::chrono::high_resolution_clock::now();
        auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(End - Start);
        std::cout << "Single Thread: " << Duration.count() << std::endl;
    }

    writeResultsToFile(MS, "../output.txt");

    return 0;
}