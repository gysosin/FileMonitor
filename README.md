```markdown
# 📁 FileMonitor - Windows MiniFilter Driver

🛡️ **FileMonitor** is a lightweight kernel-mode MiniFilter driver for Windows that logs file activity like creation, reading, writing, and deletion.

---

## 🚀 Features

- Logs key file system operations:
  - 📄 Create / Open
  - ✏️ Read / Write
  - 🗑️ Delete / Rename
- Uses `DbgPrint` for logging (view via DebugView)
- Built with WDK + KMDF in C++
- Great for auditing or forensic tools

---

## 🛠 Requirements

- Windows 10/11 x64
- Visual Studio 2019/2022 + Windows Driver Kit (WDK)
- 🔧 **Secure Boot disabled**
- 🧪 **Test signing enabled** (`bcdedit /set testsigning on`)

---

## 🏗 Build Instructions

1. Open `FileMonitor.sln` in Visual Studio
2. Set build config to: `Release | x64`
3. Build the project → generates `FileMonitor.sys` and `FileMonitor.inf`

---

## ⚙️ Installation

```powershell
sc create FileMonitor type= kernel binPath= "C:\Path\To\FileMonitor.sys"
sc start FileMonitor
```

Check it's running:

```powershell
fltmc
```

---

## 🔍 View Logs (DbgPrint)

1. Download **DebugView** from Sysinternals
2. Run as Admin
3. Enable ✅ *Capture Kernel*
4. Open / create / modify files → watch logs appear like:

```
FileMonitor: Operation 3 on \Device\...\file.txt
```

---

## 🧼 Uninstall

```powershell
sc stop FileMonitor
sc delete FileMonitor
```

---

## ⚠️ Disclaimer

This driver is test-signed and intended for development use only. Do **not** deploy on production systems without proper signing.

---

## 📄 License

MIT License