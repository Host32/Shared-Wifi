(function ($) {
    'use strict';

    $(function () {
        $('img').each(function () {
            var src = $(this).data('src'),
		elem = $(this);
            $.ajax({
                url: src,
                success: function (data) {
                    elem.attr('src', 'data:image/png;base64,' + data);
                }
            });
        });
    });
}(window.jQuery));
