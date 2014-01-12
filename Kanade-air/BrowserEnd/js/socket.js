/**
 * Created with JetBrains WebStorm.
 * User: aluex
 * Date: 1/10/14
 * Time: 22:53
 * To change this template use File | Settings | File Templates.
 */

var id=null;
var breathInterval = 500;
function connectToMainServer(){
    startLogin();
}

function sendPackage(gSettings, XList, YList, PList){
    if(id!=null)
    {
        var pack = {id:id};
        pack.layer = 0; // TODO: Add Multi-Layer Support
        pack.colors = colors;
        pack.size = gSettings.currentBrush.size;
        pack.opacity = gSettings.currentBrush.opacity;
        pack.brushNo = gSettings.currentBrush.brushNo;
        pack.XList = XList;
        pack.YList = YList;
        pack.PList = PList;
        pack.wacomSize = gSettings.wacomSupport && gSettings.wacomSize;
        pack.wacomOpacity = gSettings.wacomSupport && gSettings.wacomOpacity;

        sendDrawHistory(pack);
    }
}

function startLogin(){
    if(id!=null)
    {
        popNotice("You are already connected.","warn");
        return ;
    }

    $.ajax({
        url:'/login',
        type:'post',
        cache:false,
        async:false,
        dataType:'text'
    }).success(function(data){
            var retObj = JSON.parse(data);
            if(retObj.s != 'ok'|| typeof retObj.id != "number")
            {
                updateStatus('Communication Error');
            }
            else
            {
                console.log(retObj);
                id = retObj.id;
                updateStatus('Connection established');
                popNotice("You are online.","success");
            }
    }).error(function(data){
            updateStatus('Communication Error');
    });
    setTimeout(breathe, breathInterval);
}

function sendDrawHistory(pack){
    if(id!=null)
    {
        $.ajax({
            url: '/draw',
            type: 'post',
            cache: false,
            async: true,
            dataType: 'text',
            data: JSON.stringify(pack)
        }).success(function(data){
            var retObj = JSON.parse(data);
            if(retObj.s!='ok')
                updateStatus('Communication Error');
        }).error(function(){
            popNotice("Drawing history communication error!", "error");
        });
    }
    else
    {
        popNotice("You are offline.","error");
    }
}

function sendMessage(str, username)
{
    if(id!=null)
    {
        var postObj = {
            id:id,
            msg:str,
            un:username
        };
        $.ajax({
            url: '/msg',
            type: 'post',
            cache: false,
            async: true,
            dataType: 'text',
            data: JSON.stringify(postObj)
        }).success(function(){
            updateStatus('Message Sent');

        }).error(function(){
            //if(XMLHttpRequest.readyState==204)updateStatus('Message Sent');
            updateStatus('Message Failed');
        });
    }
    else
    {
        popNotice("You are offline.","error");
    }
}

function msgReceivedHandler(msgObj)
{
    switch(msgObj.msgType)
    {
        case 'msg':
            if(msgObj.username!=null)
                addMsgToChatRoom(msgObj.msgContent, msgObj.username);
            break;
        case 'history':
            // TODO: HISTORY
            // console.log('history received');
            // console.log(msgObj);
            Canvas.renderHistory(msgObj);
            break;
    }
}

function breatheCallback(data){
    //console.log(data);
    var retObj = JSON.parse(data);

    //var retObj = data;
    if(retObj.s == "ok")
    {
        var msgList = retObj.msgList;
        for(var i =0; i< msgList.length; ++i)
        {
            msgReceivedHandler(msgList[i]);
        }
    }
    else
    {
        updateStatus('Communication Error');
        id = null;
    }
}

function breathe(){
    if(id!=null)
    {
        var postObj = {id: id};
        $.ajax({
            url: '/breathe',
            type: 'post',
            cache: false,
            async: true,
            dataType: "text",
            data: JSON.stringify(postObj)
            //data: postObj
        })
        .success(breatheCallback)
        .error(function(XMLHttpRequest, textStatus, errorThrown){
            //console.log(errorThrown);
            //if(XMLHttpRequest.readyState==204)breatheCallback(XMLHttpRequest.responseText);
            //else
            updateStatus('Connection broken');

        });

        setTimeout(breathe, breathInterval);
    }
    else
    {
        popNotice("You are offline.","error");
    }
}

function logout(){
    id = null;
}
