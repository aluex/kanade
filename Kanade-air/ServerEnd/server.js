/* 
 * Kanade Server End, By Aluex 
 */

console.log('[ Kanade Server ]');

var http = require("http");
var urlParser = require("url");

var defaultPort = 8201;

var start = function(router, handler, listenPort){
    var onRequest = function(request, response) {
        var pathname = urlParser.parse(request.url).pathname;
        var postData = "";
        request.setEncoding("utf8");

        request.addListener("data", function(postDataChunk) {
            postData += postDataChunk;
            console.log("Received POST data chunk '"+
                postDataChunk + "'.");
        });

        request.addListener("end", function() {
            router.route(handler, request, response, postData, pathname);
        });
    }
    if(listenPort==undefined)listenPort = defaultPort;
    http.createServer(onRequest).listen(listenPort);
};

exports.start = start;
