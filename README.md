# 🖥 System Monitor Tool (Linux)

A *C++17 console-based real-time System Monitoring Tool* built for Linux.  
This project displays CPU usage, memory usage, uptime, and active processes — similar to the Linux top command.  
It was developed as part of the *Wipro On-Campus Capstone Project (2025)* under *Linux OS & LSP* modules.

---

## 🎯 Project Objective
The primary goal of this project is to design and develop a *lightweight and efficient system monitoring tool* using C++ that interacts directly with the Linux /proc filesystem.

This tool provides:
- *CPU Utilization Percentage*
- *Memory Usage* (Total, Used, Available)
- *Active Process List* (PID, Command, Memory, CPU Time)
- *System Uptime*
- *Auto Refresh* every 2 seconds

---

## ⚙ Features

✅ Real-time CPU and memory statistics  
✅ Process table with PID, Command, RSS (Memory in KB), and CPU Time  
✅ Clear, formatted, and auto-updating display  
✅ Built using only system calls and C++ standard libraries  
✅ Modular architecture (separate header & source files)  
✅ Easy to compile with Makefile  

---

## 🛠 Technologies Used

| Component | Description |
|------------|-------------|
| *Language* | C++17 |
| *Environment* | Ubuntu (via WSL - Windows Subsystem for Linux) |
| *Build Tool* | GNU Make |
| *Editor* | Visual Studio Code |
| *System Interface* | /proc filesystem (cpuinfo, meminfo, stat, uptime) |

---

## 🧱 Project Structure

# 🖥 System Monitor Tool (Linux)

A *C++17 console-based real-time System Monitoring Tool* built for Linux.  
This project displays CPU usage, memory usage, uptime, and active processes — similar to the Linux top command.  
It was developed as part of the *Wipro On-Campus Capstone Project (2025)* under *Linux OS & LSP* modules.

---

## 🎯 Project Objective
The primary goal of this project is to design and develop a *lightweight and efficient system monitoring tool* using C++ that interacts directly with the Linux /proc filesystem.

This tool provides:
- *CPU Utilization Percentage*
- *Memory Usage* (Total, Used, Available)
- *Active Process List* (PID, Command, Memory, CPU Time)
- *System Uptime*
- *Auto Refresh* every 2 seconds

---

## ⚙ Features

✅ Real-time CPU and memory statistics  
✅ Process table with PID, Command, RSS (Memory in KB), and CPU Time  
✅ Clear, formatted, and auto-updating display  
✅ Built using only system calls and C++ standard libraries  
✅ Modular architecture (separate header & source files)  
✅ Easy to compile with Makefile  

---

## 🛠 Technologies Used

| Component | Description |
|------------|-------------|
| *Language* | C++17 |
| *Environment* | Ubuntu (via WSL - Windows Subsystem for Linux) |
| *Build Tool* | GNU Make |
| *Editor* | Visual Studio Code |
| *System Interface* | /proc filesystem (cpuinfo, meminfo, stat, uptime) |

---

## 🧱 Project Structure

SystemMonitor/
│
├── cpu.cpp
├── cpu.h
├── memory.cpp
├── memory.h
├── process.cpp
├── process.h
├── main.cpp
└── Makefile


---

## 🏗 Implementation Steps

### 1️⃣ Setup Environment
Install required packages:
```bash
sudo apt update
sudo apt install g++ make git -y
