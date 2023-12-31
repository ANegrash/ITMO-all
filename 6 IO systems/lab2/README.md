# Лабораторная работа 2

**Название:** "Разработка драйверов блочных устройств"

**Цель работы:** получить знания и навыки разработки драйверов блочных устройств для операционной системы Linux.

## Описание функциональности драйвера
Согласно заданному варианту (4) драйвер создаёт виртуальный жёсткий диск в оперативной памяти с размером 50 Мбайт и разбивает его на 3 первичных раздела объёмами 10, 25 и 15 Мбайт.

## Инструкция по сборке
[Makefile](/lab2/Makefile) помимо команд `all` и `clean`, предназначенных для сборки и удаления, содержать команды `insmod` и `rmmod`.

`insmod` - загружает модуль в ядро.

`rmmod` - выгружает модель из ядра.

Эти команды вызывают shell-скрипты и созданы лишь для удобства.

## Инструкция пользователя
После загрузки модуля появится новые файлы `/dev/vramdisk` и `/dev/vramdisk<1-3>`. В списке блочных устройств появятся 4 новых записи

## Примеры использования
`mkfs.vfat /dev/vramdisk<1-3>` - создать файловую систему vfat на разделе vramdisk<1-3> диска

`mkdir /mnt/vramdisk` – создать директорию для монтирования диска

`mount -t vfat /dev/vramdisk<1-3> /mnt/vramdisk` - смонтировать файловую систему в директорию

#### Пример раздела объёмом 25 Мбайт
![раздел объёмом 25 Мбайт](/lab2/screenshots/25Mb_sample.png)

#### Копирование между разделами созданного виртуального диска
![копирование между разделами созданного виртуального диска](/lab2/screenshots/copy_virtual2virtual.png)

или

pv /mnt/testFolder1/file2copy > /mnt/testFolder2/copiedFile

10,0MiB 0:00:00 [ 448MiB/s] [==============================================================================>] 100%

#### Копирование между разделом созданного виртуального диска и реального
![копирование между разделом созданного виртуального диска и реального](/lab2/screenshots/copy_virtual2real.png)

или

pv /mnt/testFolder1/file2copy > ~/copiedFile

10,0MiB 0:00:00 [ 422MiB/s] [==============================================================================>] 100%
