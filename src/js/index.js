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

    // 中心位置
    var pointA = {}
    //计数器
    var circleCnt = 0
    var rectCnt = 0
    //是否正在移动
    var circleMoving = false
    var rectMoving = false
    //当前选中对象

    $drawCir = $("#circle")//nav 点击按钮
    $drawRect = $("#rect")//nav 点击按钮
    /***************************************************矩形****************************************************** */
    $drawRect.click(function (event) {//click事件创建矩形
        rectCnt = rectCnt + 1
        var rectname = 'rect_' + rectCnt
        $rect = $('<div class="rect"><div class="rotate">旋转</div></div>');
        $rect.attr('id', rectname);
        $draw.append($rect);
        var width = 200, height = 100//真正宽高是198，98
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
        $("#" + rectname).bind("mousemove", function (event) {
            pointA = {//中心点坐标
                X: $("#" + rectname).width() / 2 + $("#" + rectname).offset().left + parseInt($("#" + rectname).css("border-width")),
                Y: $("#" + rectname).height() / 2 + $("#" + rectname).offset().top + parseInt($("#" + rectname).css("border-width"))
            }
            if ((pointA.X - $("#" + rectname).width() / 2 < event.pageX && event.pageX < pointA.X + $("#" + rectname).width() / 2) && ((pointA.Y - $("#" + rectname).height() / 2) < event.pageY && event.pageY < (pointA.Y + $("#" + rectname).height() / 2))) {
                $("#" + rectname).css("cursor", "move")
            }
            else if
                (
                (
                    (pointA.X + $("#" + rectname).width() / 2 <= event.pageX && event.pageX <= pointA.X + $("#" + rectname).width() / 2 + parseInt($("#" + rectname).css("border-width")))
                    ||
                    (pointA.X - $("#" + rectname).width() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageX && event.pageX <= pointA.X - $("#" + rectname).width() / 2)
                )
                &&
                (
                    (pointA.Y - $("#" + rectname).height() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageY && event.pageY <= pointA.X + $("#" + rectname).height() / 2 + parseInt($("#" + rectname).css("border-width")))
                )

                ||
                (
                    (pointA.Y - $("#" + rectname).height() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageY && event.pageY <= pointA.Y - $("#" + rectname).height() / 2)
                    ||
                    (pointA.Y + $("#" + rectname).height() / 2 <= event.pageY && event.pageY <= pointA.Y + $("#" + rectname).height() / 2 + parseInt($("#" + rectname).css("border-width")))
                )
                &&
                ((
                    pointA.X - $("#" + rectname).width() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageX && event.pageX <= pointA.X + $("#" + rectname).width() / 2 + parseInt($("#" + rectname).css("border-width"))
                )
                )
            ) {
                $("#" + rectname).css("cursor", "se-resize")
            }
        })
        $("#" + rectname).mousedown(function (event) {
            event.preventDefault()
            event.stopPropagation()
            pointA = {//中心点坐标
                X: $("#" + rectname).width() / 2 + $("#" + rectname).offset().left + parseInt($("#" + rectname).css("border-width")),
                Y: $("#" + rectname).height() / 2 + $("#" + rectname).offset().top + parseInt($("#" + rectname).css("border-width"))
            }
            minWidth = $("#" + rectname).width() - parseInt($("#" + rectname).css("border-width")) * 2
            minHeight = $("#" + rectname).height() - parseInt($("#" + rectname).css("border-width")) * 2
            if ((pointA.X - $("#" + rectname).width() / 2 < event.pageX && event.pageX < pointA.X + $("#" + rectname).width() / 2) && ((pointA.Y - $("#" + rectname).height() / 2) < event.pageY && event.pageY < (pointA.Y + $("#" + rectname).height() / 2))) {
                //在小矩形内 触发平移事件
                $("#" + rectname).css("cursor", "move")
                rectMoving = true
                deltax = event.clientX - $(this).offset().left //鼠标距离上半弧的距离
                deltay = event.clientY - $(this).offset().top   //鼠标距离左半弧的距离
                pointA.X = $("#" + rectname).width() / 2 + $("#" + rectname).offset().left + parseInt($("#" + rectname).css("border-width"))
                pointA.Y = $("#" + rectname).height() / 2 + $("#" + rectname).offset().top + parseInt($("#" + rectname).css("border-width"))
                $(document).bind('mousemove', function (event) {
                    event.preventDefault()
                    event.stopPropagation()
                    if (rectMoving) {
                        x = event.clientX - deltax//距离左边的位置
                        y = event.clientY - deltay//距离上边的位置
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
                        $("#" + rectname).css({ 'left': x + 'px', 'top': y + 'px' })
                    }
                })
                $(document).bind('mouseup', function (event) {
                    rectMoving = false
                })

            }
            else if (
                (
                    (pointA.X + $("#" + rectname).width() / 2 <= event.pageX && event.pageX <= pointA.X + $("#" + rectname).width() / 2 + parseInt($("#" + rectname).css("border-width")))
                    ||
                    (pointA.X - $("#" + rectname).width() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageX && event.pageX <= pointA.X - $("#" + rectname).width() / 2)
                )
                &&
                (
                    (pointA.Y - $("#" + rectname).height() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageY && event.pageY <= pointA.X + $("#" + rectname).height() / 2 + parseInt($("#" + rectname).css("border-width")))
                )

                ||
                (
                    (pointA.Y - $("#" + rectname).height() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageY && event.pageY <= pointA.Y - $("#" + rectname).height() / 2)
                    ||
                    (pointA.Y + $("#" + rectname).height() / 2 <= event.pageY && event.pageY <= pointA.Y + $("#" + rectname).height() / 2 + parseInt($("#" + rectname).css("border-width")))
                )
                &&
                ((
                    pointA.X - $("#" + rectname).width() / 2 - parseInt($("#" + rectname).css("border-width")) <= event.pageX && event.pageX <= pointA.X + $("#" + rectname).width() / 2 + parseInt($("#" + rectname).css("border-width"))
                )
                )
            ) {}
            // {//else if
            //     var pointB = {};
            //     var pointC = {}; // A,B,C分别代表中心点，起始点，结束点坐标
            //     // 这里通过鼠标的移动获取起始点和结束点
            //     var typeMouse = false;
            //     var moveMouse = false;
            //     var allA = 0; // 存放鼠标旋转总共的度数
            //     var count = 0;
            //     var mPointB = {} // 移动的B点距离
            //     var init = {
            //         count: 0
            //     }
            //     var oldTarget = {
            //         target: null,
            //         angle: 0
            //     }
            //     // 元素跟随鼠标移动旋转拉伸
            //     $("#" + rectname).css("cursor", "se-resize")
            //     pointA.X = $("#" + rectname).width() / 2 + $("#" + rectname).offset().left + parseInt($("#" + rectname).css("border-width"))
            //     pointA.Y = $("#" + rectname).height() / 2 + $("#" + rectname).offset().top + parseInt($("#" + rectname).css("border-width"))
            //     // 计算两个旋转方块之间的角度
            //     var tanA = $("#" + rectname).width() / $("#" + rectname).height()
            //     var d = Math.round(Math.atan(tanA) * 180 / Math.PI)
            //     if (oldTarget.target && oldTarget.target != e.currentTarget) {
            //         if (e.currentTarget == $('.rotate')[0]) {
            //             oldTarget.angle = 2 * d
            //         } else {
            //             oldTarget.angle = -2 * d
            //         }
            //     } else {
            //         oldTarget.angle = 0
            //     }
            //     typeMouse = true; //获取起始点坐标
            //     if (count < 1) { // 以鼠标第一次落下的点为起点
            //         pointB.X = e.pageX;
            //         pointB.Y = e.pageY;
            //         init.count = 0
            //         oldTarget.target = e.currentTarget // 储存第一次落下的旋转区域
            //         count++
            //     }
            //     if (mPointB.flag) { // 如果移动后,元素的B点也需要加上平移的距离
            //         pointB.X += mPointB.X
            //         pointB.Y += mPointB.Y
            //         mPointB.flag = false
            //         init.count = 0
            //       }
            //       console.log(5, pointA, pointB)
            //       $(document).on('mousemove', function (e) {
            //         e.preventDefault()
            //         if (typeMouse) {
            //           pointC.X = e.pageX;
            //           pointC.Y = e.pageY; // 获取结束点坐标
            //           // 计算每次移动元素的半径变化,用作拉伸
            //           var scalX1 = pointB.X - pointA.X
            //           var scalY1 = pointB.Y - pointA.Y
            //           var scalX = pointC.X - pointA.X
            //           var scalY = pointC.Y - pointA.Y
              
            //           // 计算出旋转角度
            //           var AB = {};
            //           var AC = {};
            //           AB.X = (pointB.X - pointA.X);
            //           AB.Y = (pointB.Y - pointA.Y);
            //           AC.X = (pointC.X - pointA.X);
            //           AC.Y = (pointC.Y - pointA.Y); // 分别求出AB,AC的向量坐标表示
            //           var direct = (AB.X * AC.Y) - (AB.Y * AC.X); // AB与AC叉乘求出逆时针还是顺时针旋转
            //           var lengthAB = Math.sqrt(Math.pow(pointA.X - pointB.X, 2) +
            //               Math.pow(pointA.Y - pointB.Y, 2)),
            //             lengthAC = Math.sqrt(Math.pow(pointA.X - pointC.X, 2) +
            //               Math.pow(pointA.Y - pointC.Y, 2)),
            //             lengthBC = Math.sqrt(Math.pow(pointB.X - pointC.X, 2) +
            //               Math.pow(pointB.Y - pointC.Y, 2));
            //           var cosA = (Math.pow(lengthAB, 2) + Math.pow(lengthAC, 2) - Math.pow(lengthBC, 2)) /
            //             (2 * lengthAB * lengthAC); //   余弦定理求出旋转角
            //           var angleA = Math.round(Math.acos(cosA) * 180 / Math.PI);
            //           if (direct < 0) {
            //             allA = -angleA; //叉乘结果为负表示逆时针旋转， 逆时针旋转减度数
            //           } else {
            //             allA = angleA; //叉乘结果为正表示顺时针旋转，顺时针旋转加度数
            //           }
              
            //           allA += oldTarget.angle
            //           // $('.img-box').css('transform', 'rotate('+allA+'deg)')
              
            //           // 计算出拉伸比例
            //           var sa = Math.sqrt(scalX1 * scalX1 + scalY1 * scalY1)
            //           var ss = Math.sqrt(scalX * scalX + scalY * scalY)
            //           var sc = ss / sa
            //           // console.log(allA, sc)
            //           $('.img-box').css('transform', 'rotate('+allA+'deg) scale('+sc+')')
            //         }
            //       });

            //     //end else if
            // }

        })
        var pointA = { // 元素中心点 元素1/2自身宽高 + 元素的定位
            X: $("#" + rectname).width() / 2 + $("#" + rectname).offset().left+parseInt($("#" + rectname).css("border-width")),
            Y: $("#" + rectname).height() / 2 + $("#" + rectname).offset().top+parseInt($("#" + rectname).css("border-width"))
          };
          console.log(pointA, $("#" + rectname).position())
        
          var pointB = {};
          var pointC = {}; // A,B,C分别代表中心点，起始点，结束点坐标
          // 这里通过鼠标的移动获取起始点和结束点
          var typeMouse = false;
          var allA = 0; // 存放鼠标旋转总共的度数
          var count = 0;
          var mPointB = {} // 移动的B点距离
          var init = {
            count: 0
          }
          var oldTarget = {
            target: null,
            angle: 0
          }
        $(".rotate").on('mousedown', function (e) {
            e.preventDefault()
            e.stopPropagation()
            // 计算两个旋转方块之间的角度
            var tanA = $("#" + rectname).width() / $("#" + rectname).height()
            var d = Math.round(Math.atan(tanA) * 180 / Math.PI)
        // 　　// 如果当前旋转的区域与上一次旋转的区域不一致,需要加上这两个区域之间的角度差2*tanA,这里我只有两个旋转区域,如果有多个区域,需要分别判断
        //     if (oldTarget.target && oldTarget.target != e.currentTarget) {
        //       if (e.currentTarget == $('.rotate')[0]) {
        //         oldTarget.angle = 2 * d
        //       } else {
        //         oldTarget.angle = -2 * d
        //       }
        //     } else {
        //       oldTarget.angle = 0
        //     }
            typeMouse = true; //获取起始点坐标
            if (count < 1) { // 以鼠标第一次落下的点为起点
              pointB.X = e.pageX;
              pointB.Y = e.pageY;
              init.count = 0
              oldTarget.target = e.currentTarget // 储存第一次落下的旋转区域
              count++
            }
            if (mPointB.flag) { // 如果移动后,元素的B点也需要加上平移的距离
              pointB.X += mPointB.X
              pointB.Y += mPointB.Y
              mPointB.flag = false
              init.count = 0
            }
            console.log(5, pointA, pointB)
        
            $(document).on('mousemove', function (e) {
              e.preventDefault()
              if (typeMouse) {
                pointC.X = e.pageX;
                pointC.Y = e.pageY; // 获取结束点坐标
                // 计算每次移动元素的半径变化,用作拉伸
                var scalX1 = pointB.X - pointA.X
                var scalY1 = pointB.Y - pointA.Y
                var scalX = pointC.X - pointA.X
                var scalY = pointC.Y - pointA.Y
        
                // 计算出旋转角度
                var AB = {};
                var AC = {};
                AB.X = (pointB.X - pointA.X);
                AB.Y = (pointB.Y - pointA.Y);
                AC.X = (pointC.X - pointA.X);
                AC.Y = (pointC.Y - pointA.Y); // 分别求出AB,AC的向量坐标表示
                var direct = (AB.X * AC.Y) - (AB.Y * AC.X); // AB与AC叉乘求出逆时针还是顺时针旋转
                var lengthAB = Math.sqrt(Math.pow(pointA.X - pointB.X, 2) +
                    Math.pow(pointA.Y - pointB.Y, 2)),
                  lengthAC = Math.sqrt(Math.pow(pointA.X - pointC.X, 2) +
                    Math.pow(pointA.Y - pointC.Y, 2)),
                  lengthBC = Math.sqrt(Math.pow(pointB.X - pointC.X, 2) +
                    Math.pow(pointB.Y - pointC.Y, 2));
                var cosA = (Math.pow(lengthAB, 2) + Math.pow(lengthAC, 2) - Math.pow(lengthBC, 2)) /
                  (2 * lengthAB * lengthAC); //   余弦定理求出旋转角
                var angleA = Math.round(Math.acos(cosA) * 180 / Math.PI);
                if (direct < 0) {
                  allA = -angleA; //叉乘结果为负表示逆时针旋转， 逆时针旋转减度数
                } else {
                  allA = angleA; //叉乘结果为正表示顺时针旋转，顺时针旋转加度数
                }
        
                allA += oldTarget.angle
                // $('.img-box').css('transform', 'rotate('+allA+'deg)')
        
                // 计算出拉伸比例
                var sa = Math.sqrt(scalX1 * scalX1 + scalY1 * scalY1)
                var ss = Math.sqrt(scalX * scalX + scalY * scalY)
                var sc = ss / sa
                // console.log(allA, sc)
                $("#" + rectname).css('transform', 'rotate('+allA+'deg) scale('+sc+')')
              }
            });
          });
          $(document).on('mouseup', function (e) {
            typeMouse = false;
            moveMouse = false
          });
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
        $("#" + circlename).mousedown(function (event) {
            deltax = event.clientX - $(this).offset().left //鼠标距离上半弧的距离
            deltay = event.clientY - $(this).offset().top   //鼠标距离左半弧的距离
            circleMoving = true
            $(document).bind('mousemove', function (event) {
                if (circleMoving) {
                    x = event.clientX - deltax//距离左边的位置
                    y = event.clientY - deltay//距离上边的位置
                    centerX = x + radius
                    centerY = y + radius
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
                }
            })
            $(document).bind('mouseup', function (event) {
                circleMoving = false
            })
        })
        var pointA = {//中心点坐标
            X: $("#" + circlename).width() / 2 + $("#" + circlename).offset().left,
            Y: $("#" + circlename).height() / 2 + $("#" + circlename).offset().top
        }
        console.log(pointA)
        var pointB = {}//起始点坐标
        var pointC = {}//结束点坐标
        //鼠标获取起始点和结束点
        var typeMouse = false

        var allA = 0//存放鼠标旋转总度数
        var count = 0
        //元素跟着鼠标移动旋转
        $("#" + circlename).mousedown(function (event) {
            event.preventDefault()
            event.stopPropagation()

            typeMouse = true
            if (count < 1) {//以鼠标第一次落下的点为起点
                pointB.X = event.pageX
                pointB.Y = event.pageY
                count++
            }
            console.log(5, pointA, pointB)
            $(document).on("mousemove", function (e) {
                e.preventDefault()
                if (typeMouse) {
                    pointC.x = e.pageX
                    pointC.y = e.pageY//获取结束点坐标
                    // 计算出旋转角度
                    var AB = {}
                    var AC = {}
                    AB.X = (pointB.X - pointA.X)
                    AB.Y = (pointB.Y - pointA.Y)
                    AC.X = (pointC.X - pointA.X)
                    AC.Y = (pointC.Y - pointA.Y)//分别求出AB，AC的向量坐标表示
                    var direct = (AB.X * AC.Y) - (AB.Y * AC.X)//AB，AC的向量坐标显示
                    var lengthAB = Math.sqrt(Math.pow(pointA.X - pointB.X, 2) +
                        Math.pow(pointA.Y - pointB.Y, 2)),
                        lengthAC = Math.sqrt(Math.pow(pointA.X - pointC.X, 2) +
                            Math.pow(pointA.Y - pointC.Y, 2)),
                        lengthBC = Math.sqrt(Math.pow(pointB.X - pointC.X, 2) +
                            Math.pow(pointB.Y - pointC.Y, 2));
                    var cosA = (Math.pow(lengthAB, 2) + Math.pow(lengthAC, 2) - Math.pow(lengthBC, 2)) /
                        (2 * lengthAB * lengthAC);
                    var angleA = Math.round(Math.acos(cosA) * 180 / Math.PI)
                    if (direct < 0) {
                        allA = -angleA//叉乘结果为负表示逆时针旋转 逆时针旋转减度数
                    } else {
                        allA = angleA//叉乘结果为正表示顺时针旋转 顺时针旋转加度数
                    }
                    console.log(allA)
                    $("#" + circlename).css('transform', 'rotate(' + allA + 'deg)')
                }
            })
            $(document).on("mouseup", function (e) {
                typeMouse = false
            })
        })
    })
})
        // console.log(pointA)
        // var pointB = {}//起始点坐标
        // var pointC = {}//结束点坐标
        // //鼠标获取起始点和结束点
        // var typeMouse = false

        // var allA = 0//存放鼠标旋转总度数
        // var count = 0
        // //元素跟着鼠标移动旋转
        // $("#" + rectname).mousedown(function (event) {
        //     event.preventDefault()
        //     event.stopPropagation()
        //     $point = $('<div id="point" style="width:10px; height:10px;background-color: red;display:flex">123123123</div>');
        //     $draw.append($point);
        //     $point.css({ 'left': pointA.X + 'px', 'top': pointA.Y + 'px' })
        //     typeMouse = true
        //     if (count < 1) {//以鼠标第一次落下的点为起点
        //         pointB.X = event.pageX
        //         pointB.Y = event.pageY
        //         count++
        //     }
        //     $(document).on("mousemove", function (e) {
        //         e.preventDefault()
        //         if (typeMouse) {
        //             pointC.X = e.pageX
        //             pointC.Y = e.pageY//获取结束点坐标
        //             // 计算出旋转角度
        //             var AB = {}
        //             var AC = {}
        //             console.log(5, pointA, pointB, pointC)
        //             AB.X = (pointB.X - pointA.X)
        //             AB.Y = (pointB.Y - pointA.Y)
        //             AC.X = (pointC.X - pointA.X)
        //             AC.Y = (pointC.Y - pointA.Y)//分别求出AB，AC的向量坐标表示
        //             console.log("4535", AB.X, AB.Y, AC.X, AC.Y)
        //             var direct = (AB.X * AC.Y) - (AB.Y * AC.X)//AB，AC的向量坐标显示
        //             var lengthAB = Math.sqrt(Math.pow(pointA.X - pointB.X, 2) +
        //                 Math.pow(pointA.Y - pointB.Y, 2)),
        //                 lengthAC = Math.sqrt(Math.pow(pointA.X - pointC.X, 2) +
        //                     Math.pow(pointA.Y - pointC.Y, 2)),
        //                 lengthBC = Math.sqrt(Math.pow(pointB.X - pointC.X, 2) +
        //                     Math.pow(pointB.Y - pointC.Y, 2));
        //             var cosA = (Math.pow(lengthAB, 2) + Math.pow(lengthAC, 2) - Math.pow(lengthBC, 2)) /
        //                 (2 * lengthAB * lengthAC);
        //             var angleA = Math.round(Math.acos(cosA) * 180 / Math.PI)
        //             console.log("angleA" + angleA)
        //             if (direct < 0) {
        //                 allA = -angleA//叉乘结果为负表示逆时针旋转 逆时针旋转减度数
        //             } else {
        //                 allA = angleA//叉乘结果为正表示顺时针旋转 顺时针旋转加度数
        //             }
        //             console.log("---" + allA)
        //             $("#" + rectname).css('transform', 'rotate(' + allA + 'deg)')
        //         }
        //     })
        //     $(document).on("mouseup", function (e) {
        //         typeMouse = false
        //         $point.remove()
        //     })
        // })

/***************************************************圆****************************************************** */
