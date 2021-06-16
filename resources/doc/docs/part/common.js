;(function(){
    $(function(){
       
       $('div, body, html').addClass('drag');
       $('button, input, a, textarea').removeClass('drag');
       $('button, input, a, textarea').addClass('no-drag');
       $('iframe, .container').removeClass('drag');
      
    });
})();
