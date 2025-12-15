# psp-pandora-battery-for-arduino BaryonSweeper
<body>
  <p align="center">
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/photo%20examples/1.jpg" width=30% height=auto>
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/photo%20examples/2.jpg" width=30% height=auto>
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/photo%20examples/3.jpg" width=23.5% height=auto>
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/photo%20examples/4.jpg" width=23.5% height=auto>
  </p>

<h3><strong>RU</strong></h3>

<h3><strong>Описание</strong></h3>
<p>Эмулятор сервисной батареи пандоры для восстановления из кирпича и прошивки PSP. Проект разработан на базе Ардуино. В качестве контроллера подойдёт любая Атмега 328.</p>
<p><span style="color: #00bc03;">ПОДДЕРЖИВАЮТСЯ ВСЕ МОДЕЛИ 1000-3000, STREET и GO!</span></p>
<p>Левый переключатель отвечает за включение аккумулятор. Второй за переключение режима (обычный/сервисный). Кнопка нужна для перезагрузки микроконтроллера. При включении или перезагрузке на кнопку пандора проинформирует о типе выбранного режима в зависимости от положения переключателя. Если светодиод мигает с периодами раз в секунду, то включен сервисный режим, если горит не прерывно, то работает обычный режим. При низком уровне заряда светодиод начнёт быстро мигать.</p>
<p>Все ключи и прошивка были обновлены на основе этого проекта <a href="https://github.com/khubik2/pysweeper" target="_blank" rel="noopener" title="pysweeper">pysweeper</a>. Там же можно следить за обновлениями, которые будут появляться и в этом проекте.</p>

<h3><strong>Сборка</strong></h3>
<p>Можете выбрать люой понравившийся вариант платы. Срузу скажу, что установка кварца не обязательна, так как микроконтроллер может работать от внутреннего генератора. Для этого просто можете не ставить детали, помеченные на схеме звёздочкой.</p>

<h3>Прошивка микроконтроллера</h3>
<p>Для программирования микроконтроллера необходимо:</p>
<ol>
<li>Скачать среду программирования <a href="https://www.arduino.cc/" target="_blank" rel="noopener" title="arduino">Arduino</a></li>
<li>Устаноить дополнение для менеджера плат <a href="https://github.com/MCUdude/MiniCore" target="_blank" rel="noopener" title="MiniCore">MiniCore</a></li>
<li>Устаноить библиотеки <a href="https://github.com/ljbeng/SoftwareSerialParity" target="_blank" rel="noopener" title="SoftwareSerialParity">SoftwareSerialParity</a> и <a href="https://www.arduino.cc/reference/en/libraries/aeslib/" target="_blank" rel="noopener" title="AES">AES</a></li>
<li>Микроконтроллер должен быть предварительно прошит через программатор как Atmega 328 из minicore. В настройках вам стоит выбрать частоту работы 8 мгц от внешнего генератор (если вы хотите впаять кварц), либо от внутреннего (если вы отказываетесь от его установки).</li>
<li>Далее прошивать и обновлять прошивку можно скетчем через любой usb to ttl преобразователь, соединив с пинами (rx, tx, rst, gnd) на плате, либо вставить микроконтроллер в готовую плату arduino uno для прошивки. Так же можно использовать программатор usb asp.</li>
</ol>

<p align="center">
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/setting%20arduino%20328.png" width=30% height=auto>
  </p>

<p>
Почему не используется кварц по умолчанию на 16 мгц? Всё просто. На пониженной частототе микроконтроллер может работать от меньшего питания более стабильно, так же он потребляет меньше энергии, что хорошо скажется на экономии заряда аккумулятора.
</p>

<h3>Прошивка для PSP</h3>
<p>
<a href="https://www.pspx.ru/forum/showthread.php?t=114800" target="_blank" rel="noopener" title="6.61 DC-ARK">6.61 DC-ARK (не всегда грузится с первого раза)</a><br />
<a href="https://www.pspx.ru/forum/showthread.php?t=114382" target="_blank" rel="noopener" title="6.61 DC-ARK">6.61 aesright (всегда грузится нормально, рекомендуется)</a>
</p>

<h3><strong>Взаимозаменяемость микросхем</strong></h3>
<p>cd4011 -> к561ла7<br />
74hc00 -> кр1554ла3<br /></p>

