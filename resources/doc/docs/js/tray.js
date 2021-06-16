(function() {

    methodArr = [];
    eventArr = [];
    initApi('SN', 'show', '', '显示托盘图标');
    initApi('SN', 'hide', '', '隐藏托盘图标');
    initApi('SN', 'blink', '', '闪烁或停止闪烁托盘图标', 'bBlink, Boolean, 是否闪烁');
    initApi('SS', 'isBlink', 'Boolean', '判断托盘是否闪烁');
    initApi('SN', 'setIcon', '', '设置托盘图标', 'path, String, 图标本地路径');
    initApi('SN', 'setTooltip', '', '设置托盘提示', 'tooltip, String, 提示文字');

    initEvent('buttondown', '', '鼠标左键按下时触发');
    initEvent('buttonup', '', '鼠标左键弹起时触发');
    initEvent('rbuttondown', '', '鼠标右键近下时触发');
    initEvent('rbuttonup', '', '鼠标右键弹起时触发');
    initEvent('click', '', '鼠标左键单击时触发');
    initEvent('dbclick', '', '鼠标左键双击时触发');
    initEvent('mousehover', '', '鼠标悬停时触发');
    initEvent('moveleave', '', '鼠标离开时触发');

    $(function() {
        createApiTable($('#method'), methodArr);
        createEventTable($('#event'), eventArr);
        include('tray');
        console.dir(tray);

        $('#show').on('click', function() {
            tray.show();
        });
        $('#hide').on('click', function() {
            tray.hide();
        });
        $('#setIcon').on('click', function() {
            tray.setIcon('skin/logo.ico');
        });
        $('#setIcon1').on('click', function() {
            tray.setIcon('E:/amoylel-Out/Binary.UD32/skin/logo1.ico');
        });
        $('#setIcon2').on('click', function() {
            tray.setIcon('skin/logo2.ico');
        });
        $('#setIcon3').on('click', function() {
            tray.setIcon('skin/qq.ico');
        });
        $('#startBlink').on('click', function() {
            tray.blink(true);
        });
        $('#stopBlink').on('click', function() {
            tray.blink(false);
        });
        $('#isBlink').on('click', function() {
            alert(tray.isBlink());
        });

        $('#setTooltip').on('click', function() {
            tray.setTooltip(new Date().toString());
        });

        tray.on('buttondown', function() {
            $('#output').text('左键按下');
        });
        tray.on('buttonup', function() {
            $('#output').text('左键弹起');
        });
        tray.on('rbuttondown', function() {
            $('#output').text('右键按下');
        });
        tray.on('rbuttonup', function() {
            $('#output').text('右键弹起');
        });

        tray.on('click', function() {
            $('#output').text('单击托盘');
        });

        tray.on('dbclick', function() {
            $('#output').text('双击托盘');
        });

        tray.on('mouseenter', function() {
            $('#output').text('鼠标进入托盘');
        });


        tray.on('mousehover', function() {
            $('#output').text('鼠标悬停托盘');
        });

        tray.on('mouseleave', function() {
            $('#output').text('鼠标离开托盘');
        });

        //      tray.on('rbuttondown', function(){
        //          var menu = new Menu({
        //              lineHeight: 32,
        //              menu: [
        //                  { id: '1', text: '设置' },
        //                  { id: '2', text: '意见反馈' },
        //                  { id: '3', text: '帮助' },
        //                  { id: '4', text: '关于程序' },
        //                  { id: '5', text: '退出程序' }
        //              ]
        //          });
        //      });

    })
})();