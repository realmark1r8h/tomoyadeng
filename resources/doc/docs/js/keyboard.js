(function() {
	methodArr = [];
	settingsArr = [];
	initApi('SN', 'sayString', '', '发送字符串', 'str, String, 要发送的字符串');
	initApi('SN', 'keyPress', '', '单击按键,说明：输入参数个数不定，单个参数可以是一个字符串，也可以是一个特殊按键', 'str, String, 要发送的按键');
	initApi('SN', 'keyDown', '', '按下按键,说明：输入参数个数不定，单个参数可以是一个字符串，也可以是一个特殊按键', 'str, String, 要按下的按键');
	initApi('SN', 'keyUp', '', '弹起按键,说明：输入参数个数不定，单个参数可以是一个字符串，也可以是一个特殊按键', 'str, String, 要弹起的按键');
	initApi('SS', 'waitKey', '', '等待按任意键');
	initApi('SS', 'getLastKey', '', '检测上次按键');

	initSettings('VK_CONTROL', 'Integer', 'CONTROL');
	initSettings('VK_SHIFT', 'Integer', 'SHIFT');
	initSettings('VK_MENU', 'Integer', 'ALT');
	initSettings('VK_F1', 'Integer', 'F1');
	initSettings('VK_F2', 'Integer', 'F2');
	initSettings('VK_F3', 'Integer', 'F3');
	initSettings('VK_F4', 'Integer', 'F4');
	initSettings('VK_F5', 'Integer', 'F5');
	initSettings('VK_F6', 'Integer', 'F6');
	initSettings('VK_F7', 'Integer', 'F7');
	initSettings('VK_F8', 'Integer', 'F8');
	initSettings('VK_F9', 'Integer', 'F9');
	initSettings('VK_F10', 'Integer', 'F10');
	initSettings('VK_F11', 'Integer', 'F11');
	initSettings('VK_F12', 'Integer', 'F12');
	initSettings('VK_UP', 'Integer', 'UP');
	initSettings('VK_DOWN', 'Integer', 'DOWN');
	initSettings('VK_LEFT', 'Integer', 'LEFT');
	initSettings('VK_RIGHT', 'Integer', 'RIGHT');
	initSettings('VK_RETURN', 'Integer', 'RETURN');
	initSettings('VK_ESCAPE', 'Integer', 'ESCAPE');
	initSettings('VK_BACK', 'Integer', 'BACK');
	initSettings('VK_HOME', 'Integer', 'HOME');
	initSettings('VK_DELETE', 'Integer', 'DELETE');
	initSettings('VK_INSERT', 'Integer', 'INSERT');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		include('keyboard', 'mouse');

		console.dir(keyboard);

		$('#sayString').on('click', function() {
//			mouse.click(900, 500);
			mouse.moveR(0, -60);
			mouse.click();
			keyboard.sayString(`msdn对此方式的说明为：input_keyboard支持非键盘的输入方式，
		    	例如手写识别或语音识别，通过KEYEVENTF_UNICODE标识，这些方式与键盘（文本）输入别无二致。
		    	如果指定了KEYEVENTF_UNICODE，SendInput发送一个WM_KEYDOWN或WM_KEYUP消息给活动窗口的线程消息队列，
		    	消息的wParam参数为VK_PACKET。GetMessage或PeedMessage一旦获得此消息，
		    	就把它传递给TranslateMessage，TranslateMessage根据wScan中指定的Unicode字符产生一个WM_CHAR消息。
		    	若窗口是ANSI窗口，则Unicode字符会自动转换为相应的ANSI字符。`);

		});
		$('#keyPress').on('click', function() {
			mouse.moveR(0, -60);
			mouse.click();
			keyboard.keyPress(keyboard.VK_MENU, keyboard.VK_F4);

		});
		$('#keyDown').on('click', function() {
			mouse.moveR(0, -60);
			mouse.click();
			keyboard.keyDown('1');

		});
		$('#keyUp').on('click', function() {
			mouse.moveR(0, -60);
			mouse.click();
			keyboard.keyUp('1');

		});
	})
})();