<h3><strong>Использование</strong></h3>
<ol>
<li>Вставьте в приставку флешку с подготовленной прошивкой</li>
<li>Включите аккумулятор в сервисном режиме (светодиод должен медленно мигать)</li>
<li>Выключите полностью приставку, если она была включена ранее или находится в спящем режиме</li>
<li>Далее действуйте согласно вашей модели<br />
PSP 1000-3000: вставьте в приставку вместо аккумулятора, прошивка с флешки заведётся автоматически<br />
PSP GO: подключите кабель в приставку, прошивка заведётся автоматически (сама приставка должна быть заряжена)<br />
PSP STREET: подключите кабель в приставку, зажмите комбинацию клавиш "Влево", "круг", "левый триггер", "правый триггер", затем, не отпуская кнопки, нажмите включение, прошивка с флешки заведётся (сама приставка должна быть заряжена)<br /><br /></li>
</ol>
Прошивка иногда может загрузиться не сразу, а через несколько секунд. Просто подождите.<br />
Зарядка данного устройства производится на моделях 1000-3000. Для этого необходимо включить аккумулятор в любой из режимов, затем вставить в консоль и подключить зарядку, при этом саму PSP включать не нужно.<br /></p>
  
<h3>Решение проблем:</h3>
<ol>
<li>Не срабатывает обмен (не мигают светодиды) при подключении к PSP, всё собрано правильно, замыканий нет<br />
<strong>Решение</strong>: возможно у вас недостаточное или большое падение напряжения на микросхеме cd4011/74hc00. Попробуйте вместо R9 (который стоит под микросхемой на большой плате) разные резисторы в диапозоне с 200ом до 1000ом. Подбирается методом пробы. К примеру, у меня на smd плате зраработало с резистором 220ом, на большой плате 470ом, на другой большой плате с другой аналогичной микросхемой подошёл 680ом.</li>
<li>На приставке мигает светодиод чтения данных, прошивка не заводится<br />
<strong>Решение</strong>: возможо у вас медленная флешка. Пробуйте повторить запуск, с какой то попытки прошивка заведётся. Либо используйте другую более быструю карту памяти.</li>
<li>При подключении к приставке помигали светодиоды на аккумуляторе, но ничего не происходит<br />
<strong>Решение</strong>: тут может два варианта решения<br />
А) приставка не может считать прошивку с флешки. Скорее всего вы неправльно подготовили карту памяти с прошивкой, сделайте это повторно. Если и дальше ничего не происходит, попробуйте другую флешку.<br />
Б) Не хватает питания, попробуйте сперва подключить зарядку, а потом вставить аккумулятор. Такое явление было замеченно на 1000 fat моделях</li>
<li>Не верно определяется заряд аккумулятора<br />
<strong>Решение</strong>: в новой версии v4 был изменнён номинал резистора с 22к на 30к. Возможно, вы этого не заметили.</li>
</ol>

<p><strong>Источник</strong> https://www.pspx.ru/forum/showpost.php?p=1229948</p>

<h3><strong>EN</strong></h3>

<h3><strong>Description</strong></h3>
<p>Pandora service battery emulator for brick recovery and PSP firmware. The project is based on Arduino. Any Atmega 328 will do as a controller.</p>
<p><span style="color: #00bc03;">ALL 1000-3000, STREET and GO MODELS ARE SUPPORTED!</span></p>
<p>The left switch is responsible for turning on the battery. The second one is for switching the mode (normal/service). The button is needed to reboot the microcontroller. When turning on or rebooting with the button, Pandora will inform you about the type of the selected mode depending on the switch position. If the LED blinks with periods of once per second, then the service mode is on, if it lights up continuously, then the normal mode is working. When the battery level is low, the LED will start blinking quickly.</p>
<p>All keys and firmware have been updated based on this project <a href="https://github.com/khubik2/pysweeper" target="_blank" rel="noopener" title="pysweeper">pysweeper</a>. There you can also follow the updates that will appear in this project.</p>

<h3><strong>Assembly</strong></h3>
<p>You can choose any board design you like. I'll say right away that installing a quartz crystal is not necessary, as the microcontroller can be powered by its internal oscillator. To do this, simply omit the parts marked with an asterisk on the schematic.</p>

