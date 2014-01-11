/**
 * Created with JetBrains WebStorm.
 * User: aluex
 * Date: 1/11/14
 * Time: 0:24
 * To change this template use File | Settings | File Templates.
 */

///// Code related to front-end

var updateStatus = function(str){
    $('#statusText').text("Status: "+str);
};

var addMsgToChatRoom = function(str, username)
{
    var chatrow = document.createElement('div');
    chatrow.innerHTML = "<span class='chatroom-username'>" +username + "</span>:" +str;
    var crc = $('#chatRoomContent')[0];
    crc.appendChild(chatrow);
    crc.scrollTop = crc.scrollHeight;
};

var popNotice = function(str, type)
{
    $.notify(str, type);
};