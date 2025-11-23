# 🚧 **GATE MANAGEMENT SYSTEM (C Programming)**
## 📄 **ABSTRACT**

The **Gate Management System** is a terminal-based **C** application designed to record and manage entry and exit details of individuals or vehicles at a security gate. It enables security personnel or administrators to **add**,**view**, **search**, **update**, and delete gate entry logs efficiently.

All records are permanently stored in a binary file (`gate_data.txt`), ensuring that data remains safe even if the program is closed.

This project uses essential C concepts including **structures**, **file handling**, **loops**, **conditionals**, and **modular programming**, making it suitable for **academic mini-projects**, **learning assignments**, and **beginner-level practice**.

---

## ✨ **FEATURES**

### **Core Functionalities**

- ➕ **Add new gate entry records**
- 📋 **View all recorded logs** in a structured table format
- 🔍 **Search entry records using unique ID**
- ✏️ **Update stored gate record details**
- ❌ **Delete any record using safe temporary file handling**
- 💾 Stores all data permanently in (`gate_data.txt`)
- 🖥️ Fully terminal-based menu-driven system
- 👨‍💻 Easy to understand and modify
- ⚙️ Automatically creates data file if missing
- ⚠️ Includes basic input validation and error handling

  ---

## 🛠️ **TECHNICAL REQUIREMENTS**

### **System Requirements**

- OS: **Windows / Linux / macOS**
- Command Prompt or Terminal
- Minimum **4 MB RAM**
- Small disk space for `gate_data.txt`

### **Software Requirements**

- C Compiler: **GCC / MinGW / Clang / MSVC**
- Editor: VS Code, Turbo C, Dev-C++, Code::Blocks, etc.
- Optional: **Makefile support**

### **Programming Requirements**

- Language: **C**
- Standards **Supported: C89 / C99 / C11**
- Required Headers:

- `stdio.h`

- `stdlib.h`

- `string.h`

### **File Handling**

- Binary file storage (`gate_data.txt`)
- Auto-created if not found
- Requires read/write permissions

  ---

  ## 📌 **FUNCTIONAL REQUIREMENTS**
  
  ### **User Interface**
  - Menu-driven
  - Command-line based
  - Handles invalid inputs safely
  
    ---
    
## 🚧 **GATE ENTRY OPERATIONS**
## ➕ **Add Gate Record**

- User can enter:

- Record ID

- Person/Vehicle Name

- Purpose / Description

- Time of Entry

- Time of Exit

- Gate Number
- Stored safely in gate_data.txt

### 📋 **View Records**

- Displays all stored gate entries in a formatted table layout.

### 🔍 **Search Records**

- Search using unique Record ID.

### ✏️ **Update Records**

- Modify stored fields:

- Name

- Purpose

- Entry/Exit time

- Gate number, etc.

### ❌ **Delete Record**
- Uses temporary file method
- Safely removes selected record without data corruption

### 🔧 **DATA MANAGEMENT**

- Fast access with binary file handling
- Safe update and deletion methods
- Handles missing or empty data files gracefully

### 🔄 **PROGRAM FLOW**

-Menu executes repeatedly until Exit is selected
-Each action provides success/failure messages
-Smooth structured navigation for users

  ---
  
##▶️ **Running the Program**

### 1️⃣ **Compile**
```bash
gcc gate_management.c -o gate
```

### 2️⃣ Run
**Linux/macOS**
```bash
./gate
```

**Windows**

```
gate.exe
```

### 3️⃣ Data File

 *Automatically creates gate_data.txt
 *Saves data in binary format

---

## 📸 **Screenshots (Optional)**
*Add Gate Entry Screen
*<img width="393" height="281" alt="Screenshot 2025-11-23 152726" src="https://github.com/user-attachments/assets/d3733083-2407-432d-9ea7-8f347a6c6669" />

*<img width="399" height="281" alt="Screenshot 2025-11-23 152742" src="https://github.com/user-attachments/assets/84a83261-91c2-4491-b0ce-72e5a66ed959" />


*View Records
<img width="370" height="394" alt="Screenshot 2025-11-23 152808" src="https://github.com/user-attachments/assets/1d583933-2a0d-492f-a246-870a98cbf4f4" />


*Search Entry
<img width="421" height="311" alt="Screenshot 2025-11-23 152831" src="https://github.com/user-attachments/assets/51a1ce5e-6594-4962-b29e-6e4aaaec7b35" />


*Exit Screen
*<img width="365" height="196" alt="Screenshot 2025-11-23 152842" src="https://github.com/user-attachments/assets/b350705a-d4e4-4614-9e02-df645b99dd9c" />


##📝 **Author**

**Ravipati Koushik Sriram**
