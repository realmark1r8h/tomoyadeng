(function() {
	methodArr = [];
	settingsArr = [];


 initApi('MN', 'getName', '', '强制退出程序');
        initApi('MN', 'setName', '', '强制退出程序');
        initApi('MN', 'close', '', '强制退出程序');
        initApi('MN', 'isFocused', '', '强制退出程序');
        initApi('MN', 'show', '', '强制退出程序');
        initApi('MN', 'showInactive', '', '强制退出程序');
        initApi('MN', 'hide', '', '强制退出程序');
        initApi('MN', 'isVisible', '', '强制退出程序');
        initApi('MN', 'maximize', '', '强制退出程序');
        initApi('MN', 'unmaximize', '', '强制退出程序');
        initApi('MN', 'isMaximized', '', '强制退出程序');
        initApi('MN', 'minimize', '', '强制退出程序');
        initApi('MN', 'restore', '', '强制退出程序');
        initApi('MN', 'isMinimized', '', '强制退出程序');
        initApi('MN', 'setFullScreen', '', '强制退出程序');
        initApi('MN', 'isFullScreen', '', '强制退出程序');
        initApi('MN', 'setBounds', '', '强制退出程序');
        initApi('MN', 'getBounds', '', '强制退出程序');
        initApi('MN', 'setSize', '', '强制退出程序');
        initApi('MN', 'getSize', '', '强制退出程序');
        initApi('MN', 'setMinimumSize', '', '强制退出程序');
        initApi('MN', 'getMinimumSize', '', '强制退出程序');
        initApi('MN', 'setMaximumSize', '', '强制退出程序');
        initApi('MN', 'getMaximumSize', '', '强制退出程序');
        initApi('MN', 'setResizable', '', '强制退出程序');
        initApi('MN', 'isResizable', '', '强制退出程序');
        initApi('MN', 'setMovable', '', '强制退出程序');
        initApi('MN', 'isMovable', '', '强制退出程序');
        
        initApi('MN', 'setMinimizable', '', '强制退出程序');
        initApi('MN', 'isMinimizable', '', '强制退出程序');
        initApi('MN', 'setMaximizable', '', '强制退出程序');
        initApi('MN', 'isMaximizable', '', '强制退出程序');
        initApi('MN', 'setFullScreenable', '', '强制退出程序');
        initApi('MN', 'isFullScreenable', '', '强制退出程序');
        initApi('MN', 'setClosable', '', '强制退出程序');
        initApi('MN', 'isClosable', '', '强制退出程序');
        initApi('MN', 'setAlwaysOnTop', '', '强制退出程序');
        initApi('MN', 'isAlwaysOnTop', '', '强制退出程序');
        initApi('MN', 'center', '', '强制退出程序');
        initApi('MN', 'setPosition', '', '强制退出程序');
        initApi('MN', 'getPosition', '', '强制退出程序');
        initApi('MN', 'setTitle', '', '强制退出程序');
        initApi('MN', 'getTitle', '', '强制退出程序');
        initApi('MN', 'flashFrame', '', '强制退出程序');
        initApi('MN', 'topmost', '', '强制退出程序');
        initApi('MN', 'isTopmost', '', '强制退出程序');
        initApi('MN', 'toggleFullScreen', '', '强制退出程序');
        initApi('MN', 'toggleVisible', '', '强制退出程序');
        initApi('MN', 'showModal', '', '强制退出程序');
        initApi('MN', 'setIcon', '', '强制退出程序');
         

	$(function() {
		createApiTable($('#method'), methodArr);
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