/**
 * Created with JetBrains WebStorm.
 * User: aluex
 * Date: 1/10/14
 * Time: 20:59
 * To change this template use File | Settings | File Templates.
 */

var server = require("./server"),
    router = require("./router"),
    handler = require("./requestHandler");

var handle = {
    '/draw': handler.drawHandler,
    '/login': handler.loginHandler,
    '/breathe': handler.breathHandler,
    '/msg': handler.msgHandler
};

if(process.argv.length > 2)
    port = parseInt(process.argv[2]);
else
    port = 8201;

server.start(router, handle, port);
