#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/statvfs.h>
#include <ctime>

using namespace std;

/* ================= CONFIG ================= */

const double CPU_THRESHOLD = 80.0;
const int ALERT_SECONDS = 3;

int highCpuCount = 0;

/* ================= UI HELPERS ================= */

string cpuColor(double cpu) {
    if (cpu < 50) return "\033[32m";      // Green
    else if (cpu < 80) return "\033[33m"; // Yellow
    else return "\033[31m";               // Red
}

void drawBar(double percent, int width = 30) {
    int filled = percent * width / 100;

    cout << "[";
    for (int i = 0; i < width; i++) {
        if (i < filled) cout << "#";
        else cout << " ";
    }
    cout << "]";
}

/* ================= CPU ================= */

double getCPUUsage() {
    static long long prevTotal = 0, prevIdle = 0;

    ifstream file("/proc/stat");
    string line;
    getline(file, line);
    file.close();

    string cpu;
    long long user, nice, system, idle, iowait, irq, softirq, steal;
    stringstream ss(line);
    ss >> cpu >> user >> nice >> system >> idle >> iowait
       >> irq >> softirq >> steal;

    long long total = user + nice + system + idle +
                      iowait + irq + softirq + steal;
    long long idleTime = idle + iowait;

    long long totalDiff = total - prevTotal;
    long long idleDiff  = idleTime - prevIdle;

    prevTotal = total;
    prevIdle  = idleTime;

    if (totalDiff == 0) return 0.0;

    return (double)(totalDiff - idleDiff) / totalDiff * 100.0;
}

/* ================= MEMORY ================= */

void getMemoryUsage(long long &total, long long &used) {
    ifstream file("/proc/meminfo");
    string key, unit;
    long long value;

    long long memTotal = 0, memAvailable = 0;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") memTotal = value;
        if (key == "MemAvailable:") memAvailable = value;
        if (memTotal && memAvailable) break;
    }
    file.close();

    total = memTotal / 1024;
    used  = (memTotal - memAvailable) / 1024;
}

/* ================= DISK ================= */

void getDiskUsage(long long &total, long long &used) {
    struct statvfs stat;
    statvfs("/", &stat);

    unsigned long long totalBytes = stat.f_blocks * stat.f_frsize;
    unsigned long long freeBytes  = stat.f_bfree  * stat.f_frsize;

    total = totalBytes / (1024 * 1024 * 1024);
    used  = (totalBytes - freeBytes) / (1024 * 1024 * 1024);
}

/* ================= UPTIME ================= */

string getUptime() {
    ifstream file("/proc/uptime");
    double seconds;
    file >> seconds;
    file.close();

    int h = seconds / 3600;
    int m = ((int)seconds % 3600) / 60;
    int s = (int)seconds % 60;

    return to_string(h) + "h " +
           to_string(m) + "m " +
           to_string(s) + "s";
}

/* ================= ALERT LOG ================= */

void logCPUAlert(double cpuUsage) {
    ofstream log("cpu_alerts.log", ios::app);

    time_t now = time(0);
    string timestamp = ctime(&now);
    timestamp.pop_back();

    log << "[" << timestamp << "] "
        << "High CPU Usage: " << cpuUsage << "%\n";

    log.close();
}

void writeJSON(double cpu,
               long long memUsed, long long memTotal,
               long long diskUsed, long long diskTotal,
               string uptime) {

    ofstream json("web/stats.tmp");

    json << "{\n";
    json << "  \"cpu\": " << cpu << ",\n";
    json << "  \"memory_used\": " << memUsed << ",\n";
    json << "  \"memory_total\": " << memTotal << ",\n";
    json << "  \"disk_used\": " << diskUsed << ",\n";
    json << "  \"disk_total\": " << diskTotal << ",\n";
    json << "  \"uptime\": \"" << uptime << "\"\n";
    json << "}";

    json.close();

    rename("web/stats.tmp", "web/stats.json");
}


/* ================= MAIN ================= */

int main() {
    // Warm-up CPU reading
    getCPUUsage();
    sleep(1);

    while (true) {
        // Fast clear screen
        cout << "\033[2J\033[H";

        double cpu = getCPUUsage();

        // CPU alert logic
        if (cpu > CPU_THRESHOLD)
            highCpuCount++;
        else
            highCpuCount = 0;

        long long memTotal, memUsed;
        getMemoryUsage(memTotal, memUsed);

        long long diskTotal, diskUsed;
        getDiskUsage(diskTotal, diskUsed);

        double memPercent = (double)memUsed / memTotal * 100;

        cout << "===== SYSTEM MONITOR =====\n\n";

        cout << "CPU Usage    : "
             << cpuColor(cpu) << cpu << "% \033[0m";
        drawBar(cpu);
        cout << "\n";

        cout << "Memory Usage : "
             << memUsed << " MB / " << memTotal << " MB ";
        drawBar(memPercent);
        cout << "\n";

        cout << "Disk Usage   : "
             << diskUsed << " GB / " << diskTotal << " GB\n";

        cout << "Uptime       : " << getUptime() << "\n";

        if (highCpuCount >= ALERT_SECONDS) {
            cout << "\n\033[31⚠️  ALERT: High CPU Usage!\033[0m\n";
            logCPUAlert(cpu);
            highCpuCount = 0;
        }

        sleep(1);

	writeJSON(cpu, memUsed, memTotal, diskUsed, diskTotal, getUptime());

    }

    return 0;
}
