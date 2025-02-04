#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>

class FileProcessor {
private:
    std::mutex Mutex;
    std::string Path;
    std::vector<std::string> Files;
    std::unordered_map<std::string, int> MultiThreadResults;
    std::unordered_map<std::string, int> SingleThreadResults;

public:
    explicit FileProcessor(const std::string& DirectoryPath) : Path(DirectoryPath) {}

    void collectFiles() {
        for (const auto& File : std::filesystem::recursive_directory_iterator(Path)) {
            if (std::filesystem::is_regular_file(File.path())) {
                std::string Extension = File.path().extension().string();
                if (Extension == ".c" || Extension == ".cpp" || Extension == ".h" || Extension == ".hpp") {
                    Files.emplace_back(File.path().string());
                }
            }
        }
    }

    void parseFile(const std::string& File, std::unordered_map<std::string, int>& Map) {
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
    }

    void processFile(const std::string& File, std::unordered_map<std::string, int>& Map) {
        std::unordered_map<std::string, int> LocalMap;
        parseFile(File, LocalMap);

        std::lock_guard<std::mutex> Lock(Mutex);
        for (const auto &[Key, Val]: LocalMap) {
            Map[Key] += Val;
        }
    }

    void processWithThreads() {
        std::vector<std::thread> Threads;
        for (const auto& File : Files) {
            Threads.emplace_back(&FileProcessor::processFile, this, File, std::ref(MultiThreadResults));
        }
        for (auto& T : Threads) {
            T.join();
        }
    }

    void processSingleThread() {
        for (const auto& File : Files) {
            processFile(File, SingleThreadResults);
        }
    }

    void writeResultsToFile(const std::unordered_map<std::string, int>& Map, const std::string& OutputFile) {
        std::ofstream OutFile(OutputFile);
        if (!OutFile.is_open()) {
            std::cerr << "Error: Could not open file " << OutputFile << " for writing." << std::endl;
            return;
        }
        int Total = 0;

        for (const auto& [Key, Val] : Map) {
            Total += Val;
            OutFile << Key << ": " << Val << std::endl;
        }
        OutFile << "Total lines: " << Total << std::endl;
        OutFile << "Files: " << Files.size() << std::endl;

        std::cout << "Results written to " << OutputFile << std::endl;
    }

    void validate() {
        std::string TD = "../testcase.cpp";

        std::unordered_map<std::string, int> TM;
        parseFile(TD, TM);

        if (TM["Multi comment"] == 3 && TM["Physical line"] == 3 && TM["Blank"] == 1 && TM["Single comment"] == 1) {
            std::cout << "Parsing works correct\n";
        } else {
            std::cout << "Parsing failed\n";
        }
    }

    void run() {
        collectFiles();

        auto StartMulti = std::chrono::high_resolution_clock::now();
        processWithThreads();
        auto EndMulti = std::chrono::high_resolution_clock::now();
        std::cout << "Multiple Threads: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(EndMulti - StartMulti).count()
                  << " microseconds" << std::endl;

        auto StartSingle = std::chrono::high_resolution_clock::now();
        processSingleThread();
        auto EndSingle = std::chrono::high_resolution_clock::now();
        std::cout << "Single Thread: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(EndSingle - StartSingle).count()
                  << " microseconds" << std::endl;

        writeResultsToFile(SingleThreadResults, "../output.txt");

        validate();
    }
};

int main() {
    FileProcessor Processor("../cgal-master/");
    Processor.run();
    return 0;
}
