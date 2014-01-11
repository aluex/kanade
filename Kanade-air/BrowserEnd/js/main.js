var userName;
var cw;
var colors;
var hsvColors;
var Slider_Size;
var Slider_Opa;
var Slider_R;
var Slider_G;
var Slider_B;
var Slider_H;
var Slider_S;
var Slider_V;
var GlobalSettings;
var updateGlobalSettings = function() {
    var settings = {};
    settings.wacomSupport = $('#wacom-support').prop('checked');
    settings.wacomOpacity = settings.wacomSupport && $('#wacom-opacity').hasClass('active');
    settings.wacomSize = settings.wacomSupport && $('#wacom-size').hasClass('active');
    settings.colors = colors;
    settings.currentBrush = Canvas.currentBrush;
    settings.userName = userName;
    GlobalSettings = settings;
    return settings;
};
var updatePattern = function() {
    updateGlobalSettings();

    var ctx = $('#pattern')[0].getContext('2d');
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

    GlobalSettings.currentBrush.updatePattern(ctx);

};
var updateSize = function(size){
    Slider_Size.setValue(size);
};
var updateOpa = function(opa){
    Slider_Opa.setValue(parseInt(opa * 100));
};
var sizeSliderChange = function(){
    Canvas.currentBrush.size = Slider_Size.getValue();
    updatePattern();
};
var opaSliderChange = function(){
    Canvas.currentBrush.opacity = Slider_Opa.getValue() / 100.0;
    updatePattern();
};
$(document).ready(function(){

    userName = 'user' + parseInt(Math.random() * 5000);

    updateStatus('Loading...');

    $('#wacom-support').bootstrapSwitch();
    $('#wacom-support').on('switch-change',function(e, data){
        if(data.value == true && WTablet.getPlugin().version == undefined)
        {
            $('#wacom-support').bootstrapSwitch('setState', false); return;
        }
        if(data.value){
            $('#wacom-opacity').removeAttr('disabled');
            $('#wacom-size').removeAttr('disabled');
        }
        else {
            $('#wacom-opacity').attr('disabled','disabled');
            $('#wacom-size').attr('disabled','disabled');
        }
    });

    if(WTablet.getPlugin().version == undefined)
    {
        $('#wacomNotSupported').modal();
        $('#wacom-support').bootstrapSwitch('setState', false)
            .bootstrapSwitch('setDisabled', true);  // true || false
    }

    cw = Raphael.colorwheel($("#colorwheel")[0],120);
    cw.input($('#colorvalue')[0]);
    cw.onchange(function(color)
    {
        colors = [parseInt(color.r), parseInt(color.g), parseInt(color.b)];
        hsvColors = rgbToHsv(colors[0], colors[1], colors[2]);
        //onchange_el.css("background", color.hex).text("RGB:"+colors.join(", "))
        Slider_R.setValue(colors[0]);
        Slider_G.setValue(colors[1]);
        Slider_B.setValue(colors[2]);
        Slider_H.setValue(hsvColors[0]);
        Slider_S.setValue(hsvColors[1]);
        Slider_V.setValue(hsvColors[2]);
        updatePattern();
    });
    var RGBChange = function() {
        colors = [Slider_R.getValue(), Slider_G.getValue(), Slider_B.getValue()];
        $('#colorvalue').css('background', 'rgb('+colors[0]+','+colors[1]+','+colors[2]+')')
            .css('color', 'rgb('+(255-colors[0])+','+(255-colors[1])+','+(255-colors[2])+')')
            .val(colorToHex(colors[0], colors[1], colors[2]))
            .trigger('keyup');
        updatePattern();
    };
    var HSVChange = function() {
        var rgbColor = hsvToRGB(Slider_H.getValue(), Slider_S.getValue(), Slider_V.getValue());
        colos = rgbColor;
        $('#colorvalue').css('background', 'rgb('+rgbColor[0]+','+rgbColor[1]+','+rgbColor[2]+')')
            .css('color', 'rgb('+(255-rgbColor[0])+','+(255-rgbColor[1])+','+(255-rgbColor[2])+')')
            .val(colorToHex(rgbColor[0], rgbColor[1], rgbColor[2]))
            .trigger('keyup');
        updatePattern();
    }
    Slider_Size = $('#Size').slider().on('slide', sizeSliderChange).data('slider');
    Slider_Opa = $('#Opa').slider().on('slide', opaSliderChange).data('slider');
    Slider_R = $('#R').slider()
        .on('slide', RGBChange)
        .data('slider');
    Slider_G = $('#G').slider()
        .on('slide', RGBChange)
        .data('slider');
    Slider_B = $('#B').slider()
        .on('slide', RGBChange)
        .data('slider');
    Slider_H = $('#H').slider()
        .on('slide', HSVChange)
        .data('slider');
    Slider_S = $('#S').slider()
        .on('slide', HSVChange)
        .data('slider');
    Slider_V = $('#V').slider()
        .on('slide', HSVChange)
        .data('slider');

    // Initialize Menu

    $('#menu-connect').click(function(){
        $('#dialogConnect').modal();
    });

    $('#menu-disconnect').click(function(){
        $('#dialogDisconnect').modal();
    });

    $('#sureDisconnect').click(function(){
        // #TODO: Add disconnect code.
        logout();
        updateStatus('Offline');
    });

    $('#menu-clear').click(function(){
        $('.layer').each(function(){
            ctx = this.getContext('2d');
            ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
        })
    });

    $('#menu-view').click(function(){
        var canvas = $('.layer')[0];
        var d=canvas.toDataURL("image/png");
        var w=window.open('about:blank','ImageView');
        w.document.write("<img src='"+d+"' alt='from canvas'/>");
    });

    $('#menu-export').click(function(){
        $('#dialogExportNotice').modal();
        var canvas = $('.layer')[0];
        var type='png';
        var _fixType = function(type) {
            type = type.toLowerCase().replace(/jpg/i, 'jpeg');
            var r = type.match(/png|jpeg|bmp|gif/)[0];
            return 'image/' + r;
        };

        // Code from http://www.baidufe.com/item/65c055482d26ec59e27e.html
        var image = canvas.toDataURL("image/png").replace(_fixType(type),'image/octet-stream');  // here is the most important part because if you dont replace you will get a DOM 18 exception.

        var saveFile = function(data, filename){
            var save_link = document.createElementNS('http://www.w3.org/1999/xhtml', 'a');
            save_link.href = data;
            save_link.download = filename;

            var event = document.createEvent('MouseEvents');
            event.initMouseEvent('click', true, false, window, 0, 0, 0, 0, 0, false, false, false, false, 0, null);
            save_link.dispatchEvent(event);
        };

        var filename = 'Kanade_Air' + (new Date()).getTime() + '.' + type;

        saveFile(image,filename);
    });
    $('#menu-about').click(function(){
        $('#dialogAbout').modal();
    });
    $('#menu-options').click(function(){
        $('#optionNickName').val(userName);
        $('#dialogOptions').modal();
    });

    //Initialize Dialog

    $(".disabledForm :input").attr("disabled", true);

    $('#connectMain').click(function(){
        $('#dialogConnect').modal('hide');
        //TODO: connect to main server
        connectToMainServer();
        updateStatus('Connecting...');
    });

    $('#okOption').click(function(){
        $('#dialogOptions').modal('hide');
        if($('#optionNickName').val())
            userName = $('#optionNickName').val();
    });

    $('#optionNickName').keyup(function(evt){
        if(evt.keyCode == 13)
        {
            $('#okOption').click();
        }
    });

    //Initialize Canvas
    Canvas.AccurateEngine=false;
    Canvas.init($('.layer'), $('#pattern')[0], $('.upperlayer')[0] , $('#drawing-area')[0]).registerEvent();
    Canvas.setBrush(LinearBrush);
    //Initialize Toolbox

    $('#tool-pencil').click(function(){
        Canvas.setBrush(LinearBrush);
        updatePattern();
    });
    $('#tool-brush').click(function(){
        Canvas.setBrush(PaintBrush);
        updatePattern();
    });
    $('#tool-eraser').click(function(){
        Canvas.setBrush(Eraser);
        updatePattern();
    });

    // Initialize RGB
    colors = hexToRgb($('#colorvalue').val());
    hsvColors = rgbToHsv(colors[0],colors[1],colors[2]);

    Slider_R.setValue(colors[0]);
    Slider_G.setValue(colors[1]);
    Slider_B.setValue(colors[2]);
    Slider_H.setValue(hsvColors[0]);
    Slider_S.setValue(hsvColors[1]);
    Slider_V.setValue(hsvColors[2]);
    //Initialize HSV

    //Initialize Chatroom

    $('#txtMsg').keyup(function(evt){
        if(evt.keyCode==13)
        {
            $('#btnSendMsg').click();
        }
    });

    $('#btnSendMsg').click(function(){
        if($('#txtMsg').val()!='')
        {
            sendMessage($('#txtMsg').val(), userName);
            $('#txtMsg').val('');
        }
    });

    updatePattern();
    updateStatus('Ready');
    //alert(WTablet.getPlugin().version);

    // Things to do when Entering the program
    $('#dialogConnect').modal();
});