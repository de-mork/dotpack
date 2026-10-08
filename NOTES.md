# Команды

## link
Создаёт симлинки из конфига.
- Если dst — уже симлинк на src: пропускает (OK)
- Если dst — симлинк на другое: ошибка
- Если dst — реальный файл: ошибка
- Если dst — не существует: создаёт

### link --force
Перезаписывает dst (с бэкапом в dst.bak).

## check
Диагностика. Ничего не меняет.
Для каждого Entry показывает статус:
- OK: симлинк на src
- MISSING: dst не существует
- WRONG_LINK: симлинк, но не на src
- REAL_FILE: dst — реальный файл
- BROKEN: битый симлинк

## push
git add/commit/push в ~/dotfiles.

## scan
Поиск конфигов в системе.

## collect
Копирование в ~/dotfiles + запись в конфиг.

## setup
Мастер: scan → collect → link → push (с вопросами y/n после каждого шага).


# Вид конфигов в файле

```
~/.zshrc                       ->  ~/dotfiles/zshrc
~/.gitconfig                   ->  ~/dotfiles/gitconfig
~/.config/kitty/kitty.conf     ->  ~/dotfiles/kitty/kitty.conf
```
Оба пути - с `~`, разворачиваются в read_config.

# Архитектура
Файлы:
- src/main.cpp       - Общий сбор всех комманд
- src/config.cpp/.h  - Париснг конфигов
- src/utils.cpp/.h   - Полезные функции
- src/commands/      - содержит в себе всю логику команд
    scan.cpp/.h
    check.cpp/.h
    link.cpp/.h
    collect.cpp/.h
    push.cpp/.h
    setup.cpp/.h

# Коды ошибок:
0 - успешно
1 - ошибка filesystem
2 - неверные аргументы
3 - команда не найдена

# Архитектура поиска

## Функция (внутренняя)
scan_directories(paths, filters) → vector<path>
  - обход директорий
  - фильтрация кандидатов
  - исключения (.cache, .git, node_modules и т.д.)

## scan (команда)
run_scan():
  - вызывает scan_directories
  - печатает список кандидатов
  - ничего не меняет

## collect (команда-мастер)
run_collect():
  - вызывает scan_directories (не run_scan!)
  - показывает список
  - спрашивает пользователя (y/n по каждому)
  - копирует выбранные в ~/dotfiles/
  - дописывает в ~/.config/dotpack/config

## Итог
- 1 логика поиска (scan_directories)
- 2 команды (scan, collect)
- collect использует функцию поиска, а не команду

# Сделано
- [x] симметричный формат конфига
- [x] config.cpp — парсер (read_config, Entry)
- [x] Entry { system_path, repo_path }
- [x] utils.cpp - файл под полезные мини-функции (trim, expand_tilde, home_dir, config_path, dotfiles_dir) 
- [x] link читает конфиг и создаёт симлинки
- [x] dotfiles репо с 3 конфигами (zshrc, gitconfig, kitty)
- [x] реализован push (git add/commit/push в ~/dotfiles)
- [x] read_config разворачивает ~ в обеих частях
- [x] run_link берёт пути из Entry
- [x] убрать update, добавить заглушку check
- [x] реализовать check (диагностика)
- [x] улучшить link: already linked / wrong link
- [x] link_one: создавать родительские папки dst через fs:create_directories

# Следующее
- [ ] push: не считать "nothing to commit" ошибкой (через git diff --cached --quiet)
- [ ] реализовать scan (scan_directories + run_scan)
- [ ] реализовать collect
- [ ] реализовать setup (мастер)
- [ ] README
- [ ] LICENSE MIT
- [ ] cmake --install
- [ ] XBPS/AUR пакет
- [ ] public dotpack
