String.prototype.repeat = function(count) {
    if (count < 1) return '';
    var result = '', pattern = this.valueOf();
    while (count > 0) {
        if (count & 1) result += pattern;
        count >>= 1, pattern += pattern;
    }
    return result;
};

var canvasSize;
var canvasPos;
var XList;
var YList;
var PList;
var iList;
var LastX;
var LastY;
var capturing;
//var EngineX;
//var EngineY;
var stepDist = 0.5;   // constant for LinearBrush
var paintDist = 1.0;
var dotNumber = 20;
function colorToHex(red,green,blue) {
    var rgb = blue | (green << 8) | (red << 16);
    var s = rgb.toString(16);
    if (s.length < 6) s = "0".repeat(6- s.length) + s;
    return '#' + s;
};
function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? [
        parseInt(result[1], 16),
        parseInt(result[2], 16),
        parseInt(result[3], 16)
    ] : null;
}
function rgbToHsv(r,g,b)
{
    var rr = r/255.0, gg = g/255.0, bb = b/255.0, h, s, v=Math.max(rr,gg,bb),
        dif = v - Math.min(rr,gg,bb);
    if(dif == 0 )
    {
        h = s = 0;
    }
    else
    {
        if(v==0) s = 0 ; else s = dif / v;
        if(v==rr)
            h = (gg-bb)/v * 60;
        else if(v==gg)
            h = (bb-rr)/v * 60 + 120 ;
        else h = (rr-gg)/v * 60 + 240;
        if(h<0) h+=360;
        if(h>360) h-=360;
    }
    return [h,s,v];
}
function hsvToRGB(h,s,v)
{
  if(s==0.0) return [v,v,v];
  var h1 = parseInt(h*360), v1 = v * 255.0,
      hi = parseInt(h/60),
      f = h / 60.0 - hi,
      p = v1 * (1-s),
      q = v1 * (1 - f * s),
      t = v1 * (1 - (1 - f)*s);
  //console.log(hi);
  switch(hi)
  {
      case 0: return [v1,t,p];
      case 1: return [q,v1,p];
      case 2: return [p,v1,t];
      case 3: return [p,q,v1];
      case 4: return [t,p,v1];
      default : return [v1,p,q];
  }
}
function findPos(obj)
{
    var curleft = curtop = 0;
    if (obj.offsetParent)
    {
        curleft = obj.offsetLeft
        curtop = obj.offsetTop
        while (obj = obj.offsetParent)
        {
            curleft += obj.offsetLeft
            curtop += obj.offsetTop
        }
    }
    return {x:curleft, y:curtop};
}
function refresh() {
    //EngineX = window.event.pageX;
    //EngineY = window.event.pageY;
    Canvas.mousemove(window.event);
}
function runUpdateThread(){
    refresh();
    if(capturing)
        window.setTimeout(runUpdateThread(),3000);
}
var Eraser = {
    size: 10,
    opacity: 1.0,
    context: null,
    brushNo: 2,
    getready: function(){},
    done: function(){},
    updatePattern: function(ctx){
        ctx.beginPath();
        ctx.strokeStyle = "rgba(" + colors[0] + "," + colors[1] + "," + colors[2] + "," + this.opacity + ")";
        ctx.arc(25, 20, this.size / 2, 0, 2 * Math.PI);
        ctx.stroke();
    },
    render: function(ctx, pattern, curX, curY, pressure, lastX, lastY, GlobalSettings, lastP, size, opacity)
    {
        if(size == undefined)size = this.size;
        if(opacity == undefined)opacity = this.opacity

        var dist = Math.sqrt((curX-lastX)*(curX-lastX)+(curY-lastY)*(curY-lastY));
        var numStep = dist / stepDist;
        var xStep = (curX-lastX)/numStep, yStep = (curY - lastY)/numStep;
        ctx.beginPath();
        ctx.moveTo(lastX, lastY);
        var xTemp = lastX, yTemp = lastY;

        if(GlobalSettings.wacomSize) ctx.lineWidth = size * pressure;
        else ctx.lineWidth = size;

        var curOpa = opacity * 0.4;
        if(GlobalSettings.wacomOpacity) curOpa = curOpa * pressure;

        ctx.strokeStyle = "rgba(255, 255, 255,"+ curOpa + ")";

        for(i=0;i<numStep;++i)
        {
            xTemp += xStep;
            yTemp += yStep;
            ctx.lineTo(xTemp, yTemp);
            ctx.stroke();
            ctx.beginPath();
            ctx.moveTo(xTemp, yTemp);
        }
        ctx.lineTo(curX, curY);
        ctx.stroke();
    }
};
var PaintBrush = {
    size: 10,
    opacity: 1.0,
    contex: null,
    brushNo: 1,
    updatePattern: function(ctx){
        var grad = ctx.createRadialGradient(25, 20, 0, 25,20, this.size / 2);
        grad.addColorStop(0, 'rgba('+ colors[0] +','+ colors[1] + ','+colors[2]+','+ this.opacity +')');
        grad.addColorStop(1, 'rgba('+ colors[0] +','+ colors[1] + ','+colors[2]+',0)');
        ctx.fillStyle = grad;
        ctx.beginPath();
        ctx.arc(25,20, this.size / 2, 0, 2 * Math.PI);
        ctx.fill();
    },
    getready: function(){
        //this.patternImageData = Canvas.getPattern().getContext('2d')
        //     .getImageData(25-this.size/2, 20-this.size/2, this.size, this.size);
    },
    done: function(){},
    render: function(ctx, pattern, curX, curY, pressure, lastX, lastY, GlobalSettings, lastP, size, opacity)
    {
        if(size == undefined)size = this.size;
        if(opacity == undefined)opacity = this.opacity

        var dist = Math.sqrt((curX-lastX)*(curX-lastX)+(curY-lastY)*(curY-lastY));
        var numStep = dist / paintDist;
        var xStep = (curX-lastX)/numStep, yStep = (curY - lastY)/numStep;
        //ctx.beginPath();
        //ctx.moveTo(lastX, lastY);
        var xTemp = lastX, yTemp = lastY;

        if(GlobalSettings.wacomSize) ctx.lineWidth = size * pressure;
        else ctx.lineWidth = size;

        var curOpa = opacity * 0.1;
        if(GlobalSettings.wacomOpa) curOpa = curOpa * pressure;

        //

        //ctxx = $('#pattern')[0].getContext('2d');
        ctxx = pattern.getContext('2d');
        ctxx.clearRect(0,0,50,40);
        var grad = ctxx.createRadialGradient(25, 20, 0, 25,20, ctx.lineWidth / 2);
        grad.addColorStop(0, 'rgba('+ GlobalSettings.colors[0] +','+ GlobalSettings.colors[1] + ','+GlobalSettings.colors[2]+','+ curOpa +')');
        grad.addColorStop(1, 'rgba('+ GlobalSettings.colors[0] +','+ GlobalSettings.colors[1] + ','+GlobalSettings.colors[2]+',0)');
        ctxx.fillStyle = grad;
        ctxx.beginPath();
        ctxx.arc(25,20, ctx.lineWidth / 2, 0, 2 * Math.PI);
        ctxx.fill();

        //console.log(pressure);

        //console.log(pattern);
        //var pat = ctx.createPattern(pattern,"repeat");

        //ctx.strokeStyle = pat;

        for(i=0;i<numStep;i++)
        {
            xTemp += xStep;
            yTemp += yStep;
            //ctx.lineTo(xTemp, yTemp);
            //ctx.putImageData(this.patternImageData, xTemp, yTemp);
            //console.log(xTemp-25,yTemp-20);
            //console.log(pattern);
            ctx.drawImage(pattern, xTemp-25, yTemp-20);

            //ctx.stroke();
            //ctx.beginPath();
            //ctx.moveTo(xTemp, yTemp);
        }

        //ctx.lineTo(curX, curY);
        //ctx.stroke();
    }
};
var LinearBrush = {
    size: 10,
    opacity: 1.0,
    context: null,
    brushNo: 0,
    getready: function(){},
    done: function(){},
    updatePattern: function(ctx){
        ctx.beginPath();
        ctx.fillStyle = "rgba(" + colors[0] + "," + colors[1] + "," + colors[2] + "," + this.opacity + ")";
        ctx.arc(25, 20, this.size / 2, 0, 2 * Math.PI);
        ctx.fill();
    },
    render: function(ctx, pattern, curX, curY, pressure, lastX, lastY, GlobalSettings, lastP, size, opacity)
    {
        if(size == undefined)size = this.size;
        if(opacity == undefined)opacity = this.opacity

        var dist = Math.sqrt((curX-lastX)*(curX-lastX)+(curY-lastY)*(curY-lastY));
        var numStep = dist / stepDist;
        var xStep = (curX-lastX)/numStep, yStep = (curY - lastY)/numStep;
        ctx.beginPath();
        ctx.moveTo(lastX, lastY);
        var xTemp = lastX, yTemp = lastY;

        var pressureStep = (pressure - lastP)/numStep, lineWidthStep, opaStep, curlineWidth, curOpa;

        if(GlobalSettings.wacomSize)
        {
            curlineWidth = size * pressure;
            lineWidthStep = size * pressureStep;
        }
        else
        {
            curlineWidth = size;
            lineWidthStep = 0;
        }

        if(GlobalSettings.wacomOpacity)
        {
            curOpa = opacity * pressure;
            opaStep = opacity * pressureStep;

        }
        else
        {
            curOpa = opacity;
            opaStep = 0;
        }
        //console.log(pressure);

        //ctx.strokeStyle = "rgba(" + colors[0] + "," + colors[1] + "," + colors[2] + "," + curOpa*stepDist/(ctx.lineWidth) + ")";


        for(i=0;i<numStep;i++)
        {
            xTemp += xStep;
            yTemp += yStep;
            ctx.lineTo(xTemp, yTemp);
            ctx.lineWidth = curlineWidth - (numStep-i)*lineWidthStep;
            ctx.strokeStyle = "rgba(" + GlobalSettings.colors[0] + "," + GlobalSettings.colors[1] + "," + GlobalSettings.colors[2] + "," + (curOpa - (numStep-i)*opaStep)*stepDist/(ctx.lineWidth) + ")";

            ctx.stroke();
            ctx.beginPath();
            ctx.moveTo(xTemp, yTemp);
        }
        ctx.lineWidth = curlineWidth;
        ctx.strokeStyle = "rgba(" + GlobalSettings.colors[0] + "," + GlobalSettings.colors[1] + "," + GlobalSettings.colors[2] + "," + (curOpa)*stepDist/(ctx.lineWidth) + ")";

        ctx.lineTo(curX, curY);
        ctx.stroke();
    }
};
var ColorPicker = {
    size: 10,
    opacity: 1.0,
    context: null,
    brushNo: 30,
    notInHistory: true,
    getready: function(){},
    done: function(){},
    updatePattern: function(ctx){
    },
    render: function(ctx, pattern, curX, curY, pressure, lastX, lastY, GlobalSettings, lastP, size, opacity)
    {
        var p = ctx.getImageData(curX, curY, 1, 1).data;
        //if(p[3]==0) colors = [255,255,255];
        //else
        if(p[0]==0 && p[1] == 0 && p[2] == 0 && p[3] == 0)
        {
            colors = [255,255,255];
            updateOpa(1);
        }
        else
        {
            colors[0] = p[0];
            colors[1] = p[1];
            colors[2] = p[2];
            updateOpa(p[3] / 255.0);
            //console.log(p / 255.0);
        }
        $('#colorvalue').css('background', 'rgb('+colors[0]+','+colors[1]+','+colors[2]+')')
            .css('color', 'rgb('+(255-colors[0])+','+(255-colors[1])+','+(255-colors[2])+')')
            .val(colorToHex(colors[0], colors[1], colors[2]))
            .trigger('keyup');
        //updatePattern();
    }
};
var QuadraticBrush = {
    size: 10,
    opacity: 1.0,
    context: null,
    getready: function(){},
    done: function(){},
    brushNo:3,
    updatePattern: function(ctx){},
    render: function(ctx, pattern, curX, curY, pressure, lastX, lastY, GlobalSettings, lastP, size, opacity)
    {
        if(size == undefined)size = this.size;
        if(opacity == undefined)opacity = this.opacity

        //var dist = Math.sqrt((curX-lastX)*(curX-lastX)+(curY-lastY)*(curY-lastY));
        //var numStep = dist / stepDist;
        //var xStep = (curX-lastX)/numStep, yStep = (curY - lastY)/numStep;
        var x3 = XList[iList-1] * 2 - XList[iList-2], y3 = YList[iList-1]*2 - YList[iList-2];

        ctx.beginPath();
        ctx.moveTo(lastX, lastY);
        //var xTemp = lastX, yTemp = lastY;
        var stepLength = 1.0/dotNumber;
        var xTemp = lastX, yTemp = lastY;

        if(GlobalSettings.wacomSize) ctx.lineWidth = size * pressure;
        else ctx.lineWidth = size;

        var curOpa = opacity;
        if(GlobalSettings.wacomOpa) curOpa = curOpa * pressure;

        ctx.strokeStyle = "rgba(" + colors[0] + "," + colors[1] + "," + colors[2] + "," + curOpa * stepDist/(ctx.lineWidth) + ")";

        for(i=0;i<1;i+=stepLength)
        {
            xTemp = lastX + (x3-lastX)*i + i*(x3-lastX+(lastX+curX-2*x3)*i);
            yTemp = lastY + (y3-lastY)*i + i*(y3-lastY+(lastY+curY-2*y3)*i);

            //xTemp += (x3-lastX+i*(lastX+curX-2*x3))*2*stepLength - (lastX+curX-2*x3)*stepLength*stepLength;
            //yTemp += (y3-lastY+i*(lastY+curY-2*y3))*2*stepLength - (lastY+curY-2*y3)*stepLength*stepLength;
            ctx.lineTo(xTemp, yTemp);
            ctx.stroke();
            ctx.beginPath();
            ctx.moveTo(xTemp, yTemp);
        }

        ctx.lineTo(curX, curY);
        ctx.stroke();
    }
};
var WTablet = {
    getPlugin: function(){ return document.getElementById('wtPlugin');},
    getPenAPI: function(){ return this.getPlugin().penAPI; }
};
var Canvas = {
    AccurateEngine: false,
    getLayers: function(){ return this.layers },
    getPattern: function(){ return this.pattern },
    getUpperLayer: function() {return this.upperLayer },
    brushList:[LinearBrush, PaintBrush, Eraser, ColorPicker],
    brushMap:{},
    setBrush: function(brush) {
        updateSize(brush.size);
        updateOpa(brush.opacity);
        return (this.currentBrush = brush);
    },
    loadBrush:function(){
        for(var i=0;i<this.brushList.length; ++i)
        {
            this.brushMap[this.brushList[i].brushNo] = this.brushList[i];  // Double Mapping
        }
    },
    init: function(layers, pattern, upperCanvas, container){
        this.layers = layers;
        this.layerContext = this.layers[0].getContext('2d');
        this.layerContext.lineCap = 'round';
        this.pattern = pattern;
        this.upperLayer = upperCanvas;
        upperCanvas.getContext('2d').lineCap = 'round';
        //this.upperContext = upperCanvas.getContext('2d');
        canvasSize = {width: $(layers[0]).width(), height: $(layers[0]).height() };
        canvasPos = findPos(this.layers[0]);
        capturing = false;
        XList = YList = []; iList = 0;
        this.container = container;
        this.currentBrush = LinearBrush;
        this.loadBrush();
        return this;
    },
    inCanvasBounds: function(x,y){
        var left = 0;
        var top = 0;
        var right = canvasSize.width;
        var bottom = canvasSize.height;

        return ( x >= left && x <= right &&
            y >= top && y <= bottom);
    },
    renderHistory: function(msgObj){
        var ctx = Canvas.getUpperLayer().getContext('2d');
        ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
        // # TODO: Multi Layer Support
        //if(msgObj.XList)msgObj.XList.unshift(msgObj.XList[0]);
        //if(msgObj.YList)msgObj.YList.unshift(msgObj.YList[0]);
        //if(msgObj.PList)msgObj.PList.unshift(msgObj.PList[0]);
        console.log(msgObj);
        for(var i = 2; i< msgObj.XList.length; ++i)
        {
            var tmpCTX = $('#temppattern')[0].getContext('2d');
            Canvas.brushMap[msgObj.brushNo].updatePattern(tmpCTX);
            Canvas.brushMap[msgObj.brushNo].render(ctx, $('#temppattern')[0],
                msgObj.XList[i], msgObj.YList[i], msgObj.PList[i],
                msgObj.XList[i-1], msgObj.YList[i-1],
                msgObj, msgObj.PList[i-1],
                msgObj.size, msgObj.opacity);
        }
        Canvas.layerContext.drawImage(Canvas.getUpperLayer(), 0, 0);
    },
    mousemove: function (evt)
    {
        if(!capturing) return ;
        // Non-IE browsers will use evt
        var ev = evt || window.event;


        var canvas = Canvas.getLayers()[0];
        var pressure = 1.0;
        var isEraser;

        //if (penAPI && penAPI.isWacom )
        if(GlobalSettings.wacomSupport)
        {
            var penAPI = WTablet.getPenAPI();
            if(penAPI)
            {
                pressure = penAPI.pressure;
            }
        }
        curX = (ev.pageX?ev.pageX : ev.clientX + document.body.scrollLeft) + Canvas.container.scrollLeft - canvasPos.x;
        curY = (ev.pageY?ev.pageY : ev.clientY + document.body.scrollTop) + Canvas.container.scrollTop - canvasPos.y;


        capturing = Canvas.inCanvasBounds(curX, curY);

        if (capturing && pressure > 0.0)
        {
            if (canvas.getContext)
            {
                var ctx = Canvas.layerContext;
                //LinearBrush.render(ctx, curX, curY, pressure);
                XList.push(curX); YList.push(curY); PList.push(pressure); ++iList;

                Canvas.currentBrush.render(ctx, Canvas.getPattern(), curX, curY, pressure, lastX, lastY, GlobalSettings, PList[iList-1]);
            }
        }

        lastX = curX;
        lastY = curY;

    },
    mousedown: function(evt){
        var ev = evt || window.event;

        var canvas = Canvas.getLayers()[0];
        //canvas.onmousemove=Canvas.mousemove;

        GlobalSettings = updateGlobalSettings();

        lastX = (ev.pageX?ev.pageX : ev.clientX + document.body.scrollLeft) + Canvas.container.scrollLeft - canvasPos.x;
        lastY = (ev.pageY?ev.pageY : ev.clientY + document.body.scrollTop ) + Canvas.container.scrollTop - canvasPos.y;
        XList = [lastX,lastX];
        YList = [lastY,lastY];
        PList = [0.0,0.0];
        iList = 1;
        capturing = Canvas.inCanvasBounds(lastX, lastY);

        if(Canvas.AccurateEngine)runUpdateThread();
        // Register click immediately
        else Canvas.mousemove(evt);

        if(Canvas.currentBrush.getready)
            Canvas.currentBrush.getready();
    },
    mouseup: function(evt) {

        capturing = false;
        //Canvas.upperLayer.clearRect(0,0,)
        if(Canvas.currentBrush.done)
            Canvas.currentBrush.done();
        if(Canvas.currentBrush.notInHistory == undefined)
            sendPackage(GlobalSettings, XList, YList, PList);
    },
    registerEvent: function(){
        $(this.layers[0]).bind('mouseup',this.mouseup).bind('mousedown',this.mousedown);
        if (!Canvas.AccurateEngine) $(this.layers[0]).bind('mousemove',this.mousemove);
        else refresh();
    }
}