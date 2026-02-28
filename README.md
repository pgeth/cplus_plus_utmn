# Программирование и алгоритмизация на С++(ТюмГУ 2026, Январь-Июнь).

Преподователь: Анна Георгиевна Царина

---

## Настройка VS Code для компиляции и запуска отдельных файлов C++

**Окружение:** macOS Tahoe, Apple M4 (arm64)

```
clang++ --version
Apple clang version 17.0.0 (clang-1700.6.3.2)
Target: arm64-apple-darwin25.3.0
```

---

### Шаг 1. Установить расширения VS Code

- **C/C++** (Microsoft) — IntelliSense, подсветка, отладка
- **Code Runner** (Jun Han) — запуск файла одной кнопкой

---

### Шаг 2. Настроить Code Runner в settings.json

Открыть палитру команд `Cmd+Shift+P` → **Preferences: Open User Settings (JSON)** и добавить:

```json
"code-runner.runInTerminal": true,
"code-runner.executorMap": {
  "cpp": "cd $dir && clang++ -std=c++23 -O2 \"$fileName\" -o \"$fileNameWithoutExt\" && \"./$fileNameWithoutExt\""
}
```

- `runInTerminal: true` — вывод идёт во встроенный терминал VS Code (иначе в Output, где нет интерактивного ввода)
- `clang++` — компилятор из Xcode Command Line Tools (уже есть на Mac)
- `-std=c++23` — стандарт C++23
- `-O2` — оптимизация (как на большинстве контестов)
- Команда сначала компилирует, затем запускает бинарник в той же папке

---

### Шаг 3. Привязать запуск к клавише F5

Открыть `Cmd+Shift+P` → **Preferences: Open Keyboard Shortcuts (JSON)** и добавить:

```json
{
  "key": "f5",
  "command": "code-runner.run",
  "when": "editorTextFocus"
}
```

Теперь `F5` — скомпилировать и запустить текущий открытый `.cpp` файл.

> По умолчанию `F5` запускает отладчик (`workbench.action.debug.start`). Новая привязка перекрывает его при фокусе в редакторе.

---

### Шаг 4. Файлы конфигурации проекта (.vscode/)

Папка `.vscode/` в корне проекта хранит настройки для этого workspace.

#### `.vscode/c_cpp_properties.json`

IntelliSense: подсветка, автодополнение, навигация по коду.

```json
{
  "configurations": [
    {
      "name": "Mac",
      "includePath": ["${workspaceFolder}/**"],
      "defines": [],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c17",
      "cppStandard": "c++23",
      "intelliSenseMode": "macos-clang-arm64"
    }
  ],
  "version": 4
}
```

#### `.vscode/tasks.json`

Сборка через `Cmd+Shift+B` (без запуска). Используется также отладчиком как шаг сборки перед запуском.

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: g++ сборка активного файла",
      "command": "/usr/bin/g++",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-std=c++23",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

- Флаг `-g` — включает отладочную информацию (нужна для дебаггера)
- Без `-O2`, т.к. для отладки оптимизация мешает

#### `.vscode/launch.json`

Конфигурация отладчика (`lldb`). Работает для любого открытого `.cpp` файла — перед запуском автоматически вызывается сборка.

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug current file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "externalConsole": false,
      "MIMode": "lldb",
      "preLaunchTask": "C/C++: g++ сборка активного файла"
    }
  ]
}
```

Ключевые моменты:
- `"externalConsole": false` — встроенный терминал VS Code (при `true` открывается Terminal.app, который на Apple Silicon вспыхивает и закрывается пустым)
- `"program": "${fileDirname}/${fileBasenameNoExtension}"` — динамический путь, работает для любого открытого файла
- `"preLaunchTask"` — автоматически запускает сборку из `tasks.json` перед отладкой

---

### Итоговый рабочий процесс

| Действие | Команда |
|---|---|
| Запустить текущий `.cpp` файл | `F5` (Code Runner) |
| Только собрать (без запуска) | `Cmd+Shift+B` (tasks.json) |
| Запустить отладчик | Панель Run & Debug → **Debug current file** |
| Открыть терминал | `` Ctrl+` `` |

**Основной сценарий для задач:** открыть файл задачи → `F5` → результат в терминале.
