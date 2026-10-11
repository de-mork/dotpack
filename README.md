# dotpack

CLI-утилита для управления вашими конфигами через симлинки и git

## Команды

### link
- Создаёт симлинки из конфига
- Флаг (--force) - перезаписывает dst (с бэкапом в dst.bak)

### scan
- Поиск конфигов в системе (~/.config и точечные файлы в `~/`)

### check
- Показывает статус симлинков

### collect
- Копирование недобавленных конфигов в ~/dotfiles + запись в конфиг
- Флаг (--all) - показывает все найденные конфиги (включая уже добавленные)

### push
- git add/commit/push в ~/dotfiles (автосообщение коммита)
- Флаг (--message) - своё сообщение коммита

## Вид конфигов в файле

```
~/.zshrc                            -> ~/dotfiles/zshrc
~/.gitconfig                        -> ~/dotfiles/gitconfig
~/.config/kitty/kitty.conf          -> ~/dotfiles/kitty/kitty.conf
...
```

## Установка

Зависимости: `gcc`/`clang`, `cmake` ≥ 3.20, git

```
git clone https://github.com/de-mork/dotpack.git
cd dotpack
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

## Лицензия

MIT
