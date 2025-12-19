\# System Monitoring Tool (C++)



A Linux-based system monitoring tool built in C++ that displays real-time system statistics.



\## Features

\- CPU usage (time-differential calculation)

\- Memory usage (using MemAvailable)

\- Disk usage (statvfs system call)

\- System uptime

\- Live refresh every second



\## Concepts \& Technologies

\- Linux `/proc` virtual filesystem

\- Kernel ↔ user space interaction

\- CPU performance counters

\- Linux memory management

\- Filesystem statistics

\- System calls (`statvfs`)



\## Project Structure

system\_monitor/

├── prototypes/ # Individual learning modules

│ ├── cpu.cpp

│ ├── memory.cpp

│ ├── disk.cpp

│ ├── uptime.cpp

│ └── meminfo.cpp

│

├── system\_monitor.cpp # Final integrated monitor

└── README.md

