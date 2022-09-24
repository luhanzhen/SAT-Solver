#pragma once
#include<chrono>
#include<regex>
using namespace std;
using namespace std::chrono;


void initcsv()
{
	ofstream out("CNF_SAT_OUT.csv", ios::trunc);
	out << "instance, init_time(ms),algorithms1,search_time(ms),algorithms2,search_time(ms),algorithms3,search_time(ms),runtime_date" << endl;
	out.close();

}

#ifdef _WIN32

#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;

void getallfiles(const fs::path str_path, vector<fs::path>& files) {
	regex cnf("^.*\\.cnf$");
	for (auto& fe : fs::directory_iterator(str_path)) {
		const auto& fp = fe.path();
		auto ffilename = fp.filename();

		if (fs::is_directory(fe)) {
			if (ffilename != "." && ffilename != "..") {
				getallfiles(fp, files);
			}
		}
		else {

			if (regex_match(fp.filename().string(), cnf))
				files.push_back(fp);
		}
	}
}


void int2str(const int& int_temp, string & string_temp) {
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   // stream>>string_temp
}

template<typename t>
t str2number(const string & string_temp) {
	t res;
	stringstream stream(string_temp);
	stream >> res;
	return res;
}

#elif defined(__GNUC__) || defined(__GNUG__)
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

bool getallfiles(const std::string& dir_in, std::vector<std::string>& files) {
	regex cnf("^.*\\.cnf$");
	if (dir_in.empty()) {
		return false;
	}
	struct stat s;
	stat(dir_in.c_str(), &s);
	if (!S_ISDIR(s.st_mode)) {
		return false;
	}
	DIR* open_dir = opendir(dir_in.c_str());
	if (NULL == open_dir) {
		std::exit(EXIT_FAILURE);
	}
	dirent* p = nullptr;
	while ((p = readdir(open_dir)) != nullptr) {
		struct stat st;
		if (p->d_name[0] != '.') {
			
			std::string name = dir_in + std::string("//") + std::string(p->d_name);
			stat(name.c_str(), &st);
			if (S_ISDIR(st.st_mode)) {
				getallfiles(name, files);
			}
			else if (S_ISREG(st.st_mode)) {
				if (regex_match(name, cnf))
					files.push_back(name);
			}
		}
	}
	closedir(open_dir);
	return true;
}

#endif


class Timer {
public:
	Timer() : m_begin(high_resolution_clock::now()) {}
	void reset() { m_begin = high_resolution_clock::now(); }

	//	//ƒ¨»œ ‰≥ˆ√Î
	//	double elapsed() const {
	//		return duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
	//	}

		//ƒ¨»œ ‰≥ˆ∫¡√Î
	int64_t elapsed() const {
		return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//Œ¢√Î
	int64_t elapsed_micro() const {
		return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//ƒ…√Î
	int64_t elapsed_nano() const {
		return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//√Î
	int64_t elapsed_seconds() const {
		return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
	}

	//∑÷
	int64_t elapsed_minutes() const {
		return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
	}

	// ±
	int64_t elapsed_hours() const {
		return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
	}

private:
	time_point<high_resolution_clock> m_begin;
};
