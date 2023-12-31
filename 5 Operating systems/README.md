# Операционные системы
**Автор:** Неграш Андрей

**Преподаватель:** Осипов Святослав Владимирович

Университет ИТМО, 2023

Трек "3"

## Задания 1 и 2
Excel-книга с решением в формате [xlsx](https://github.com/ANegrash/ITMO-all/tree/master/5%20Operating%20systems/tasks_1_and_2.xlsx)

**Вариант:** 25645

## Теория для задания 1
Краткая справка по алгоритмам планирования и парочка определений. Данные взяты из [книги Вильяма Столлингса](https://github.com/ANegrash/ITMO-all/tree/master/5%20Operating%20systems/Stollings_Operating_systems_rus.pdf), глава 9.2.

*Невытесняющие стратегии* (режимы принятия решения) - это такие стратегии, при которых попавший на процессор (выполняющийся) процесс будет продолжать выполнение, пока не завершится, либо пока не "уйдёт" на операцию ввода-вывода.

*Вытесняющие стратегии* (режимы принятия решения) - это такие стратегии, при которых выполняющийся в настоящий момент процесс может быть прерван и переведен операционной системой в состояние готовности к выполнению (помещён в очередь на выполнение). Произойти это может из-за появления процесса, имеющего больший приоритет, нежели есть у выполняющегося. Приоритетность определяется алгоритмом планирования.

### FCFS (First Come, First Served)
Самый простой метод, процессы обрабатываются в процессе их прибытия.

Короткие процессы:
- Могут быстро завершаться, если находятся в начале очереди
- Долго ждать, если перед ним длинный процесс

Длинные процессы:
- Вызывают значительное время ожидания для всех последующих процессов, независимо от их длины

### RR-1 (Round Robin)
Использует квантование времени (в данном случае 1 мс) - то есть каждую 1 мс происходит прерывание, во время которого выполняемый процесс помещается в конец очереди, а затем из очереди берётся процесс по алгоритму FCFS. Соответственно, если на процессоре всего одна задача, то после каждого сброса будет выбираться один и тот же процесс.

Короткие процессы:
- Будут выполняться быстро, так как время ожидания зависит от длины очереди, а не от длины предшествующих процессов

Длинные процессы:
- Будут часто прерываться, что увеличит время их выполнения

### RR-4 (Round Robin)
Использует квантование времени (в данном случае 4 мс) - то есть каждые 4 мс происходит прерывание, во время которого выполняемый процесс помещается в конец очереди, а затем из очереди берётся процесс по алгоритму FCFS. Соответственно, если на процессоре всего одна задача, то после каждого сброса будет выбираться один и тот же процесс.

Короткие процессы:
- Будут выполняться дольше, чем в RR-1, так как длинные процессы будут занимать процессор больше времени (полный квант), но всё ещё лучше FCFS

Длинные процессы:
- Будут более производительны из-за большего кванта времени

### SPN (Shortest Process Next)
*Невытесняющая* стратегия, при которой для выполнения выбирается процесс с наименьшим ожидаемым временем выполнения. В реальном мире мы обычно не знаем, сколько процесс будет выполняться, но в лабораторной это дано. МОжно использовать в системе, в которой не предполагается большого количества длинных процессов.

Короткие процессы:
- Получают явное преимущество и выполняются очень эффективно

Длинные процессы:
- Могут страдать от "голодания", поскольку более короткие процессы будут их постоянно обгонять в очереди
- Трудно или невозможно предсказать время выполнения

### SRT (Shortest Remaining Time)
*Вытесняющая* версия стратегии SPN. Планировщик выбирает процесс с наименьшим ожидаемым временем до окончания процесса. При присоединении нового процесса к очереди готовых к выполнению процессов может оказаться, что его оставшееся время в действительности меньше, чем оставшееся время выполняемого в настоящий момент процесса. Планировщик, соответственно, может применить вытеснение при готовности нового процесса.

Короткие процессы:
- Ещё лучше и эффективнее, так как получают преимущество сразу при добавлении в очередь

Длинные процессы:
- В наиболее невыгодном положении, так как даже попадание на процессор не гарантирует выполнение процесса до конца

### HRRN (Highest Response Ratio Next)
Для выполнения из очереди готовых процессов выбирается тот, который имеет наибольшее значение R, где значение R вычисляется по формуле: `R = (w + s) / s`.

Здесь w - время, которое процесс находится в очереди, s - время обслуживания.

Короткие процессы:
- Имеют меньшую эффективность относительно SPN и SRT

Длинные процессы:
- Обрабатываются более справедливо, так как во время ожидания увеличивается их приоритет
- При попадании на процессор процесс уже не вытеснить, а значит он выполнится полностью