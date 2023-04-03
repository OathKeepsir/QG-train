$(document).ready(function () {
    $("#loadData").click(function () {
        $.ajax({
            url: "/getData",
            method: "GET",
            dataType: "json",
            success: function (data) {
                $("#dataDisplay").html(JSON, stringify(data, null, 2));
            },
            error: function (jqXHR, textStatus, errorThrown) {
                alert("Error:" + textStatus + "\n" + errorThrown);
            }
        });
    });
});