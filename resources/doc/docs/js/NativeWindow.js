(function() {
	methodArr = [];
	settingsArr = [];
	eventArr = [];

 
	initApi('MS', 'getName', 'String', '获取窗口名称');
	initApi('MN', 'setName', '', '设置窗口名称', 'name, String, BrowserWindow 名称');

	initApi('MN', 'close', '', '关闭窗口');
	initApi('MN', 'focus', '', '使窗口获得焦点');
	initApi('MS', 'isFocused', 'Boolean', '判断窗口是否获得焦点');
	initApi('MN', 'show', '', '显示窗口');
	initApi('MN', 'showInactive', '', '显示窗口');
	initApi('MN', 'hide', '', '隐藏窗口');
	initApi('MS', 'isVisible', 'Boolean', '判断窗口是否可见');
	initApi('MN', 'maximize', '', '最大化窗口');
	initApi('MN', 'unmaximize', '', '还原窗口，跟restore相同');
	initApi('MS', 'isMaximized', 'Boolean', '判断窗口是否最大化');
	initApi('MN', 'minimize', '', '最小化窗口');
	initApi('MN', 'restore', '', '还原窗口');
	initApi('MS', 'isMinimized', 'Boolean', '判断窗口是否最小化');
	initApi('MN', 'setFullScreen', '', '全屏窗口');
	initApi('MS', 'isFullScreen', 'Boolean', '判断窗口是否处理全屏状态');
	initApi('MN', 'setBounds', '', '设置窗口位置大小', 'option, Object, 例{x:0, y:0, width: 1000, height:500}');
	initApi('MS', 'getBounds', 'Object', '获取窗口位置大小，返回一个对象{x:0, y:0, width: 1000, height:500}');
	initApi('MN', 'setSize', '', '设置窗口宽高', 'width, Integer, 宽', 'height, Integer, 高');
	initApi('MS', 'getSize', 'Object', '获取窗口宽高，返回一个对象{width:100, height:100}');
	initApi('MN', 'setMinimumSize', '', '设置窗口最小宽高', 'width, Integer, 宽', 'height, Integer, 高');
	initApi('MS', 'getMinimumSize', 'Object', '获取窗口最小宽高，返回 一个对象{width:300, height:100}');
	initApi('MN', 'setMaximumSize', '', '设置窗口最大宽高', 'width, Integer, 宽', 'height, Integer, 高');
	initApi('MS', 'getMaximumSize', 'Object', '获取窗口最大宽高，返回 一个对象{width:300, height:100}');
	initApi('MN', 'setResizable', '', '设置窗口是否可以改变大小', 'resizble, Boolean');
	initApi('MS', 'isResizable', 'Boolean', '判断窗口是否可以改变大小');
	initApi('MN', 'setMovable', '', '设置窗口是否可移动', 'moveable, Boolean');
	initApi('MS', 'isMovable', 'Boolean', '判断窗口是否可移动');

	initApi('MN', 'setMinimizable', '', '设置窗口是否可最小化', 'minimizable, Boolean');
	initApi('MS', 'isMinimizable', 'Boolean', '判断窗口是否可以最小化');
	initApi('MN', 'setMaximizable', '', '设置窗口是否可以最大化', 'maximizable, Boolean');
	initApi('MS', 'isMaximizable', 'Boolean', '判断窗口是否可以最大化');
	initApi('MN', 'setFullScreenable', '', '设置窗口是否可以全屏', 'fullscreenable, Boolean');
	initApi('MS', 'isFullScreenable', 'Boolean', '判断窗口是否可以全屏');
	initApi('MN', 'setClosable', '', '设置窗口是否可以关闭', 'closable, Boolean');
	initApi('MS', 'isClosable', 'Boolean', '判断窗口是否可以关闭');
	initApi('MN', 'setAlwaysOnTop', '', '设置窗口是否置顶', 'topmost, Boolean, 是否置顶');
	initApi('MS', 'isAlwaysOnTop', 'Boolean', '判断窗口是否置顶显示');
	initApi('MN', 'center', '', '设置窗口居中显示');
	initApi('MN', 'setPosition', '', '移动窗口到指定位置', 'x, Integer, x坐标', 'y, Integer, y 坐标');
	initApi('MS', 'getPosition', 'Object', '获取窗口在屏幕中的位置，同getBounds');
	initApi('MN', 'setTitle', '', '设置窗口标题', 'title, String, 窗口标题');
	initApi('MS', 'getTitle', 'String', '获取窗口标题');
	initApi('MN', 'flashFrame', '', '闪烁窗口');
	initApi('MN', 'topmost', '', '置顶窗口， 同setAlwaysOnTop');
	initApi('MS', 'isTopmost', '', '判断窗口是否置顶，同isAlwaysOnTop');
 
	initApi('MN', 'setHasShadow', '', '设置是否显示窗口阴影', 'hasShadow, Boolean, 是否显示');
	initApi('MS', 'hasShadow', 'Boolean', '判断是否显示窗口阴影');
 

	initApi('MN', 'toggleFullScreen', '', '全屏/退出全屏');
	initApi('MN', 'toggleVisible', '', '显示/隐藏');
	initApi('MN', 'setIcon', '', '设置窗口图标');
 
	// initSettings
	// NativeWindow Settings
	initSettings('id', 'String', '窗口ID, 默认"0"');
	initSettings('name', 'String', '窗口名称');
	initSettings('parent', 'String', '父窗口ID, 默认"0"');
	initSettings('title', 'String', '窗口标题名');
	initSettings('icon', 'String', '窗口图标， 默认""');
	initSettings('titleBar', 'Boolean', '是否显示标题栏, 默认false');
	initSettings('sizebox', 'String', '可拖动改变窗口大小的边框范围, 默认"2,2,2,2"');
	initSettings('roundcorner', 'Integer', '窗口圆角,默认0');
	initSettings('show', 'Boolean', '是否显示窗口， 默认true');
	initSettings('center', 'Boolean', '是否居中窗口，默认true');
	initSettings('adjustPos', 'Boolean', '创建窗口时是否调整窗口位置，默认true');
	initSettings('x', 'Integer', '窗口左上角X坐标，默认0');
	initSettings('y', 'Integer', '窗口左上角Y坐标，默认0');
	initSettings('width', 'Integer', '窗口宽度，默认960');
	initSettings('height', 'Integer', '窗口高度，默认650');
	initSettings('minWidth', 'Integer', '窗口最小宽度，默认不限制0');
	initSettings('minHeight', 'Integer', '窗口最小高度，默认不限制0');
	initSettings('maxWidth', 'Integer', '窗口最大宽度，默认不限制0');
	initSettings('maxHeight', 'Integer', '窗口最大高度，默认不限制0');
	initSettings('resizeable', 'Boolean', '是否允许改变窗口大小，默认true');
	initSettings('moveable', 'Boolean', '是否允许移动窗口，默认true');
	initSettings('minimizable', 'Boolean', '是否允许最小化窗口，默认true');
	initSettings('maximizable', 'Boolean', '是否允许最大化窗口，默认true');
	initSettings('fullscreenable', 'Boolean', '是否允许全屏窗口，默认true');
	initSettings('closable', 'Boolean', '是否允许关闭窗口，默认true');
	initSettings('fullscreen', 'Boolean', '是否创建窗口时始其全屏，默认false');
	initSettings('alwaysOnTop', 'Boolean', '是否置顶窗口，默认false');
	initSettings('hasShadow', 'Boolean', '是否显示窗口阴影，默认true');

	// Event
	initEvent('create', '', '窗口创建时触发');
	initEvent('closed', '', '窗口关闭后');
	initEvent('restore', '', '窗口还原时触发');
	initEvent('maximize', '', '窗口最大化时触发');
	initEvent('resize', '', '窗口大小发生改变时触发');
	initEvent('move', '', '窗口移动时触发');
	initEvent('minimize', '', '窗口最小化时触发');
	initEvent('blur', '', '失去焦点时触发');
	initEvent('focus', '', '获取焦点时触发');
	initEvent('close', '', '窗口关闭时触发');
	initEvent('notify', '', 'Duilib Notify 的所有通知');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		createEventTable($('#event'), eventArr);
		include('NativeWindow', 'BrowserWindow');
		console.dir(NativeWindow);

		NativeWindow.on('create', function(event) {
			console.dir(event);
			event.data[0].maximize();
			//          win1.maximize();
		});
		NativeWindow.on('closed', function(win1) {
			//         console.dir(win1); 
		});
		$('#createWindow').on('click', function() {
			win = new NativeWindow({

				modal: true,
				hasShadow: true,
				xml: ['<?xml version="1.0" encoding="utf-8" standalone="yes"?>',
					'<Window size="790,560" caption="0,0,0,25" mininfo="790,560" sizebox="3,3,3,3" roundcorner="3,3" bordersize="2" bordercolor="#ff0080ff" inset="1,1,1,1">',
					'    <VerticalLayout dragable="true" bkcolor="#FFFDFDFD" bordercolor="#FFCCCCCC" bordersize="0" borderround="3,3" inset="0,0,0,0">',
					'        <VerticalLayout height="33" name="title_layout">',
					'            <VerticalLayout height="33">',
					'                <HorizontalLayout height="33" inset="0,6,0,6">',
					'                    <HorizontalLayout />',
					'                    <HorizontalLayout />',
					'                    <Button name="minbtn"  dragable="false" height="20" width="20" normalimage="mini_btn.png" hotimage="mini_click_btn.png" pushedimage="mini_click_btn.png" />',
					'                    <HorizontalLayout width="6" />',
					'                    <Button name="maxbtn"  dragable="false" height="20" width="20" normalimage="max_btn.png" hotimage="max_click_btn.png" pushedimage="max_click_btn.png" />',
					'                    <HorizontalLayout width="4" />',
					'                    <Button name="restorebtn" dragable="false" visible="false"  height="20" width="20" normalimage="restore.png" hotimage="restore_click_btn.png" pushedimage="restore.png" />',
					'                    <Button name="closebtn"  dragable="false" height="20" width="20" normalimage="close_btn.png" hotimage="close_click_btn.png" pushedimage="close_click_btn.png" />',
					'                    <HorizontalLayout width="3" />',
					'                </HorizontalLayout>',
					'            </VerticalLayout>',
					'        </VerticalLayout>',
					'        <HorizontalLayout name="browser_layout"></HorizontalLayout>',
					'    </VerticalLayout>',
					'</Window>'
				].join("")
			});
			console.dir(win);
			//          win.showModal();
			window.win = win;
			win.on('click', function(event) {
				event.setReturnValue(3);
				event.stopPropagation();
				console.log(event);
				var target = event.target;
				console.dir(target);
				var data = event.data;
				console.dir(data);
				data[0].sender.setValue('23322');

				//              if(target.name == "minbtn") {
				//                  win.minimize(); 
				//              } else if(target.name == "maxbtn") {
				//                   win.showModal();
				//                  win.maximize(); 
				//              } else if(target.name == "restorebtn") {
				//                  win.restore(); 
				//              } else if(target.name == "closebtn") { 
				//                  win.close(); 
				//              }
				return false;
			});
			win.on('maximize', function() {

			});

		});

		$('#closeWindow').on('click', function() {
			if(win == undefined) {
				alert('undefined');
			}

			console.dir(win);
			win.close();
		});

	});
})();