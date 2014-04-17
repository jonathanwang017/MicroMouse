$(document).ready(function() {
    $("#header_subtitle").mouseover(function() {
        $("#header_subtitle").text("Berkeley - Team LiveMau5");
    });
    $("#header_subtitle").mouseleave(function() {
        $("#header_subtitle").text("A record of our robot building experience");
    });
    $("#description_header").click(function() {
        $("#description_sect").toggle();
    });
    $("#parts_header").click(function() {
        $("#parts_sect").toggle();
    });
    $("#building_header").click(function() {
        $("#building_sect").toggle();
    });
    $("#wiring_header").click(function() {
        $("#wiring_sect").toggle();
    });
    $("#challenges_header").click(function() {
        $("#challenges_sect").toggle();
    });
    $("#operations_header").click(function() {
        $("#operations_sect").toggle();
    });
    $("#algorithms_header").click(function() {
        $("#algorithms_sect").toggle();
    });
});