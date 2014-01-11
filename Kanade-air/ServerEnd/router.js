/**
 * Created with JetBrains WebStorm.
 * User: aluex
 * Date: 1/10/14
 * Time: 21:04
 * To change this template use File | Settings | File Templates.
 */

var nodeStatic = require('node-static'),
    util = require('util');

var staticRoot = "../BrowserEnd";

var file = new(nodeStatic.Server)(staticRoot, {
    cache: 600,
    headers: { 'X-Powered-By': 'node-static' }
});

var route = function(handler, request, response, postData, pathname){
    console.log('Access:'+ pathname);
    if (typeof handler[pathname] === 'function') {
        handler[pathname](request, response, postData);
    } else {
        file.serve(request, response, function(error, result) {
            if (error) {
                console.error('Error serving %s - %s', request.url, error.message);
                if (error.status === 404 || error.status === 500) {
                    file.serveFile(util.format('/%d.html', error.status), error.status, {}, request, response);
                } else {
                    response.writeHead(error.status, error.headers);
                    response.end();
                }

            } else {
                console.log('%s - %s', request.url, response.message);
            }
        });
    }
};

exports.route = route;