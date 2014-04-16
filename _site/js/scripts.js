// detect mobile browsers
function mobileBrowser() {
    return (/Android|iPhone|iPad|iPod|BlackBerry/i).test(navigator.userAgent || navigator.vendor || window.opera);
}

// parallax header
if (!mobileBrowser()) { // parallax scrolling is janky on mobile, so we don't do it.
    jQuery(document).ready(function($) {
        $(window).scroll( function()
        {
            var scroll = $(window).scrollTop(), slowScroll = scroll/3;
            var headerheight = $('header').height();
            $('header').css({ transform: "translateY(" + slowScroll + "px)" });
            $('header .container').css({ opacity: Math.min(1, 1.2 - scroll/headerheight) });
        });
    });
}

---
---
(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
})(window,document,'script','//www.google-analytics.com/analytics.js','ga');

ga('create', 'UA-40241848-1', 'qrohlf.com');
ga('send', 'pageview');