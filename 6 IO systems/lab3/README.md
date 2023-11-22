# Лабораторная работа 3

**Название:** "Разработка драйверов сетевых устройств"

**Цель работы:** получить знания и навыки разработки драйверов сетевых интерфейсов для операционной системы Linux.

## Описание функциональности драйвера
Согласно заданному варианту (4), разработанный драйвер создаёт виртуальный сетевой интерфейс, перехватывает udp-пакеты и выводит следующую информацию о перехваченном пакете: 
- адрес отправителя (saddr)
- адрес получателя (daddr)
- длину сообщения (data length)
- само перехваченное сообщение (data)

## Инструкция по сборке
Для запуска
```
make
make test
```

Для отключения
```
make exit
make clean
```

## Инструкция пользователя
После запуска введите команду такого вида:
```
echo -n <your string> > /dev/udp/<host>/<port>
```
И затем проверьте `dmesg -T` для просмотра выведенной информации в лог.

Также вся информация о прехваченном пакете записывается в /proc/vni_custom. Для просмотра воспользуйтесь командой:
```
cat /proc/vni_custom
```

## Пример использования
![dmesg](https://github.com/IP-13/IO-systems/blob/main/lab3/dmesg.png)

![proc](https://github.com/IP-13/IO-systems/blob/main/lab3/proc.png)