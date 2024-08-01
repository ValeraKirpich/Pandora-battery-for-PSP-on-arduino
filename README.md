# psp-pandora-battery-for-arduino BaryonSweeper
<body>
  <p align="center">
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/main/IMG_2024-08-01-13-10-03-141.jpg" width=30% height=auto>
  </p>
 </body>

RU

ДОБАВЛЕНА НОВАЯ БОЛЕЕ КОМПАКТНАЯ ВЕРСИЯ ПЛАТЫ. ВСЁ НАХОДИТСЯ В ОДНОМ lay ФАЙЛЕ. НОВАЯ ВЕРСИЯ ПЛАТЫ ПОКА НЕ ТЕСТИРОВАЛОСЬ ПОЛНОСТЬЮ. ДОБАВЛЕНА ПОДДЕРЖКА PSP GO.

Эмулятор сервисной батареи пандоры, написаный под ардуино. В качестве контроллера подойдёт Атмега 168/328. 

Левый переключатель отвечает за включение аккумулятор. Второй за переключение режима (обычный/сервисный). Кнопка нужна для перезагрузки микроконтроллера. При включении или перезагрузке на кнопку пандора проинформирует о типе выбранного режима в зависимости от положения переключателя. Если светодиод мигает с периодами раз в секунду, то включен сервисный режим, если горит не прерывно, то работает обычный режим. При низком уровне заряда светодиод начнёт быстро мигать.

ПОДДЕРЖИВАЮТСЯ ВСЕ МОДЕЛИ 1000-3000, STREET и GO!. 

Все ключи и прошивка были обновлены на основе этого проекта https://github.com/khubik2/pysweeper. Там же можно следить за обновлениями, которые будут появляться и в этом проекте.

Для программирования необходимо сделать следующие действия:
1) В микроконтроллер нужно будет зашить ардуиновкий бутлоадер (если у вас чистый мк), либо взять готовую arduino uno с микроконтроллером в dip исполнении (так будет проще, так как не придётся разбираться с прошивкой бутлоадера)
2) Устаноить в ардуино библиотеки SoftwareSerialParity https://github.com/ljbeng/SoftwareSerialParity и AES https://www.arduino.cc/reference/en/libraries/aeslib/
3) Далее прошивать МК скетчем можно через любой usb to ttl преобразователь, соединив с пинами (rx, tx, rst, gnd) на плате, либо через саму ардуино

Источник https://www.pspx.ru/forum/showpost.php?p=1229948

EN

A NEW MORE COMPACT VERSION OF THE BOARD ADDED. EVERYTHING IS IN ONE lay FILE. THE NEW VERSION OF THE BOARD HAS NOT BEEN COMPLETELY TESTED YET. PSP GO SUPPORT HAS BEEN ADDED.

Pandora service battery emulator written for Arduino. Atmega 168/328 is suitable as a controller.

The left switch is responsible for turning on the battery. The second is for switching mode (normal/service). The button is needed to reboot the microcontroller. When you turn on or reboot the button, Pandora will inform you about the type of mode selected depending on the position of the switch. If the LED flashes once per second, then the service mode is on; if it lights up continuously, then the normal mode is operating. When the battery level is low, the LED will flash quickly.

ALL MODELS SUPPORTED 1000-3000, STREET AND GO!

All keys and firmware have been updated based on this project https://github.com/khubik2/pysweeper. There you can also follow the updates that will appear in this project.

To program you need to do the following:
1) You will need to install an Arduino bootloader into the microcontroller (if you have a blank microcontroller), or take a ready-made arduino uno with a dip microcontroller (this will be easier, since you won’t have to deal with the bootloader firmware)
2) Install library in Arduino SoftwareSerialParity https://github.com/ljbeng/SoftwareSerialParity and AES https://www.arduino.cc/reference/en/libraries/aeslib/
3) Next, you can flash the MK with a sketch through any usb to ttl converter, connecting it to the pins (rx, tx, rst, gnd) on the board, or through the arduino itself

Source https://www.pspx.ru/forum/showpost.php?p=1229948
