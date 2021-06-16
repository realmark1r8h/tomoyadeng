includes('EventEmitter', 'BrowserWindow', 'app', 'dynamic', 'Menu');

function foo1(val) {
    console.log(val);
    return val;
}

function foo2(val) {
    console.log(val);
    return val;
}

function foo3(val) {
    console.log(val);
    return val;
}

;
(function() {

    methodArr = [];
    settingsArr = [];
    eventArr = [];

    initApi('SN', 'addBrowserWindowSettings', '',
        '给一个URL添加默认的窗口显示参数，如果一个BrowserWindow不是通过new BrowserWindow(options)创建的可以使用该函数设置BrowserWindow的显示参数',
        'url, String, 需要设置显示参数的URL', 'settings, Object, 显示参数');
    initApi('SN', 'removeBrowserWindowSettings', '', '移除所给URL的默认显示参数', 'url, String, 需要移除显示参数的URL');
    initApi('SN', 'getBrowserWindowSettings', '', '获取所给URL的显示参数', 'url, String, URL');
    initApi('SN', 'currentWindow', 'Object', '获取当前页面的BrowserWindow对象');
    initApi('SN', 'getAllWindows', 'Array', '获取所有BrowserWindow对象');
    initApi('SN', 'getFocusedWindow', 'Object', '获取处于焦点状态下的BrowserWindow对象');
    initApi('SN', 'fromId', 'Object', '通过ID获取BrowserWindow对象', 'id, String, BrowserWindow ID');

    initApi('MS', 'getName', 'String', '获取窗口名称');
    initApi('MN', 'setName', '', '设置窗口名称', 'name, String, BrowserWindow 名称');
    initApi('MS', 'id', 'String', '获取窗口 ID');

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

    initApi('MN', 'setSkipTaskbar', '', '未实现');
    initApi('MS', 'getNativeWindowHandle', '', '未实现');
    initApi('MN', 'hookWindowMessage', '', '未实现');
    initApi('MS', 'isWindowMessageHooked', '', '未实现');
    initApi('MN', 'unhookWindowMessage', '', '未实现');
    initApi('MN', 'unhookAllWindowMessages', '', '未实现');
    initApi('MN', 'focusOnWebView', '', '未实现');
    initApi('MN', 'blurWebView', '', '未实现');
    initApi('MN', 'capturePage', '', '未实现');
    initApi('MN', 'loadURL', '', '加载URL', 'url, String, URL');
    initApi('MN', 'reload', '', '重新加载页面');
    initApi('MN', 'setMenu', '', '未实现');
    initApi('MN', 'setProgressBar', '', '未实现');
    initApi('MN', 'setOverlayIcon', '', '未实现');
    initApi('MN', 'setHasShadow', '', '设置是否显示窗口阴影', 'hasShadow, Boolean, 是否显示');
    initApi('MS', 'hasShadow', 'Boolean', '判断是否显示窗口阴影');

    initApi('MN', 'showDevTools', '', '打开调试窗口');
    initApi('MN', 'closeDevTools', '', '关闭调试窗口');

    initApi('MN', 'exec', '', '发送普通消息（不管执行结果）');
    initApi('MS', 'sync', 'POD', '发送同步消息（直接获得执行结果）');
    initApi('MA', 'async', '', '发送异步消息（通过回调函数得到执行结果）');

    initApi('MN', 'enableDrag', '', '允许被拖动');
    initApi('MN', 'disableDrag', '', '禁止窗口被拖动');

    initApi('MS', 'getBrowser', 'Object', '获取窗口的Browser对象');

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

    // BrowserWindow Settings
    initSettings('url', 'String', '浏览窗口打开页面地址, 默认"chrome://version"');
    initSettings('offscreen', 'Boolean', '是否使用离屏渲染, 默认false');
    initSettings('transparent', 'Boolean', '是否透明窗口,offscreen为true时，此参数有效， 默认false');

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
        include('BrowserWindow');

        var win = BrowserWindow.currentWindow;

        $('#addBrowserWindowSettings').click(function() {
            BrowserWindow.addBrowserWindowSettings('http://www.oschina.net', {
                titleBar: true,
                alwaysOnTop: true,
            });
        });

        $('#removeBrowserWindowSettings').click(function() {
            BrowserWindow.removeBrowserWindowSettings('http://www.oschina.net');
        });
        
        $('#framelessWindow').click(function(){
            var framelessWindow = new BrowserWindow({
                titleBar: false,
                url: 'http://127.0.0.1:8020/amoylel/doc/example/FramelessWindow.html'
            });
        });

        $('#showDevTools').click(function() {
            win.showDevTools();
        });
        $('#closeDevTools').click(function() {
            win.closeDevTools();
        });

        $('#id').click(function() {
            alert(win.id());
        });
        $('#destroy').click(function() {
            win.destroy();
        });
        $('#close').click(function() {
            win.close();
        });
        $('#focus').click(function() {
            win.focus();
        });
        $('#isFocused').click(function() {
            alert(win.isFocused());
        });
        $('#show').click(function() {
            win.show();
        });
        $('#showInactive').click(function() {
            win.showInactive();
        });
        $('#hide').click(function() {
            win.hide();
        });
        $('#isVisible').click(function() {
            //		    require('app').on();
            alert(win.isVisible());
            //		    console.log(win.isVisible());
            //          console.log(win.isVisible());
            //          console.log(win.isVisible());
            //          console.log(win.isVisible());
            //          alert(require('app').on());
            //			alert(win.isVisible());
        });
        $('#maximize').click(function() {
            win.maximize();
        });
        $('#unmaximize').click(function() {
            win.unmaximize();
        });
        $('#isMaximized').click(function() {
            alert(win.isMaximized());
        });
        $('#minimize').click(function() {
            win.minimize();
        });
        $('#restore').click(function() {
            win.restore();
        });
        $('#isMinimized').click(function() {
            alert(win.isMinimized());
        });
        $('#dlltest').click(function() {

            var cmd = DWORD(23423);
            console.dir(cmd);
            console.dir(DWORD);
            alert(cmd.id);

            var fn = require('Win32Project1');
            fn.import("INT fnWin32Project1();");
            alert(fn.fnWin32Project1());

            var kernel32 = require('kernel32');
            kernel32.import('VOID SetLastError(DWORD);');
            kernel32.import('DWORD GetLastError();');
            kernel32.SetLastError(3333);
            alert(kernel32.GetLastError());

        });
        $('#test1').click(function() {
            alert(win.test1());
        });
        $('#test2').click(function() {
            alert(win.test2());
        });
        $('#test3').click(function() {
            win.test3(function(str) {
                alert(str);
            });
        });
        $('#test4').click(function() {
            alert(win.test4());
        });
        $('#test5').click(function() {
            alert(win.test5());
        });
        $('#test6').click(function() {
            alert(win.test6());
        });
        $('#quit').click(function() {
            app.quit();
        });
        $('#exit').click(function() {
            app.exit();
        });
        $('#external').click(function() {
            alert(dynamic.foo1());
        });
        $('#fullscreen').click(function() {
            win.setFullScreen(true);
        });
        $('#normalscreen').click(function() {
            win.setFullScreen(false)
        });
        $('#setBounds').click(function() {
            win.setBounds({ x: 100, y: 100, width: 900, height: 600 });
        });
        $('#getBounds').click(function() {
            var cc = win.getBounds();
            alert(JSON.stringify(cc));
            console.log(cc);
        });

        $('#setSize').click(function() {
            win.setSize(400, 300);
        });
        $('#getSize').click(function() {
            var cc = win.getSize();
            alert(JSON.stringify(cc));
            console.log(cc);
        });

        $('#setMinimumSize').click(function() {
            win.setMinimumSize(400, 300);
        });
        $('#getMinimumSize').click(function() {
            var cc = win.getMinimumSize();
            alert(JSON.stringify(cc));
            console.log(cc);
        });

        $('#setMaximumSize').click(function() {
            win.setMaximumSize(800, 500);
        });
        $('#getMaximumSize').click(function() {
            var cc = win.getMaximumSize();
            alert(JSON.stringify(cc));
            console.log(cc);
        });
        $('#setMovable').click(function() {
            win.setMovable(false);
        });
        $('#isMovable').click(function() {
            var cc = win.isMovable();
            alert(cc);
        });

        // 
        $('#setMinimizable').click(function() {
            win.setMinimizable(false);
        });
        $('#isMinimizable').click(function() {
            var cc = win.isMinimizable();
            alert(cc);
        });

        $('#setMaximizable').click(function() {
            win.setMaximizable(false);
        });
        $('#isMaximizable').click(function() {
            var cc = win.isMaximizable();
            alert(cc);
        });

        $('#setFullScreenable').click(function() {
            win.setFullScreenable(false);
        });
        $('#isFullScreenable').click(function() {
            var cc = win.isFullScreenable();
            alert(cc);
        });

        $('#setClosable').click(function() {
            win.setClosable(false);
        });
        $('#isClosable').click(function() {
            var cc = win.isClosable();
            alert(cc);
        });

        $('#setAlwaysOnTop').click(function() {
            win.setAlwaysOnTop(true);
        });
        $('#isAlwaysOnTop').click(function() {
            var cc = win.isAlwaysOnTop();
            alert(cc);
        });

        $('#setPosition').click(function() {
            win.setPosition(0, 0);
        });
        $('#setPosition').click(function() {
            var cc = win.getPosition();
            alert(JSON.stringify(cc));
        });

        $('#setTitle').click(function() {
            win.setTitle('在在在 2 3 323  2');
        });
        $('#getTitle').click(function() {
            var cc = win.getTitle();
            alert(cc);
        });

        $('#flashFrame').click(function() {
            win.flashFrame(true);
        });

        $('#setHasShadow').click(function() {
            win.setHasShadow(!win.hasShadow());
        });
        $('#hasShadow').click(function() {
            var cc = win.hasShadow();
            alert(cc);
        });
        $('#loadURL').click(function() {
            win.loadURL('http://www.baidu.com');
        });
        $('#reload').click(function() {
            win.reload();
        });
        $('#exec').click(function() {
            win.exec('abcd', 23);
        });
        $('#sync').click(function() {
            var arr = win.sync('abcd', 23);
            alert(arr);
        });

        $('#async').click(function() {
            win.async('abcd', 23, function(val) {
                alert(val);
            });
        });
        $('#setIcon1').click(function() {
            win.setIcon('skin/logo.ico');
        });
        $('#setIcon2').click(function() {
            win.setIcon('skin/logo1.ico');
        });
        $('#setIcon3').click(function() {
            win.setIcon('skin/logo2.ico');
        });

        win.on('abcd', function(event) {
            event.setReturnValue(3233);
            event.stopPropagation();
        });

        $('#test_require').click(function() {
            alert((function() { return BrowserWindow.currentWindow.emit; })());
            alert(BrowserWindow.currentWindow.emit);
            console.dir(BrowserWindow.currentWindow.emit);
            prompt();

        });

        $('#normalWindow').click(function() {
            var normalWindow = new BrowserWindow({
                roundcorner: 3,
                name: 'aaaaaaaaaaaaa',
                titleBar: true,
                width: 960,
                height: 650,
                minWidth: 471,
                minHeight: 520,
                url: "http://www.baidu.com/more"
            });
        });
        $('#offscreenWindow').click(function() {
            var offscreenWindow = new BrowserWindow({
                roundcorner: 3,
                name: 'aaaaaaaaaaaaa',
                titleBar: true,
                width: 960,
                height: 650,
                minWidth: 471,
                minHeight: 520,
                url: "http://www.baidu.com/more",
                offscreen: true
            });
        });
        $('#transparentWindow').click(function() {
            var transparentWindow = new BrowserWindow({
                roundcorner: 3,
                name: 'aaaaaaaaaaaaa',
                titleBar: true,
                width: 960,
                height: 650,
                minWidth: 471,
                minHeight: 520,
                url: "http://www.baidu.com/more",
                offscreen: true,
                transparent: true
            });
        });
        $('#login').click(function() {
            var win3 = new BrowserWindow({
                offscreen: true,
                transparent: true,
                minimizable: false,
                resizeable: false,
                windowColor: 0x0,
                roundcorner: 5,
                hasShadow: true,
                width: 434,
                height: 334,
                minWidth: 434,
                minHeight: 334,
                maxinfo: "",
                //                      url:"http://127.0.0.1:8020/amoylel/web/index2.html"
                url: "http://127.0.0.1:8020/amoylel/web/QQ/login.html"
                //          url:"http://127.0.0.1:8020/zui-1.6.0/setting.html"
            });
        });
        $('#chat').click(function() {
            var win3 = new BrowserWindow({
                roundcorner: 5,
                windowColor: 0x0,
                width: 440,
                height: 505,
                minWidth: 440,
                minHeight: 505,
                sizebox: "4,4,6,6",
                caption: "0,0,0,0",
                mininfo: "471,520",
                maxinfo: "",
                //                      url:"http://127.0.0.1:8020/amoylel/web/index2.html"
                url: "http://127.0.0.1:8020/amoylel/web/QQ/chat.html"
                //          url:"http://127.0.0.1:8020/zui-1.6.0/setting.html"
            });
        });

        $('#main').click(function() {
            var win3 = new BrowserWindow({
                roundcorner: 5,
                windowColor: 0x0,
                width: 280,
                height: 700,
                minWidth: 280,
                minHeight: 700,
                url: "http://127.0.0.1:8020/amoylel/web/QQ/main.html"
            });
        });
        $('#picture_viewer').click(function() {
            var win3 = new BrowserWindow({
                offscreen: true,
                transparent: true,
                titleBar: false,
                hasShadow: false,
                windowColor: 0x00000000,
                roundcorner: 5,
                width: 461,
                height: 505,
                minWidth: 461,
                minHeight: 505,
                caption: "0,0,0,0",
                mininfo: "600,520",
                maxinfo: "",
                url: "http://127.0.0.1:8020/amoylel/web/viewer/viewpanel.html"
            });
        });
        $('#fm').click(function() {
            var win3 = new BrowserWindow({
                offscreen: false,
                transparent: false,
                width: 960,
                height: 652,
                minWidth: 960,
                minHeight: 652,
                caption: "0,0,0,0",
                mininfo: "600,520",
                maxinfo: "",
                url: "http://fm.baidu.com/"
            });
        });
        $('#exe_creator').click(function() {
            var win3 = new BrowserWindow({
                offscreen: true,
                hasShadow: true,
                width: 420,
                height: 652,
                minWidth: 420,
                minHeight: 652,
                caption: "0,0,0,0",
                mininfo: "600,520",
                maxinfo: "",
                url: "http://127.0.0.1:8020/amoylel/web/setting.html"
            });
        });
    })
})();