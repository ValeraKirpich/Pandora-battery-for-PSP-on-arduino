# psp-pandora-battery-for-arduino BaryonSweeper

RU

Эмулятор сервисной батареи пандоры, написаный под ардуино. В качестве контроллера подойдёт Атмега 168/328. 

Левый переключатель отвечает за включение аккумулятор. Второй за переключение режима (обычный/сервисный). Кнопка нужна для перезагрузки микроконтроллера. При включении или перезагрузке на кнопку пандора проинформирует о типе выбранного режима в зависимости от положения переключателя. Если светодиод мигает с периодами раз в секунду, то включен сервисный режим, если горит не прерывно, то работает обычный режим. При низком уровне заряда светодиод начнёт быстро мигать.

ПОДДЕРЖИВАЮТСЯ ВСЕ МОДЕЛИ!

Все ключи и прошивка были обновлены на основе этого проекта https://github.com/khubik2/pysweeper. Там же можно следить за обновлениями, которые будут появляться и в этом проекте.

Для изготовления понадоятся следующие детали:

1) Микроконтролеер atmega 168 или 328 в dip исполнении
2) Три светодиода 3мм
3) микросхема К561ЛА7 или CD4011
4) Одна кнопка на 4 ноги
5) Два dip переключателя
6) Кварц на 16 Mhz
7) Два конденстора на 18-22pF
8) Четрые резистора на 10 кОм
9) Три резистора на 150 ом
10) Один резистор на 22 кОм
11) Один резистор на 200 ом
12) Штырёвый разъйм на 1x4 пина
13) Разъём как на родном psp АКБ
14) Любой акб от старого телефона

Для программирования необходимо сделать следующие действия:
1) В микроконтроллер нужно будет зашить ардуиновкий бутлоадер (если у вас чистый мк), либо взять готовую arduino uno с микроконтроллером в dip исполнении (так будет проще, так как не придётся разбираться с прошивкой бутлоадера)
2) Устаноить в ардуино библиотеку SoftwareSerialParity https://github.com/ljbeng/SoftwareSerialParity
3) Далее прошивать МК скетчем можно через любой usb to ttl преобразователь, соединив с пинами (rx, tx, rst, gnd) на плате, либо через саму ардуино

Источник https://www.pspx.ru/forum/showpost.php?p=1229948

EN

Pandora service battery emulator written for Arduino. Atmega 168/328 is suitable as a controller.

The left switch is responsible for turning on the battery. The second is for switching mode (normal/service). The button is needed to reboot the microcontroller. When you turn on or reboot the button, Pandora will inform you about the type of mode selected depending on the position of the switch. If the LED flashes once per second, then the service mode is on; if it lights up continuously, then the normal mode is operating. When the battery level is low, the LED will flash quickly.

ALL MODELS SUPPORTED!

All keys and firmware have been updated based on this project https://github.com/khubik2/pysweeper. There you can also follow the updates that will appear in this project.

For manufacturing you will need the following parts:

1) Microcontroller atmega 168 or 328 in dip version
2) Three 3mm LEDs
3) K561LA7 microcircuit or CD4011
4) One button for 4 legs
5) Two dip switches
6) Quartz at 16 Mhz
7) Two capacitors at 18-22pF
8) Four 10 kOhm resistors
9) Three 150 ohm resistors
10) One 22 kOhm resistor
11) One 200 ohm resistor
12) 1x4 pin connector
13) The connector is like on a native PSP battery
14) Any battery from an old phone

To program you need to do the following:
1) You will need to install an Arduino bootloader into the microcontroller (if you have a blank microcontroller), or take a ready-made arduino uno with a dip microcontroller (this will be easier, since you won’t have to deal with the bootloader firmware)
2) Install the SoftwareSerialParity library in Arduino https://github.com/ljbeng/SoftwareSerialParity
3) Next, you can flash the MK with a sketch through any usb to ttl converter, connecting it to the pins (rx, tx, rst, gnd) on the board, or through the arduino itself

Source https://www.pspx.ru/forum/showpost.php?p=1229948
