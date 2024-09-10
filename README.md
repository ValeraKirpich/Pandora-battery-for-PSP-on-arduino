# psp-pandora-battery-for-arduino BaryonSweeper
<body>
  <p align="center">
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/main/IMG_2024-08-01-13-09-17-202.jpg" width=30% height=auto>
    <img src="https://raw.githubusercontent.com/ValeraKirpich/Pandora-battery-for-PSP-on-arduino/main/IMG_2024-08-01-13-10-03-141.jpg" width=30% height=auto>
  </p>

<h3><strong>RU</strong></h3>

<h3><strong>Описание</strong></h3>
<p>Эмулятор сервисной батареи пандоры для восстановления из кирпича и прошивки PSP. Проект разработан на базе Ардуино. В качестве контроллера подойдёт Атмега 168/328.</p>
<p><span style="color: #00bc03;">ПОДДЕРЖИВАЮТСЯ ВСЕ МОДЕЛИ 1000-3000, STREET и GO!</span></p>
<p>Левый переключатель отвечает за включение аккумулятор. Второй за переключение режима (обычный/сервисный). Кнопка нужна для перезагрузки микроконтроллера. При включении или перезагрузке на кнопку пандора проинформирует о типе выбранного режима в зависимости от положения переключателя. Если светодиод мигает с периодами раз в секунду, то включен сервисный режим, если горит не прерывно, то работает обычный режим. При низком уровне заряда светодиод начнёт быстро мигать.</p>
<p>Все ключи и прошивка были обновлены на основе этого проекта <a href="https://github.com/khubik2/pysweeper" target="_blank" rel="noopener" title="pysweeper">pysweeper</a>. Там же можно следить за обновлениями, которые будут появляться и в этом проекте.</p>

<h3>Прошивка микроконтроллера</h3>
<p>Для программирования микроконтроллера необходимо:</p>
<ol>
<li>Скачать среду программирования <a href="https://www.arduino.cc/" target="_blank" rel="noopener" title="arduino">Arduino</a></li>
<li>Устаноить библиотеки <a href="https://github.com/ljbeng/SoftwareSerialParity" target="_blank" rel="noopener" title="SoftwareSerialParity">SoftwareSerialParity</a> и <a href="https://www.arduino.cc/reference/en/libraries/aeslib/" target="_blank" rel="noopener" title="AES">AES</a></li>
<li>Если вы работаете с чистым микроконтроллером, то предварительно в него нужно зашить bootloader от Arduino uno</li>
<li>Далее прошивать и обновлять прошивку можно скетчем через любой usb to ttl преобразователь, соединив с пинами (rx, tx, rst, gnd) на плате, либо вставить микроконтроллер в готовую плату arduino uno для прошивки. Так же можно использовать программатор usb asp.</li>
</ol>
<h3>Прошивка для PSP</h3>
<p>Универсальную прошивку для всех PSP можете скачать тут <a href="https://www.pspx.ru/forum/showthread.php?t=114800" target="_blank" rel="noopener" title="6.61 DC-ARK">6.61 DC-ARK</a></p>

<h3><strong>Взаимозаменяемость микросхем</strong></h3>
<p>Atmega 328 или 168<br />
cd4011 -> к561ла7<br />
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
Зарядка данного устройства производится на моделях 1000-3000. Для этого необходимо включить аккумулятор в любой из режимов, затем вставить в консоль и подключить зарядку, при этом саму PSP включать не нужно.<br /></p>
  
<h3>Решение проблем:</h3>
<ol>
<li>Не срабатывает обмен (не мигают светодиды) при подключении к PSP, всё собрано правильно, замыканий нет<br />
<strong>Решение</strong>: возможно у вас недостаточное падение напряжения на микросхеме cd4011/74hc00. Попробуйте увеличить номинал резистора R9 (который стоит под микросхемой) с 470 ом до 610-1000 ом (подбирается методом пробы).</li>
<li>На приставке мигает светодиод чтения данных, прошивка не заводится<br />
<strong>Решение</strong>: возможо у вас медленная флешка. Пробуйте повторить запуск, с какой то попытки прошивка заведётся. Либо используйте другую более быструю карту памяти.</li>
</ol>

