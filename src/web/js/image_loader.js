(function ($) {
    'use strict';

    $(function () {
        $('img').each(function () {
            var src = $(this).data('src');
            $.ajax({
                url: src,
                success: function (data) {
                    $(this).attr('src', 'data:image/png;base64,' + data);
                }
            });
        });
    });
}(window.jQuery));
