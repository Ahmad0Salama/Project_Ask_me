# Q&A System

This project is a command-line Q&A platform inspired by basic social Q&A features. It allows multiple users to interact by asking and answering questions. The system maintains user accounts and questions with persistence across sessions using file-based storage. Key components include user management, question management, and basic authentication.

The system uses object-oriented programming principles, with classes for `user` and `questions`. It handles input validation, menu-driven navigation, and error handling for invalid operations.

**Note:** This is a basic implementation and not intended for production use without enhancements like encryption for passwords, concurrency handling, or a real database.

## 🚀 Features

- **User Management:**
  - Sign up with a unique ID, name, and password.
  - Log in with ID and password.
  - Change name or password.
  - Delete user account (which also deletes associated questions).
  - List all system users.

- **Question Management:**
  - Ask a question to another user by their ID.
  - Answer unanswered questions directed to you.
  - View questions asked by you (to others).
  - View questions directed to you (answered and unanswered).
  - Delete your own questions.
  - View the system feed (all questions).

- **Persistence:**
  - Data is saved automatically after operations.
  - Reloads data on startup or menu navigation.

- **Validation and Security:**
  - Input validation for integers, strings, and ranges.
  - Access control: Users can only modify their own data.
  - Basic error handling for invalid IDs or operations.

- **Other:**
  - Menu-driven interface for ease of use.
  - Supports multiple users (though not concurrent; single-threaded).

## 📜 Database Technique

The system uses a simple file-based persistence mechanism instead of a full database like SQL or NoSQL. This is suitable for a lightweight, educational project.

- **Storage Files:**
  - `database/users.txt`: Stores user data (ID, name, password).
  - `database/questions.txt`: Stores question data (ID, owner ID, target user ID, question text, answer text or "NULL", validity flag).

- **Technique:**
  - **Serialization:** Objects are written to text files using overloaded `<<` operators for streaming data in a space-separated format. Strings with spaces are quoted.
  - **Deserialization:** Data is read back using `ifstream`, parsing lines to reconstruct `user` and `questions` objects.
  - **State Management:** Global maps (`curr_users` and `curr_questions`) hold in-memory objects. Files are loaded on startup (`LoadDataBase()`) and saved after changes (`SaveDataBase()`).
  - **ID Generation:** Auto-incrementing IDs for users and questions, persisted in files.
  - **Directory Handling:** Uses `std::filesystem` (C++17) to create the `database/` directory if it doesn't exist.
  - **Limitations:** No encryption (passwords stored in plain text), no transactions, and potential issues with concurrent access. For production, migrate to a proper database like SQLite.

## 📦 Requirements

- C++ compiler (e.g., g++ with C++17 support).
- Standard libraries (included via `<bits/stdc++.h>` and `<filesystem>`).

Tested on:
- Compiler: g++ (GCC 11+)
- OS: Linux/Mac/Windows (with C++17 filesystem support).

## 🔧 Installation & Running

1. Open your terminal.
2. Run:
   ```bash
   git clone https://github.com/Ahmad0Salama/Project_Ask_me
   ```
3. Navigate to the project directory:
   ```bash
   cd Project_Ask_me
   ```

## 🧑‍💻 How to Run

1. **Compile the Code:**
   ```bash
   g++ -std=c++17 main.cpp -o qa_system
   ```
   - Use `-std=c++17` to enable filesystem features.
   - On Windows, you may need additional flags if using MinGW.

2. **Run the Executable:**
   ```bash
   ./qa_system
   ```
   - On Windows: `qa_system.exe`.

3. **Interact with the System:**
   - Follow the menu prompts.
   - Sign up or log in to start.
   - The `database/` folder will be created automatically for data storage.

4. **Example Usage:**
   - Sign up: Create a new user.
   - Ask a question: Select "Ask Question" and enter another user's ID.
   - Exit: Saves data automatically.

**Note:** If compilation fails due to filesystem issues, ensure your compiler supports C++17. Clean the `database/` folder to reset data.

## 🤝 How to Contribute

We welcome contributions to improve the project! Follow these steps:

1. **Fork the Repository:**
   - Click "Fork" on the GitHub repo page.

2. **Clone Your Fork:**
   ```bash
   git clone https://github.com/your-username/qa-system.git
   ```

3. **Create a Branch:**
   ```bash
   git checkout -b feature/your-feature-name
   ```

4. **Make Changes:**
   - Add features, fix bugs, or improve documentation.
   - Ensure code follows C++ best practices (e.g., no memory leaks, proper error handling).

5. **Commit Changes:**
   ```bash
   git commit -m "Add your commit message"
   ```

6. **Push to Your Fork:**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create a Pull Request:**
   - Go to the original repo and click "New Pull Request".
   - Describe your changes clearly.
