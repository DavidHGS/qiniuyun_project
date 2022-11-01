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

    //公用 const
    var posX = 500
    var posY = 500
    var $draw = $("#left")
    //矩形
    var $rect = null

    //圆
    var $circle = null

    // 圆心位置
    var centerX = 500;
    var centerY = 500;
    //计数器
    var circleCnt = 0
    var rectCnt = 0
    //是否正在移动
    var circleMoving = false

    //当前选中对象
    var $currObj = null
    if ($currObj != null) {
        $currObj.css("border-width", $("#xiankuan").val())
        $currObj.css("border-style", $("#xianxing").val())
        $currObj.css("border-color", $("#xianse").val())
        $currObj.css("background-color", $("#tianchongse").val())
    }
    $drawCir = $("#circle")//nav 点击按钮
    $drawRect = $("#rect")//nav 点击按钮
    $drawRect.click(function (event) {//click事件创建矩形
        rectCnt = rectCnt + 1
        var rectname = 'rect_' + rectCnt
        $rect = $('<div class="rect"></div>');
        $rect.attr('id', rectname);
        $draw.append($rect);
        var width = 200, height = 100
        $rect.css("left", posX - width / 2 + "px");
        $rect.css("top", posY - height / 2 + "px");
        $rect.css("width", width + "px");
        $rect.css("height", height + "px");
        //为新创建的矩形添加事件 点击出现右侧属性栏
        $("#" + rectname).on("click", function () {
            $currObj = $("#" + rectname)
            console.log($currObj)
            $("#style").addClass("active in")
            $("#text").removeClass("active")
            $("#yangshi").addClass("active")
            $("#wenben").removeClass("active")
            $("#xiankuan").val("" + $(this).css("border-width"))
            $("#xianxing").val("" + $(this).css("border-style"))
            $("#xianse").val("" + $(this).css("border-color"))
            $("tianchongse").val("" + $(this).css("background-color"))
        })
        console.log($currObj)
        $("#" + rectname).mousedown(function (event) {
            deltax = event.clientX - $(this).offset().left //鼠标距离上半弧的距离
            deltay = event.clientY - $(this).offset().top   //鼠标距离左半弧的距离
            $(document).bind('mousemove', function (event) {
                x = event.clientX - deltax//距离左边的位置
                y = event.clientY - deltay//距离上边的位置
                centerX = x + width / 2
                centerY = y + height / 2
                console.log(centerX + "++++++++++++++" + centerY)
                if (x < 0) {
                    x = 0
                }
                if (x > ($draw.width() - width)) {
                    x = $draw.width() - width
                }
                if (y < $("#navbar").height()) {
                    y = $("#navbar").height()
                }
                if (y > ($draw.height() - height + $("#navbar").height())) {
                    y = $draw.height() - height + $("#navbar").height()
                }
                console.log(x, y)
                $("#" + rectname).css({ 'left': x + 'px', 'top': y + 'px' })
                return false
            })
            $(document).bind('mouseup', function (event) {
                $(this).unbind('mousemove')
                $(this).unbind('mouseup')
            })
            return false
        })
        
    })

    $drawCir.click(function (event) {//click事件创建圆
        circleCnt = circleCnt + 1
        var circlename = 'circle_' + circleCnt
        $circle = $('<div class="circle"></div>');
        $circle.attr('id', circlename);
        $draw.append($circle);
        var radius = 100//半径
        $circle.css("left", posX - radius + "px");
        $circle.css("top", posY - radius + "px");
        $circle.css("width", 2 * radius + "px");
        $circle.css("height", 2 * radius + "px");
        $circle.css("border-radius", radius + "px")
        //为新创建的圆添加事件 点击出现右侧属性栏
        $("#" + circlename).on("click", function () {
            $currObj = $("#" + circlename)
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
        //     circleMoving=true;
        //     event.preventDefault();
        // })
        // //鼠标移动事件
        // $("#"+circlename).on("mousemove",function(){


        // })
        // //释放鼠标事件 
        // $("#"+circlename).on("mouseup",function(event){
        //     if(circleMoving){
        //         $("#"+circlename).css("left",event.pageX-$draw.offset().left)
        //         $("#"+circlename).css("top",event.pageY-$draw.offset().top)
        //     }
        //     circleMoving=false
        // })
        $("#" + circlename).mousedown(function (event) {
            deltax = event.clientX - $(this).offset().left //鼠标距离上半弧的距离
            deltay = event.clientY - $(this).offset().top   //鼠标距离左半弧的距离
            $(document).bind('mousemove', function (event) {
                x = event.clientX - deltax//距离左边的位置
                y = event.clientY - deltay//距离上边的位置
                centerX = x + radius
                centerY = y + radius
                console.log(centerX + "++++++++++++++" + centerY)
                if (x < 0) {
                    x = 0
                }
                if (x > ($draw.width() - 2 * radius)) {
                    x = $draw.width() - 2 * radius
                }
                if (y < $("#navbar").height()) {
                    y = $("#navbar").height()
                }
                if (y > ($draw.height() - 2 * radius + $("#navbar").height())) {
                    y = $draw.height() - 2 * radius + $("#navbar").height()
                }
                console.log(x, y)
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