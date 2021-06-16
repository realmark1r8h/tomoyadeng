;
(function() {
    $(function() {
        $('button').off('click');
        $('button').on('click', function() {
            alert(3);
        });
    });
})();