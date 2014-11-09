import QtQuick 2.0

Rectangle
{
    id: id_qml_StockPriceChartPrice;
    width: 320
    height: 200

    // 作为Item的派生类型，我们同样可以设置它的布局与属性
    //anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    //anchors.bottom: parent.bottom;

    //new Date()初始化得到的是当前时间
    property var m_Date_startDate: new Date();
    property var m_Date_endDate: new Date();
    //设置表格显示的时间跨度为一年
    property string activeChart: "year";

    //每个网格宽度为4px
    property int m_n_gridSize: 4
    // 网格数为（宽度 - 最右方那一栏的宽度）/ 网格宽度，如果gridSize为0，采用画布中的计算方式
    property real m_n_gridStep: m_n_gridSize ? (id_qml_StockPriceChartPrice.width - m_canvas.tickMargin) / m_n_gridSize : m_canvas.xGridStep

    ////////////////////////////////////////////////////////////////////////
    //UI
    Canvas
    {// 画布，基本上与HTML的Canvas相同
        id: m_canvas;
        // 注释介绍将下面两行语句取消注释以获得OpenGL的硬件加速渲染，为什么没有开？有些平台不支持嘛...
        // Uncomment below lines to use OpenGL hardware accelerated rendering.
        // See Canvas documentation for available options.
        //renderTarget: Canvas.FramebufferObject  // 渲染到OpenGL的帧缓冲
        //renderStrategy: Canvas.Threaded        // 渲染工作在一个私有渲染线程中进行
        property int pixelSkip: 1;
        //存储数据点的个数
        property int m_n_TotalPoints: 1;
        //右边格的宽度
        property int tickMargin: 32;

        //使用属性绑定
        //网格宽度
        property real xGridStep: (m_canvas.width - m_canvas.tickMargin) / m_canvas.m_n_TotalPoints
        //y方向向下的偏移度，用在水平线的绘制
        property real yGridOffset: height / 26
        //网格高度
        property real yGridStep: height / 12

        onPaint:
        {// 绘制入口
            if (!m_CurrentUserStockData.m_bool_ready)
            {// 等待数据完成
                return;
            }
            console.log('StockPriceChartPrice.qml',
                        ' ','onPaint:',
                        ' ','m_CurrentUserStockData.m_bool_ready:',m_CurrentUserStockData.m_bool_ready);

            // 由StockModel取得startDate到现在的数据数
            //m_canvas.m_n_TotalPoints = m_CurrentUserStockData.indexOf(id_qml_StockPriceChartPrice.m_Date_startDate);
            m_canvas.m_n_TotalPoints = m_CurrentUserStockData.count;

            /*qml: StockChart.qml   onPaint:   id_qml_StockChart.startDate: Tue Oct 15 2013   m_canvas.numPoints: 251*/
            console.log('StockPriceChartPrice.qml',' ','onPaint:',
                        ' ','id_qml_StockPriceChartPrice.m_Date_startDate:',id_qml_StockPriceChartPrice.m_Date_startDate.toDateString(),
                        ' ','m_canvas.m_n_TotalPoints:',m_canvas.m_n_TotalPoints);

            if (id_qml_StockPriceChartPrice.m_n_gridSize == 0)
            {
                //使gridStep绑定到(width - canvas.tickMargin) / numPoints上
                id_qml_StockPriceChartPrice.m_n_gridSize = m_canvas.m_n_TotalPoints
            }

            //创建ctx
            var ctx = m_canvas.getContext("2d");//object getContext(string contextId, any)
            //混合模式
            ctx.globalCompositeOperation = "source-over";
            ctx.lineWidth = 1;

            // 背景绘制
            console.log('StockPriceChartPrice.qml',' ','onPaint:', ' ','drawBackground(ctx)');
            drawBackground(ctx);


            var highestPrice = 0;
            var highestVolume = 0;
            var lowestPrice = -1;
            var points = [];// 创建一个数组
            for (var i = m_n_TotalPoints, j = 0; i >= 0 ; i -= m_canvas.pixelSkip, j += m_canvas.pixelSkip)
            {// pixelSkip被定义为 1
                var price = m_CurrentUserStockData.get(i);

                // 得到最高价
                if (parseFloat(highestPrice) < parseFloat(price.high))
                {
                    highestPrice = price.high;
                }


                if (parseInt(highestVolume, 10) < parseInt(price.volume, 10))
                {
                    highestVolume = price.volume;
                }

                // 得到最低价
                // 注意这里如果设置lowestPrice = 0或是别的数
                if (lowestPrice < 0 || parseFloat(lowestPrice) > parseFloat(price.low))
                {
                    // 就有可能一直无法满足条件，因此添加这个负数使第一个price.low被赋予lowestPrice
                    lowestPrice = price.low;
                }


                // 插入数据，它类似于Model，但多了一个 x 的坐标值
                points.push({
                                x: j * m_canvas.xGridStep,
                                open: price.open,
                                close: price.close,
                                high: price.high,
                                low: price.low,
                                volume: price.volume
                            });
            }//for

            console.log('StockPriceChartPrice.qml',' ','onPaint:', ' ','calculat points array num:', points.length);

            // 判断StockSettingPanel中相应的选项是否被勾选，然后绘制数据线段
            console.log('StockPriceChartPrice.qml',
                        ' ','onPaint:',
                        ' ','drawPrice(ctx)',
                        ' ','highestPrice:',highestPrice,
                        ' ','lowestPrice',lowestPrice,
                        ' ','m_canvas.numPoints',m_canvas.m_n_TotalPoints);
            if (settings.drawClosePrice)
            {
                drawPrice(ctx, 0, m_canvas.m_n_TotalPoints, 'red', "close", points, highestPrice, lowestPrice);
            }

            //成交量绘制
            console.log('StockPriceChartPrice.qml',
                        ' ','onPaint:',
                        ' ','drawVolume(ctx)',
                        ' ','highestVolume',highestVolume,
                        ' ','m_canvas.numPoints',m_canvas.m_n_TotalPoints);
            drawVolume(ctx, 0, m_canvas.m_n_TotalPoints, 'green', "volume", points, highestVolume);

            //价格标尺绘制
            console.log('StockPriceChartPrice.qml',
                        ' ','onPaint:',
                        ' ','drawScales(ctx)',
                        ' ','highestPrice',highestPrice,
                        ' ','lowestPrice',lowestPrice,
                        ' ','highestVolume',highestVolume);
            drawScales(ctx, highestPrice, lowestPrice, highestVolume);
        }//onPaint










        function drawBackground(ctx)
        {// 界面的绘制由onPaint开始，这是绘制背景的一个函数。ctx作为传参，类似C++中的painter
            ctx.save();// 保存之前绘制内容
            ctx.fillStyle = "#ffffff";// 填充颜色，之所以叫Style是因为它还可以使用渐变等等...
            ctx.fillRect(0, 0, m_canvas.width, m_canvas.height);  // fillRect是一个便利函数，用来填充一个矩形区域
            ctx.strokeStyle = "#d7d7d7";// 描边颜色
            ctx.beginPath();

            ////////////////////////////////////////////////////////////
            var nIndex = 0;
            var xValue1 = 0.0;
            var yValue1 = 0.0;
            var xValue2 = 0.0;
            var yValue2 = 0.0;
            console.log('StockPriceChartPrice.qml',' ','drawBackground(ctx)',
                        ' ','draw x grid',
                        ' ','grid num:',12);

            xValue1 = 0.0;
            yValue1 = 0.0;
            xValue2 = 0.0;
            yValue2 = 0.0;
            //水平网格线
            for (nIndex = 0; nIndex < 12; nIndex++)
            {
                xValue1 = 0;
                yValue1 = m_canvas.yGridOffset + nIndex * m_canvas.yGridStep;
                //ctx.moveTo(0, m_canvas.yGridOffset + i * m_canvas.yGridStep);
                ctx.moveTo(xValue1, yValue1);

                xValue2 = m_canvas.width;
                yValue2 = yValue1;
                //ctx.lineTo(m_canvas.width, m_canvas.yGridOffset + i * m_canvas.yGridStep);
                ctx.lineTo(xValue2, yValue2);
            }//水平网格线
            ////////////////////////////////////////////////////////////
            console.log('StockPriceChartPrice.qml',' ','drawBackground(ctx)',
                        ' ','draw y grid',
                        ' ','grid num:',id_qml_StockPriceChartPrice.m_n_gridSize);
            //垂直网格线
            //垂直线的高度为画布高度的 35/36
            var height = 35 * m_canvas.height / 36;
            //垂直线离顶部距离为高度的 1/36
            var yOffset = m_canvas.height - height;
            var xOffset = 0;

            xValue1 = 0.0;
            yValue1 = 0.0;
            xValue2 = 0.0;
            yValue2 = 0.0;
            for (nIndex = 0; nIndex < id_qml_StockPriceChartPrice.m_n_gridSize; nIndex++)
            {
                xValue1 = xOffset + nIndex * id_qml_StockPriceChartPrice.m_n_gridStep;
                yValue1 = yOffset;
                //ctx.moveTo(xOffset + nIndex * id_qml_StockChart.gridStep, yOffset);
                ctx.moveTo(xValue1, yOffset);
                //ctx.lineTo(xOffset + nIndex * id_qml_StockChart.gridStep, height);
                xValue2 = xValue1;
                yValue2 = height;
                ctx.lineTo(xValue2, height);
            }//垂直网格线
            ////////////////////////////////////////////////////////////
            //描线
            ctx.stroke();
            // 右方以及下方颜色较深的那几根线
            ctx.strokeStyle = "#666666";
            ctx.beginPath();
            // x = 画布宽度 - 价格部分宽度
            var xStart = m_canvas.width - tickMargin;
            ctx.moveTo(xStart, 0);
            // 向下画直线
            ctx.lineTo(xStart, m_canvas.height);
            // 12根短横线
            xValue1 = 0.0;
            yValue1 = 0.0;
            xValue2 = 0.0;
            yValue2 = 0.0;
            for (nIndex = 0; nIndex < 12; nIndex++)
            {
                xValue1 = xStart;
                yValue1 = m_canvas.yGridOffset + nIndex * m_canvas.yGridStep;
                xValue2 = m_canvas.width;
                yValue2 = m_canvas.yGridOffset + nIndex * m_canvas.yGridStep;
                //ctx.moveTo(xStart, m_canvas.yGridOffset + nIndex * m_canvas.yGridStep);
                ctx.moveTo(xValue1, yValue1);
                //ctx.lineTo(m_canvas.width, m_canvas.yGridOffset + nIndex * m_canvas.yGridStep);
                ctx.lineTo(xValue2, yValue2);
            }
            // 移动绘制点到第九根横线左端
            ctx.moveTo(0, m_canvas.yGridOffset + 9 * m_canvas.yGridStep);
            // 向右绘制横线
            ctx.lineTo(m_canvas.width, m_canvas.yGridOffset + 9 * m_canvas.yGridStep);
            // 完成路径
            ctx.closePath();
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }

        function drawScales(ctx, high, low, vol)         // 绘制右方股票价格标尺函数
        {
            ctx.save();
            ctx.strokeStyle = "#888888";
            //ctx.font = "10px Open Sans"
            //ctx.font = "10px Helvetica"
            //ctx.font = "Helvetica"
            ctx.beginPath();

            // prices on y-axis
            var x = m_canvas.width - tickMargin + 3;       // 离右边实线3px
            var priceStep = (high - low) / 9.0;          // 相隔最高价与最低价的差值除以9
            for (var i = 0; i < 10; i += 2)
            {            // 隔一级显示
                var price = parseFloat(high - i * priceStep).toFixed(1);
                ctx.text(price, x, m_canvas.yGridOffset + i * yGridStep - 2); // 绘制text的坐标在文字的左下角
            }

            // highest volume
            ctx.text(vol, 0, m_canvas.yGridOffset + 9 * yGridStep + 12);   // 绘制最高成交量

            ctx.closePath();
            ctx.stroke();
            ctx.restore();
        }

        function drawPrice(ctx, from, to, color, price, points, highest, lowest)
        {//数据曲线绘制
            // 保存之前绘制内容
            ctx.save();
            //透明度
            ctx.globalAlpha = 0.7;
            //color由StockSettingPanel指定
            ctx.strokeStyle = color;
            ctx.lineWidth = 3;
            ctx.beginPath();
            //数据长度
            var end = points.length;

            //取值范围
            var range = highest - lowest;
            if (range == 0)
            {
                //range作为被除数不能为0
                range = 1;
            }

            // 设置绘制高度为九倍的网格高度
            var h = 9 * yGridStep;//baseline 从第九格开始
            for (var nIndex = 0; nIndex < end; nIndex += m_canvas.pixelSkip)
            {
                var x = 0.0;
                var y = 0.0;
                var vCurrentValue = 0.0;
                x = points[nIndex].x;
                //取出对应设置的价格数据
                vCurrentValue = points[nIndex][price];


                // lowest - y为非正数，h + yGridOffset为曲线绘制的底部
                y = h * (lowest - vCurrentValue)/range + h + yGridOffset;

                if (nIndex == 0)
                {
                    //移动到初始点
                    ctx.moveTo(x, y);
                }
                else
                {
                    //向后绘制
                    ctx.lineTo(x, y);
                }
            }
            // 描边
            ctx.stroke();
            // 载入保存的内容
            ctx.restore();
        }

        function drawVolume(ctx, from, to, color, price, points, highest)            // 成交量绘制函数
        {
            ctx.save();
            ctx.fillStyle = color;
            ctx.globalAlpha = 0.8;
            //由于线宽影响绘制边界(参考HTML)，这里将线宽设置为0
            ctx.lineWidth = 0;
            ctx.beginPath();

            var end = points.length;
            var margin = 0;

            if (id_qml_StockPriceChartPrice.activeChart === "month" || id_qml_StockPriceChartPrice.activeChart === "week")
            {
                margin = 8;
                //x方向的阴影
                ctx.shadowOffsetX = 4;
                //模糊效果
                ctx.shadowBlur = 3.5;
                ctx.shadowColor = Qt.darker(color);
            }
                                                                                                                                                                      // 由于柱状图的宽度限制，柱状图比实际的数据少一个
            // To match the volume graph with price grid, skip drawing the initial
            // volume of the first day on chart.
            for (var i = 1; i < end; i += m_canvas.pixelSkip)
            {
                var x = points[i - 1].x;
                var y = points[i][price];
                y = m_canvas.height * (y / highest);
                y = 3 * y / 12;                               // 柱状图高度占画布的1/4
                ctx.fillRect(x, m_canvas.height - y + yGridOffset,
                             m_canvas.xGridStep - margin, y);    // "周"与"月"时有间隔，其他则没有
            }

            ctx.stroke();
            ctx.restore();
        }




















    }//Canvas
}//Rectangle


