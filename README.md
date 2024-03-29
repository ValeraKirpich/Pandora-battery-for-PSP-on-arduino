# psp-pandora-battery-for-arduino BaryonSweeper

Эмулятор сервисной батареи пандоры, написаный под ардуино. В качестве контроллера подойдёт Атмега 168/328. 

Левый переключатель отвечает за включение аккумулятор. Второй за переключение режима (обычный/сервисный). Кнопка нужна для перезагрузки микроконтроллера. При включении или перезагрузке на кнопку пандора проинформирует о типе выбранного режима в зависимости от положения переключателя. Если светодиод мигает с периодами раз в секунду, то включен сервисный режим, если горит не прерывно, то работает обычный режим. При низком уровне заряда светодиод начнёт быстро мигать.

ПОДДЕРЖИВАЮТСЯ ВСЕ МОДЕЛИ!

Все ключи и прошивка были обновлены на основе этого проекта https://github.com/khubik2/pysweeper. Там же можно следить за обновлениями, которые будут появляться и в этом проекте.

Для изготовления понадоятся следующие детали:

1) Микроконтролеер atmega 168 или 328 в dip исполнении
2) Три светодиода 3мм
3) микросхема К561ЛА7 или любой аналог
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
