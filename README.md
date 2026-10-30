# Expense Manager

A modern, fast, and cross-platform desktop expense tracking application written in **C++** using **Dear ImGui** for the graphical user interface.

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-green)
![Dear ImGui](https://img.shields.io/badge/UI-Dear%20ImGui-orange)
![vcpkg](https://img.shields.io/badge/Package%20Manager-vcpkg-purple)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

---

## 🚀 Features

* **Transaction Management:** Add, edit, delete, and inspect income and expense entries.
* **Category Organization:** Customize categories to classify transactions effectively.
* **Filtering & Search:** Filter entries by date range, amount thresholds, categories, or transaction type.
* **Data Persistence:** Automatic loading and saving of history in JSON format.
* **Clean Architecture:** Separated into clear layers (Models, Views, Manager/Logic, and Main Application Loop).
* **Modern GUI:** Responsive and lightweight user interface powered by Dear ImGui with custom typography (`Roboto-Regular.ttf`).

---

## 🛠️ Tech Stack

* **Language:** C++17 / C++20
* **GUI Framework:** [Dear ImGui](https://github.com/ocornut/imgui)
* **Build System:** [CMake](https://cmake.org/) (v3.15+)
* **Package Manager:** [vcpkg](https://vcpkg.io/)
* **Data Serialization:** JSON
* **Auxiliary Tools:** Python 3 (for test data generation)

---

## 📂 Project Structure

```text
CPP_Project/
├── assets/             # Assets and fonts (Roboto-Regular.ttf)
├── data/               # App data storage and Python sample data generator
│   ├── data.json
│   └── generate.py
├── include/            # Header files (.hpp)
│   ├── models/         # Data structures (Transaction, Category, Filter)
│   ├── views/          # ImGui view headers (Add, Edit, Filter, List views)
│   ├── Application.hpp # Main application window lifecycle & ImGui setup
│   └── ExpenseManager.hpp # Core state management and data operations
├── src/                # Implementation files (.cpp)
│   ├── views/          # UI rendering implementations
│   ├── Application.cpp
│   ├── ExpenseManager.cpp
│   └── main.cpp        # Entry point
├── .vscode/            # Pre-configured tasks, launch, and C++ settings
├── CMakeLists.txt      # Root CMake configuration
└── vcpkg.json          # Dependency manifest
```

---

## 🔨 Build Process & Setup Guide

### 1. Prerequisites

Before building the project, ensure you have installed the following tools:

1. **C++ Compiler:**
   * **Windows:** MSVC (Visual Studio 2019/2022 with C++ Desktop Development Workload) or MinGW-w64.
   * **Linux:** `g++` (v8+) or `clang++` (v7+).
   * **macOS:** Xcode Command Line Tools (`xcode-select --install`).
2. **CMake:** Version 3.15 or higher (`cmake --version`).
3. **Git:** Required to clone the repository and `vcpkg`.
4. **vcpkg:** Microsoft's C++ Package Manager.

---

### 2. Setting Up `vcpkg` (If not already installed)

If you do not have `vcpkg` installed on your machine, follow these commands:

#### **Windows (PowerShell)**
```powershell
cd C:\
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
```

#### **Linux / macOS (Terminal)**
```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
```

*(Optional)* Set an environment variable for easier access:
* **Windows:** `[System.Environment]::SetEnvironmentVariable('VCPKG_ROOT', 'C:\vcpkg', 'User')`
* **Linux/macOS:** `export VCPKG_ROOT=$HOME/vcpkg` (add to `~/.bashrc` or `~/.zshrc`).

---

### 3. Building the Project

#### **Step 1: Clone the Repository**
```bash
git clone https://github.com/your-username/ExpenseManager.git
cd ExpenseManager
```

#### **Step 2: Configure with CMake**
Pass the `vcpkg` toolchain file during configuration so CMake can automatically locate dependencies declared in `vcpkg.json`.

* **Windows (Cmd / PowerShell):**
  ```cmd
  cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
  ```

* **Linux / macOS:**
  ```bash
  cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
  ```

#### **Step 3: Compile the Executable**
```bash
cmake --build build --config Release
```

---

### 4. Running the Application

* **Windows:**
  ```cmd
  .\build\Release\CPP_Project.exe
  ```
* **Linux / macOS:**
  ```bash
  ./build/CPP_Project
  ```

---

### 5. Building via Visual Studio Code

The repository includes pre-configured settings in `.vscode/`:

1. Open the project folder in VS Code.
2. Install the **C/C++** and **CMake Tools** extensions.
3. Open VS Code Settings (`Ctrl + ,` / `Cmd + ,`), search for `CMake: Configure Args`, and add:
   ```text
   -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg>/scripts/buildsystems/vcpkg.cmake
   ```
4. Press `F5` or click **Build & Run** on the bottom status bar.

---

## 🧪 Mock Data Generation

To generate sample data for testing:

```bash
python data/generate.py <amount>
```
This updates or populates `data/data.json` with random categories and transaction entries.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
