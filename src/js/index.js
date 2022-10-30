$(function () {
    $('.color').colorpicker({
        allowEmpty: true,//允许为空,显示清楚颜色按钮
        color: "#ffffff",//初始化颜色
        showInput: true,//显示输入
        containerClassName: "full-spectrum",
        showInitial: true,//显示初始颜色,提供现在选择的颜色和初始颜色对比
        showPalette: true,//显示选择器面板
        showSelectionPalette: true,//记住选择过的颜色
        showAlpha: true,//显示透明度选择
        maxPaletteSize: 7,//记住选择过的颜色的最大数量
        preferredFormat: "hex"//输入框颜色格式,(hex十六进制,hex3十六进制可以的话只显示3位,hsl,rgb三原
    });
});
// $(function () {
//     // Basic instantiation:
//     $('.color').colorpicker();

//     // Example using an event, to change the color of the #demo div background:
//     $('.color').on('colorpickerChange', function(event) {
//       $('#demo').css('background-color', event.color.toString());
//     });
//   });


$(document).ready(function () {


    //圆
    var $circle = null
    var $draw = $("#left")
    // 圆心位置
    var centerX = 500;
    var centerY = 500;

    var circleCnt =0
    $drawCir = $("#circle")
    $drawCir.click(function (event) {
        circleCnt=circleCnt+1
        var circlename='circle_'+circleCnt
        $circle = $('<div class="circle"></div>');
        $circle.attr('id',circlename);
        $draw.append($circle);
        var radius=100
        $circle.css("left", centerX - radius + "px");
        $circle.css("top", centerY - radius + "px");
        $circle.css("width", 2 * radius + "px");
        $circle.css("height", 2 * radius + "px");
        $circle.css("border-radius", radius + "px")
    })
    
})