<p><strong>Источник</strong> https://www.pspx.ru/forum/showpost.php?p=1229948</p>

<h3><strong>EN</strong></h3>
<h3><strong>Description</strong></h3>
<p>Pandora service battery emulator for brick recovery and PSP firmware. The project is based on Arduino. Atmega 168/328 is suitable as a controller.</p>
<p><span style="color: #00bc03;">ALL MODELS 1000-3000, STREET and GO ARE SUPPORTED!</span></p>
<p>The left switch is responsible for turning on the battery. The second one is for switching the mode (normal/service). The button is needed to reboot the microcontroller. When turning on or rebooting with the button, Pandora will inform you about the type of the selected mode depending on the switch position. If the LED blinks with periods of once per second, then the service mode is on, if it lights up continuously, then the normal mode is working. When the battery level is low, the LED will start blinking quickly.</p>
<p>All keys and firmware have been updated based on this project <a href="https://github.com/khubik2/pysweeper" target="_blank" rel="noopener" title="pysweeper">pysweeper</a>. There you can also follow the updates that will appear in this project.</p>
<h3>Microcontroller firmware</h3>
<p>To program the microcontroller you need:</p>
<ol>
<li>Download the programming environment <a href="https://www.arduino.cc/" target="_blank" rel="noopener" title="arduino">Arduino</a></li>
<li>Install the libraries <a href="https://github.com/ljbeng/SoftwareSerialParity" target="_blank" rel="noopener" title="SoftwareSerialParity">SoftwareSerialParity</a> and <a href="https://www.arduino.cc/reference/en/libraries/aeslib/" target="_blank" rel="noopener" title="AES">AES</a></li>
<li>If you are working with a clean microcontroller, you must first flash the bootloader from Arduino Uno into it</li>
<li>Then you can flash and update the firmware using a sketch via any USB to TTL converter, connecting it to the pins (rx, tx, rst, gnd) on the board, or insert the microcontroller into a ready-made Arduino Uno board for flashing. You can also use the usb asp programmer.</li>
</ol>
<h3>Firmware for PSP</h3>
<p>You can download the universal firmware for all PSPs here <a href="https://www.pspx.ru/forum/showthread.php?t=114800" target="_blank" rel="noopener" title="6.61 DC-ARK">6.61 DC-ARK</a></p>

<h3><strong>Interchangeability of microcircuits</strong></h3> 
<p>Atmega 328 or 168<br /> 
cd4011 -> k561la7<br /> 
74hc00 -> kr1554la3<br /></p>

<h3><strong>Usage</strong></h3>
<ol>
<li>Insert the flash drive with the prepared firmware into the console</li>
<li>Turn on the battery in service mode (the LED should blink slowly)</li>
<li>Turn off the console completely if it was turned on earlier or is in sleep mode</li>
<li>Then proceed according to your model<br />
PSP 1000-3000: insert into the console instead of the battery, the firmware from the flash drive will start automatically<br />
PSP GO: connect the cable to the console, the firmware will start automatically (the console itself must be charged)<br />
PSP STREET: connect the cable to the console, hold down the key combination "Left", "circle", "left trigger", "right trigger", then, without releasing the button, press the power button, the firmware from the flash drive will start (the console itself must be charged)<br /><br /></li>
</ol>
This device is charged on models 1000-3000. To do this, you need to turn on the battery in any of the modes, then insert it into the console and connect the charger, while the PSP itself does not need to be turned on.<br /></p>

<h3>Troubleshooting:</h3>
<ol>
<li>The exchange does not work (LEDs do not blink) when connected to the PSP, everything is assembled correctly, there are no short circuits<br />
<strong>Solution</strong>: you may have insufficient voltage drop on the cd4011/74hc00 chip. Try increasing the value of the resistor R9 (which is located under the chip) from 470 ohms to 610-1000 ohms (selected by trial and error).</li>
<li>The data reading LED on the console blinks, the firmware does not start<br />
<strong>Solution</strong>: you may have a slow flash drive. Try to restart the firmware, it will start after some attempt. Or use another faster memory card.</li>
</ol>

<p><strong>Source</strong> https://www.pspx.ru/forum/showpost.php?p=1229948</p>

 </body>
