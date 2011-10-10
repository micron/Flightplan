jQuery(function ($) {

    var outputFlights = function (flights, options) {
        if (flights.length) {
            var flightsString = '';

            $('#flights tbody').remove();

            $.each(flights, function (key, value) {
                if (options.limit >= (key + 1)) {
                    flightsString = flightsString + '<tbody><tr class="ui-widget-content"><td>' + value.number + '</td><td>' + value.destination + '</td><td>' + value.time + '</td><td>' + value.rollway + '</td><td>' + value.pilot + '</td><td>' + value.numberplate + '</td></tr></tbody>';
                }

                if (typeof options.search == 'number' && key == options.search) {
                    flightsString = flightsString + '<tbody><tr class="ui-widget-content"><td>' + value.number + '</td><td>' + value.destination + '</td><td>' + value.time + '</td><td>' + value.rollway + '</td><td>' + value.pilot + '</td><td>' + value.numberplate + '</td></tr></tbody>';
                }
            })

            var toggleFlights = function () {

            }
            options.search = null;
            $('#flights').append(flightsString).show('bounce');

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

    var tempArray = [];

    for (var i = 0, c = flights.length; i < c; i++) {
        $.each(flights[i], function (key, value) {

            var data = {};

            data.value = i;
            data.label = value;
            tempArray.push(data);

        })
    }

    $('#search').autocomplete({
        source: tempArray,
        select: function (event, ui) {
            $("#search").val(ui.item.label);
            options = {
                limit: null,
                search: ui.item.value
            }
            outputFlights(flights, options);
            return false;
        }

    }).data("autocomplete")._renderItem = function (ul, item) {
        return $("<li></li>")
				.data("item.autocomplete", item)
				.append("<a>" + item.label + "</a>")
				.appendTo(ul);
    }
})