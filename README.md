# Linux System Monitor with Web Dashboard

A Linux-based system monitoring tool written in **C++** that collects real-time system statistics and visualizes them through a **web dashboard** using HTML, CSS, and JavaScript.

This project demonstrates **system-level programming**, **full-stack integration**, and **real-time data visualization** without using heavy frameworks.

---

## 🚀 Features

- 📊 Real-time **CPU usage** calculation using `/proc/stat`
- 🧠 **Memory usage** monitoring using `/proc/meminfo`
- 💽 **Disk usage** using `statvfs`
- ⏱ **System uptime** display
- 🔄 Live updates every second
- 🌐 Web-based dashboard with modern glassmorphism UI
- 🚨 Visual CPU spike glow for high CPU usage
- 🔐 Atomic file updates to prevent race conditions

---

## 🛠 Tech Stack

### Backend
- **C++**
- Linux `/proc` filesystem
- POSIX system calls

### Middleware
- JSON file (`stats.json`)
- Python HTTP server

### Frontend
- HTML
- CSS (Glassmorphism UI)
- JavaScript (Fetch API)

---

## 🧩 Project Architecture

Linux Kernel
↓
C++ System Monitor
↓
stats.json (atomic update)
↓
Python HTTP Server
↓
HTML / CSS / JavaScript Dashboard

yaml
Copy code

---

## ▶️ How to Run

### 1️⃣ Compile the monitor
```bash
g++ system_monitor.cpp -o monitor
2️⃣ Start the system monitor
bash
Copy code
./monitor
3️⃣ Start the web server (in another terminal)
bash
Copy code
cd web
python3 -m http.server
4️⃣ Open in browser
arduino
Copy code
http://localhost:8000
📁 Project Structure
markdown
Copy code
system_monitor/
├── system_monitor.cpp
├── README.md
├── .gitignore
└── web/
    ├── index.html
    ├── style.css
    ├── script.js
    └── ima.jpg
