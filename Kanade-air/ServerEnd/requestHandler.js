/**
 * Created with JetBrains WebStorm.
 * User: aluex
 * Date: 1/10/14
 * Time: 21:09
 * To change this template use File | Settings | File Templates.
 */

var idHash = {}, msgQueue = {}, countDownList = {};

var breathMaxInterval = 30000; // Stop breathing for 30000ms
var loginDurationMax = 1000;
var idMax = 1000;

function clone(obj) {
    if (null == obj || "object" != typeof obj) return obj;
    var copy = obj.constructor();
    for (var attr in obj) {
        if (obj.hasOwnProperty(attr)) copy[attr] = obj[attr];
    }
    return copy;
}

var initializeMQ = function(id)
{
    msgQueue[id] = [];
    if(id!=0)
    {
        msgQueue[id] = clone(msgQueue[0]);
    }
};

idHash[0]=true; // Room Master
initializeMQ(0);

var spreadMsg = function(id, msgObj)
{
    for(var i in idHash)
    {
        var t = parseInt(i);
        if((t != undefined) && t != id && msgQueue[i])
        {
            msgQueue[i].push(msgObj);
        }
    }
};

var responseErr = function(response)
{
    var retObj = {s:'err'};
    response.write(
        JSON.stringify(retObj)
    );
    response.end();
};

var breathe = function(request, response, postData){
    //console.log('breathe called');
    response.writeHead(200, {
            'Content-Type': 'text/plain' }
    );
    var postObj = JSON.parse(postData);
    //console.log(postObj.id);
    if(postObj.id != null)
    {
        var id = postObj.id;
        if(msgQueue[id]==null)
        {
            console.log(id + "'s msgQueue is empty!");
            responseErr(response);
            return ;
        }
        if(countDownList[id]!=null)
        {
            clearTimeout(countDownList[id]);
            countDownList[id] = setTimeout(function(){ clearNonBreathing(id); }, breathMaxInterval);
        }
        var retObj = {s:'ok'};
        retObj.msgList = msgQueue[id];
        retObj.msgNum = msgQueue[id].length;
        response.write(JSON.stringify(retObj));
        msgQueue[id] = [];
    }
    else
    {
        console.log(id + " is not valid!");
        responseErr(response);
        return ;
    }
    response.end();
};

var clearNonBreathing = function(id){
    idHash[id]=null;
    msgQueue[id]=null;
};

var login = function(request, response, postData){
    console.log('login called');
    response.writeHead(200, {
        'Content-Type': 'text/plain' }
    );
    retObj = {s:'ok'};
    var id = parseInt(Math.random() * idMax) + 100;
    while(idHash[id]!=undefined)
    {
        ++id;
        if(id>idMax + 100 ) id -= idMax;
    }
    retObj.id = id;
    idHash[id] = true;
    countDownList[id] = setTimeout(function(){ clearNonBreathing(id); }, loginDurationMax + breathMaxInterval);
    initializeMQ(id);
    spreadMsg(-1,{
        msgType:'msg',
        msgContent: 'Someone joined.',
        username: 'Server'
    });
    response.write(JSON.stringify(retObj));
    response.end();
};

var draw = function(request, response, postData){
    console.log('draw called');
    response.writeHead(200, {
            'Content-Type': 'text/plain' }
    );
    var postObj = JSON.parse(postData);
    if(postObj.id != null)
    {
        var id = postObj.id;
        if(msgQueue[id]==null)
        {
            responseErr(response);
            return ;
        }
        var msgObj = {
            msgType: 'history',
            msgContent: ''
        };
        msgObj.layer = postObj.layer;
        msgObj.colors = postObj.colors;
        msgObj.size = postObj.size;
        msgObj.opacity = postObj.opacity;
        msgObj.brushNo = postObj.brushNo;
        msgObj.XList = postObj.XList;
        msgObj.YList = postObj.YList;
        msgObj.PList = postObj.PList;
        msgObj.wacomOpacity = postObj.wacomOpacity;
        msgObj.wacomSize = postObj.wacomSize;
        spreadMsg(id, msgObj);
        var retObj = {s: 'ok'};
        response.write(JSON.stringify(retObj));
    }
    else
    {
        responseErr(response);
        return ;
    }
    response.end();
};

var msg = function(request, response, postData){
    console.log('msg called');
    response.writeHead(200, {
            'Content-Type': 'text/plain' }
    );
    var postObj = JSON.parse(postData);
    if(postObj.id != null)
    {
        var id = postObj.id;
        if(msgQueue[id]==null)
        {
            responseErr(response);
            return ;
        }
        var msgObj = {
            msgType: 'msg',
            msgContent: postObj.msg,
            username: postObj.un
        };
        spreadMsg(id, msgObj);
        msgQueue[id].push(msgObj);
        var retObj = {s: 'ok'};
        response.write(
            JSON.stringify(retObj)
        );
    }
    else
    {
        responseErr(response);
        return ;
    }
    response.end();
};

exports.breathHandler = breathe;
exports.loginHandler = login;
exports.drawHandler = draw;
exports.msgHandler = msg;
