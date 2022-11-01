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

    var circleCnt = 0

    //是否正在移动
    var isMoving = false
    $drawCir = $("#circle")
    $drawCir.click(function (event) {//click事件创建圆
        circleCnt = circleCnt + 1
        var circlename = 'circle_' + circleCnt
        $circle = $('<div class="circle"></div>');
        $circle.attr('id', circlename);
        $draw.append($circle);
        var radius = 100//半径
        $circle.css("left", centerX - radius + "px");
        $circle.css("top", centerY - radius + "px");
        $circle.css("width", 2 * radius + "px");
        $circle.css("height", 2 * radius + "px");
        $circle.css("border-radius", radius + "px")
        //为新创建的圆添加事件
        $("#" + circlename).on("click", function () {
            $("#style").addClass("active in")
            $("#text").removeClass("active")
            $("#yangshi").addClass("active")
            $("#wenben").removeClass("active")
            $("#xiankuan").val("" + $(this).css("border-width"))
            $("#xianxing").val("" + $(this).css("border-style"))
            $("#xianse").val("" + $(this).css("border-color"))
            $("tianchongse").val("" + $(this).css("background-color"))
        })
        //按下鼠标开始画圆
        // $("#"+circlename).on("mousedown",function(event){
        //     centerX=event.pageX-$draw.offset().left;//相对于画图面板的距离
        //     centerY=event.pageY-$draw.offset().top;
        //     isMoving=true;
        //     event.preventDefault();
        // })
        // //鼠标移动事件
        // $("#"+circlename).on("mousemove",function(){


        // })
        // //释放鼠标事件 
        // $("#"+circlename).on("mouseup",function(event){
        //     if(isMoving){
        //         $("#"+circlename).css("left",event.pageX-$draw.offset().left)
        //         $("#"+circlename).css("top",event.pageY-$draw.offset().top)
        //     }
        //     isMoving=false
        // })
        $("#" + circlename).mousedown(function (event) {
            deltax = event.clientX - $(this).offset().left //可视距离左-距离父级的左
            deltay = event.clientY - $(this).offset().top   //
            $(document).bind('mousemove', function (event) {
                x = event.clientX - deltax
                y = event.clientY - deltay
                centerX = x + radius
                centerY = y + radius
                // if (x < deltax) {
                //     x = deltax
                // }
                // if (x > ($draw.width() - radius)) {
                //     x = $draw.width() - radius
                // }
                // if (y < deltay) {
                //     y = deltay
                // }
                // if (y > ($draw.height() - radius)) {
                //     y = $draw.height() - radius
                // }
                console.log(x,y)
                console.log(deltax,deltay)
                $("#" + circlename).css({ 'left': x + 'px', 'top': y + 'px' })
                return false
            })
            $(document).bind('mouseup', function (event) {
                $(this).unbind('mousemove')
                $(this).unbind('mouseup')
            })
            return false
        })
    })

})