<h3>Microcontroller firmware</h3>
<p>To program the microcontroller you need:</p>
<ol>
<li>Download the <a href="https://www.arduino.cc/" target="_blank" rel="noopener" title="arduino">Arduino programming environment</a></li>
<li>Install the add-on for the board manager <a href="https://github.com/MCUdude/MiniCore" target="_blank" rel="noopener" title="MiniCore">MiniCore</a></li>
<li>Install the libraries <a href="https://github.com/ljbeng/SoftwareSerialParity" target="_blank" rel="noopener" title="SoftwareSerialParity">SoftwareSerialParity</a> and <a href="https://www.arduino.cc/reference/en/libraries/aeslib/" target="_blank" rel="noopener" title="AES">AES</a></li>
<li>The microcontroller must be pre-programmed as an Atmega 328 from minicore using a programmer. In the settings, you should select an operating frequency of 8 MHz from an external oscillator (if you want to solder in a quartz crystal) or from an internal one (if you refuse to install one).</li>
<li>Then you can flash and update the firmware using a sketch via any USB to TTL converter, connecting it to the pins (rx, tx, rst, gnd) on the board, or insert the microcontroller into a ready-made Arduino Uno board for flashing. You can also use the usb asp programmer.</li>
</ol>

<p align="center">
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/refs/heads/main/setting%20arduino%20328.png" width=30% height=auto>
  </p>

<p>
Why isn't the default 16 MHz crystal used? It's simple. At a lower frequency, the microcontroller can operate more reliably from a lower power supply, and it also consumes less power, which will have a positive impact on battery life.
</p>

<h3>Firmware for PSP</h3> 
<p>
<a href="https://www.pspx.ru/forum/showthread.php?t=114800" target="_blank" rel="noopener" title="6.61 DC -ARK">6.61 DC-ARK (doesn't always load the first time)</a><br /> 
<a href="https://www.pspx.ru/forum/showthread.php?t=114382" target="_blank" rel="noopener" title="6.61 DC-ARK">6.61 aesright (always loads normally, recommended)</a> 
</p>

<h3><strong>Interchangeability of chips</strong></h3>
<p>cd4011 -> k561la7<br />
74hc00 -> kr1554la3<br /></p>

<h3><strong>Usage</strong></h3>
<ol>
<li>Insert the flash drive with the prepared firmware</li>
<li>Turn on the battery in service mode (the LED should blink slowly)</li>
<li>Turn off the console completely if it was turned on earlier or is in sleep mode</li>
<li>Then proceed according to your model<br />
PSP 1000-3000: insert it into the console instead of the battery, the firmware from the flash drive will start automatically<br />
PSP GO: connect the cable to the console, the firmware will start automatically (the console itself must be charged)<br />
PSP STREET: connect the cable to the console, hold down the key combination "Left", "circle", "left trigger", "right trigger", then, without releasing the buttons, press the power button, the firmware from the flash drive will start (the console itself must be charged)<br /><br /></li>
</ol>
The firmware may sometimes not load immediately, but after a few seconds. Just wait.<br />
This device is charged on models 1000-3000. To do this, turn on the battery in any of the modes, then insert it into the console and connect the charger, while the PSP itself does not need to be turned on.<br /></p>

<h3>Troubleshooting:</h3>
<ol>
<li>The exchange does not work (the LEDs do not blink) when connected to the PSP, everything is assembled correctly, there are no short circuits<br />
<strong>Solution</strong>: You may have insufficient or excessive voltage drop on the CD4011/74HC00 chip. Try different resistors ranging from 200ohms to1000 ohms instead of R9 (which is located under the chip on the larger board). The correct value is determined by trial and error. For example, a 220ohm resistor worked for me on an SMD board, a 470ohm resistor on a larger board, and a 680ohm resistor worked on another larger board with a different, similar chip.</li>
<li>The data reading LED on the console blinks, the firmware does not start<br />
<strong>Solution</strong>: perhaps you have a slow flash drive. Try to restart, the firmware will start after some attempt. Or use another faster memory card.</li>
<li>When connected to the console, the LEDs on the battery blinked, but nothing happens<br />
<strong>Solution</strong>: there may be two possible solutions<br />
A) the console cannot read the firmware from the flash drive. Most likely, you incorrectly prepared the memory card with the firmware, do it again. If nothing happens, try another flash drive.<br />
B) There is not enough power, try connecting the charger first, and then insert the battery. This phenomenon was noticed on 1000 fat models</li>
<li>Battery charge is not being detected correctly<br />
<strong>Solution</strong>: In the new v4 version, the resistor value was changed from 22k to 30k. You may not have noticed this.</li>
</ol>

<p><strong>Source</strong> https://www.pspx.ru/forum/showpost.php?p=1229948</p>

 </body>
