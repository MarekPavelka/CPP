#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>
#include <sstream>
#include <fstream>
#include <vector>

namespace utils {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    extern std::string generate_uuid() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }

    void string_split(const std::string& str, const char delimiter, std::vector<std::string>& parts) {
        std::stringstream ss(str);
        std::string part;
        while (getline(ss, part, delimiter)) {
            parts.push_back(std::move(part));
        }
    }

    void file_read(const std::string& filename, std::vector<std::string>& lines) {
        std::ifstream fin;
        fin.open(filename);
        if (!fin.is_open()) { return; }
        std::string line;
        while (std::getline(fin, line)) {
            lines.push_back(line);
        }
        fin.close();
    }

    void file_write(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream fout;
        fout.open(filename, std::ios::out | std::ios::trunc);
        if (!fout.is_open()) { return; }
        for (const auto& line : lines) {
            fout << line << std::endl;
        }
        fout.close();
    }
}

#endif //UTILS_HPP


