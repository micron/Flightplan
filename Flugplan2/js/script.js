jQuery(function ($) {

    var outputFlights = function (flights, options) {
        if (flights.length) {
            var flightsString = '';

            $('#flights tbody').remove();

            $.each(flights, function (key, value) {
                if (options.limit >= (key + 1)) {
                    flightsString = flightsString + '<tbody><tr><td>' + value.number + '</td><td>' + value.destination + '</td><td>' + value.time + '</td><td>' + value.rollway + '</td><td>' + value.pilot + '</td><td>' + value.numberplate + '</td></tr></tbody>';
                }
            })

            $('#flights').append(flightsString);
        }
    }

    var options = {
        limit: flights.length
    };

    outputFlights(flights, options);

    $('#amount').slider({
        min: 1,
        max: flights.length,
        value: flights.length,
        slide: function (event, ui) {
            $("#Text1").val(ui.value);
        },
        stop: function () {
            options.limit = $("#amount").slider("value");
            outputFlights(flights, options);
        }
    });

    $("#Text1").val($("#amount").slider("value"));
})