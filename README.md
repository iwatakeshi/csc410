# Getting Started

It is recommended to use [Visual Studio Code](https://code.visualstudio.com/) since it supports [clang-format](https://clang.llvm.org/docs/ClangFormat.html) and provides intellisense and an integrated terminal for Windows, Mac, and Linux. However, other text editors such as Atom and Sublime will work as well. If you prefer to use a terminal, you check out [vim-clang-format](https://github.com/rhysd/vim-clang-format) plugin for vim or manually format the code with `clang-format -i [file]`.

### Preparing the Development Environment

1.  Assuming we are using Linux or OSX, install the essential build tools such as gcc, g++, and make via `sudo apt install build-essential` or Xcode (via App Store).

> **Note:** It's possible to use Linux on Windows 10 via "Bash on Ubuntu on Windows". You can download Ubuntu and/or openSUSE on the Windows Store by searching either "Ubuntu" or "openSUSE".

2. Install Visual Studio Code
  > **Note:** On Windows 10, the default integrated terminal shell is PowerShell. This can be changed to Bash in File > Preferences > Settings and adding ` { "terminal.integrated.shell.windows": "C:\\Windows\\Sysnative\bash.exe" }` to the User Settings. If you prefer not to mess with the User Settings, you will need to execute `bash` in Powershell each time you open the integrated terminal.

3. Install [vscode-cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension for Visual Studio Code.
4. Install clang-format via `sudo apt install clang-format` or `brew install clang-format` on OSX.
> **Note:** On Windows 10, you can use clang-format via Bash, however, for a better experience, install clang-format using the [Windows installer](https://llvm.org/builds).

5. Add clang-format to Visual Studio Code and change the default intellisense engine:

**Windows:** 

Go to File > Preferences > Settings and add:

```json
{
  "C_Cpp.clang_format_path": "C:\\Program Files (x86)\\LLVM\\bin\\clang-format.exe",
  "C_Cpp.intellisenseEngine": "Default"
}
```

**Linux:**

Find the path of clang-format:

```bash
which clang-format
```
Go to File > Preferences > Settings and add:
```json
{
  "C_Cpp.clang_format_path": "{ Full path of clang-format here }",
  "C_Cpp.intellisenseEngine": "Default"
}
```

**OSX:**

Find the path of clang-format:

```bash
which clang-format
```
Go to Code > Preferences > Settings and add:
```json
{
  "C_Cpp.clang_format_path": "{ Full path of clang-format here }",
  "C_Cpp.intellisenseEngine": "Default"
}
```

### Contributing to the Project

Simply fork the project on [Github](https://github.com) and make the changes locally on your computer. Once you have made the changes and are ready to push the changes, [format the code](https://stackoverflow.com/questions/29973357/how-do-you-format-code-in-visual-studio-code-vscode) and create a pull request. The changes will then be merged into the main branch.

> **Note:** On Windows and OSX, you can use [Github for Desktop](https://desktop.github.com/) to easily create a commit and push the changes. On Linux, you can use [GitKraken](https://www.gitkraken.com/) and it's [free for students](https://www.gitkraken.com/github-student-developer-pack). Otherwise, you will need to install [git](https://git-scm.com/).

### Building the Project

Clone the forked project onto your computer and open the root directory `csc410/` from Visual Studio Code. To open Visual Studio Code from Bash:

```bash
# Set the current dir
cd csc410/
# Open the current dir in vscode
code .
```

Then open an integrated terminal (optinal) and run make from `a1/` as shown below.

```bash
cd a1/
# Get the dependencies for the project (one time only)
cd make dep
# Make the project with the depenencies
cd make
```

### Cleaning the project

There are two commands to clean the project:

```bash
# Clean the auxiliary files
make clean

# Clean the dependencies
make clean-dep

# Clean both
make clean*
```

While it's not necessary to run `clean-dep`, it might be good to do so.
