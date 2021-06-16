(function() {
    methodArr = [];

    initApi('SS', 'exec', '', '发送普通消息', 'message, String, 消息名', '[arguments...], POD, 消息内容, 任意长度的不定项参数');
    initApi('SS', 'sync', 'POD', '发送同步消息','message, String, 消息名', '[arguments...], POD, 消息内容, 任意长度的不定项参数');
    initApi('SS', 'async', '', '发送异步消息','message, String, 消息名', 
    '[arguments...], POD, 消息内容, 任意长度的不定项参数',
    'callback, Funcion, 回调函数，放在任意位置均可以，但只能有一个回调函数');

    $(function() {
        createApiTable($('#method'), methodArr);
        includes('ipc');

        console.dir(ipc);
        $('#exec').on('click', function() {
            var val = ipc.exec('message', 123);
            console.dir(val);
        });

        $('#sync').on('click', function() {
            var val = ipc.sync('message', 123);
            console.dir(val);
        });

        $('#async').on('click', function() {
            ipc.async('message', 123, function(val) {
                console.dir(val);
            });
        });

    })
})();